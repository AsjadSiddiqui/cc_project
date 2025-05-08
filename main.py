#!/usr/bin/env python
"""
Audio to Sheet Music Converter

This script converts MP3 and other audio files to sheet music notation.
Simply place your MP3 files in the same directory as this script and run it.
"""

import argparse
import fractions
import math
import os
import subprocess
import zipfile
from collections import Counter
from enum import Enum
from math import floor

import abjad
import librosa
import numpy as np


class AudioToSheetMusicConverter:
    
    class State(Enum):
        SILENCE = 0
        ONSET = 1
        SUSTAIN = 2

    def __init__(self):
        self.midi_min = 0
        self.midi_max = 0
        self.n_notes = 0
        self.fmin = 0
        self.fmax = 0
        self.__audio_data = []
        self.__sampling_rate = 0
        self.onset_method = 1
        self.frame_length = 2048
        self.hop_length = 512
        self.__f0_ = []
        self.__voiced_flags = []
        self.__onsets = []
        self.__notesroll = []
        self.__bpm = 0
        
    def initialize_audio_data(self, file_path):
        """Load audio data from file."""
        self.__audio_data, self.__sampling_rate = librosa.load(file_path)
        print(f"Successfully loaded audio data from {file_path}")
        
    def initialize_audio_parameters(self, note_min="C4", note_max="C6", onset_method=1):
        """Initialize audio processing parameters."""
        self.midi_min = librosa.note_to_midi(note_min)
        self.midi_max = librosa.note_to_midi(note_max)
        self.n_notes = self.midi_max - self.midi_min + 1
        self.fmin = librosa.note_to_hz(note_min)
        self.fmax = librosa.note_to_hz(note_max)
        self.onset_method = onset_method
        print(f"Note range: {note_min} - {note_max}")
        print(f"Onset detection method: {onset_method}")
        
    def __calculate_onsets_and_f0_candidates(self):
        """Calculate onsets and fundamental frequency candidates."""
        pitch, self.__voiced_flags, _ = librosa.pyin(
            y=self.__audio_data, fmin=self.fmin * 0.9, fmax=self.fmax * 1.1,
            sr=self.__sampling_rate, frame_length=self.frame_length, 
            win_length=int(self.frame_length / 2), hop_length=self.hop_length
        )
        tuning = librosa.pitch_tuning(pitch)
        self.__f0_ = np.round(librosa.hz_to_midi(pitch - tuning)).astype(int)
        
        print("Detecting note onsets...")
        if self.onset_method == 0:
            o_env = librosa.onset.onset_strength(y=self.__audio_data, sr=self.__sampling_rate)
        elif self.onset_method == 1:
            o_env = librosa.onset.onset_strength(
                y=self.__audio_data, sr=self.__sampling_rate, 
                aggregate=np.median, fmax=self.fmax * 1.5, n_mels=256
            )
        else:
            C = np.abs(librosa.cqt(y=self.__audio_data, sr=self.__sampling_rate))
            o_env = librosa.onset.onset_strength(
                sr=self.__sampling_rate, S=librosa.amplitude_to_db(C, ref=np.max)
            )
        
        self.__onsets = librosa.onset.onset_detect(
            y=self.__audio_data, sr=self.__sampling_rate, onset_envelope=o_env,
            hop_length=self.hop_length, backtrack=False
        )
        
    def __onsets_to_notesroll(self):
        """Convert detected onsets to a note roll."""
        silence, onset, sustain = 0, 1, 2
        my_state = silence
        output = []
        
        last_onset = 0
        last_midis = []
        hop_time = self.hop_length / self.__sampling_rate
        
        for i, _ in enumerate(self.__f0_):
            if my_state == silence:
                if i in self.__onsets:
                    # Found onset
                    last_midis = []
                    last_onset = i * hop_time
                    last_midis.append(self.__f0_[i])
                    my_state = onset
            
            elif my_state == onset:
                if i not in self.__onsets:
                    # Found sustaining phase
                    my_state = sustain
                    last_midis.append(self.__f0_[i])
            
            elif my_state == sustain:
                if i in self.__onsets:
                    # Found new onset, complete previous note
                    last_offset = i * hop_time
                    last_midi = Counter(last_midis).most_common(1)[0][0]
                    last_note = librosa.midi_to_note(last_midi)
                    my_note = [last_onset, last_offset, last_midi, last_note]
                    output.append(my_note)
                    
                    # Start new note
                    last_midis = []
                    last_onset = i * hop_time
                    last_midis.append(self.__f0_[i])
                    my_state = onset
                
                elif i + 1 < len(self.__voiced_flags) and not (self.__voiced_flags[i] or self.__voiced_flags[i+1]):
                    # Detected silence, complete previous note
                    last_offset = i * hop_time
                    last_midi = Counter(last_midis).most_common(1)[0][0]
                    last_note = librosa.midi_to_note(last_midi)
                    my_note = [last_onset, last_offset, last_midi, last_note]
                    output.append(my_note)
                    my_state = silence
                else:
                    last_midis.append(self.__f0_[i])
        
        # Handle any incomplete note at the end
        if my_state == sustain and last_midis:
            last_offset = (len(self.__f0_) - 1) * hop_time
            last_midi = Counter(last_midis).most_common(1)[0][0]
            last_note = librosa.midi_to_note(last_midi)
            my_note = [last_onset, last_offset, last_midi, last_note]
            output.append(my_note)
            
        return output
    
    def __round_to_fraction_power_of_two(self, n, precision=0.2):
        """Round a number to a fraction with power-of-two denominator."""
        i = 1
        while True:
            power_of_two = 2 ** i
            closest_fraction = round(n * power_of_two) / power_of_two
            if abs(n - closest_fraction) < precision:
                frac = fractions.Fraction(closest_fraction).limit_denominator()
                return frac.numerator, frac.denominator
            i += 1
    
    def __breakdown_fraction(self, numerator, denominator):
        """Break down a fraction into simpler fractions."""
        results = []
        while numerator > 0:
            power_of_two = 1
            while power_of_two <= numerator / 2:
                power_of_two *= 2
            results.append((1, denominator // power_of_two))
            numerator -= power_of_two
        return results
    
    def __split_duration(self, duration, left_space):
        """Split duration into parts that fit within left space."""
        if duration - left_space > 0:
            return np.array([left_space, duration - left_space])
        else:
            return np.array([duration])
    
    def convert_to_notes(self):
        """Convert audio to notes using the pYin algorithm and onset detection."""
        print("Starting audio analysis...")
        self.__calculate_onsets_and_f0_candidates()
        
        print("Converting detected onsets to notes...")
        self.__notesroll = self.__onsets_to_notesroll()
        self.__bpm = floor(librosa.beat.tempo(y=self.__audio_data)[0])
        print(f"Detected tempo: {self.__bpm} BPM")
        print(f"Found {len(self.__notesroll)} notes")
        
        return self.__notesroll, self.__bpm
    
    def generate_text_notes(self, output_directory='results'):
        """Generate a simple text file with the detected notes."""
        if not self.__notesroll:
            print("No notes to generate text file from. Run convert_to_notes() first.")
            return
            
        print("Generating plain text notes file...")
        # Make sure output directory exists
        os.makedirs(output_directory, exist_ok=True)
        
        # Create text file path
        txt_path = os.path.join(output_directory, 'notes.txt')
        
        # Extract just the note names (without octaves for simplicity)
        with open(txt_path, 'w') as f:
            f.write("# Detected Notes\n\n")
            for note in self.__notesroll:
                # Get the base note (A, B, C, etc.) without the octave number
                note_name = note[3][0]  # First character is the note name
                # Check if there's a sharp or flat
                if len(note[3]) > 1 and (note[3][1] == '♯' or note[3][1] == '♭'):
                    note_name += note[3][1]
                f.write(f"{note_name} ")
            
            # Add a more detailed section with timing information
            f.write("\n\n# Detailed Notes (with timing)\n\n")
            for i, note in enumerate(self.__notesroll):
                onset = float(note[0])
                offset = float(note[1])
                duration = offset - onset
                f.write(f"Note {i+1}: {note[3]} (Duration: {duration:.2f}s)\n")
        
        print(f"Created text notes file at {txt_path}")
        return txt_path

    def generate_sheet_music(self, output_directory='results', error=0.05, precision=0.2, meter=(4, 4)):
        """Generate sheet music from the note roll."""
        if not self.__notesroll:
            print("No notes to generate sheet music from. Run convert_to_notes() first.")
            return
            
        print("Generating sheet music...")
        # Make sure output directory exists
        os.makedirs(output_directory, exist_ok=True)
        
        container = abjad.Container()
        measures_in_bar = meter[0]
        basic_meter_unit = meter[1]
        basic_meter_unit_time = self.__bpm/60 * (meter[1]/4)

        current_bar = abjad.Duration(meter)
        for note in self.__notesroll:
            onset = float(note[0])
            offset = float(note[1])
            height = note[3].replace("♯", "s")
            relation = (offset - onset) * basic_meter_unit_time
            
            if abs(relation - np.round(relation)) < error * np.round(relation) and np.round(relation) % 2 != 1:
                note_length = abjad.Duration(1, 4/(2**round(math.log2(relation))))
                durations = self.__split_duration(note_length, current_bar)
                for i, duration in enumerate(durations):
                    current_note = abjad.Note(height, duration)
                    print(current_note)
                    if len(durations) > 1 and i == 0:
                        abjad.attach(abjad.StartSlur(), current_note)
                    elif len(durations) > 1 and i == len(durations) - 1:
                        abjad.attach(abjad.StopSlur(), current_note)
                    container.append(current_note)
                    current_bar -= duration
                    if current_bar == 0:
                        current_bar = abjad.Duration(meter)
            else:
                numerator, denominator = self.__round_to_fraction_power_of_two(relation, precision)
                measures = self.__breakdown_fraction(numerator, denominator * 4)
                
                for i, measure in enumerate(measures):
                    durations = self.__split_duration(abjad.Duration(measure), current_bar)
                    for j, duration in enumerate(durations):
                        current_note = abjad.Note(height, duration)
                        if ((i==0 and len(measures) > 1) or (j==0 and len(durations) > 1)):
                            abjad.attach(abjad.StartSlur(), current_note)
                        elif ((i==len(measures)-1 and len(measures) > 1) or (j==len(durations)-1 and len(durations) > 1)):
                            abjad.attach(abjad.StopSlur(), current_note)
                        current_bar -= duration
                        if current_bar == 0:
                            current_bar = abjad.Duration(meter)
                        container.append(current_note)
                
        # Create LilyPond file
        lilypond_file = abjad.LilyPondFile([container])
        
        # Save the LilyPond file
        ly_path = os.path.join(output_directory, 'result.ly')
        with open(ly_path, 'w') as f:
            f.write(abjad.lilypond(lilypond_file))
        
        print(f"Created LilyPond file at {ly_path}")
        
        # Check if LilyPond is installed and try to generate PDF and PNG
        try:
            # Try to find LilyPond executable
            lilypond_cmd = None
            for path in ['/usr/local/bin/lilypond', '/usr/bin/lilypond', '/opt/homebrew/bin/lilypond']:
                if os.path.exists(path):
                    lilypond_cmd = path
                    break
            
            if not lilypond_cmd:
                # Try to find using which command
                try:
                    lilypond_cmd = subprocess.check_output(['which', 'lilypond']).decode().strip()
                except:
                    pass
            
            if lilypond_cmd:
                print(f"Found LilyPond at: {lilypond_cmd}")
                # Generate PDF
                subprocess.run([lilypond_cmd, '--pdf', '-o', output_directory, ly_path], check=True)
                print(f"Created PDF in {output_directory}/result.pdf")
                
                # Generate PNG
                subprocess.run([lilypond_cmd, '--png', '-o', output_directory, ly_path], check=True)
                print(f"Created PNG in {output_directory}/result.png")
            else:
                print("LilyPond not found. Generated only the .ly file.")
                print("To generate PDF and PNG files, please install LilyPond:")
                print("  - On macOS: brew install lilypond")
                print("  - On Linux: sudo apt-get install lilypond")
                print("Once installed, you can generate the files manually with:")
                print(f"  lilypond --pdf -o {output_directory} {ly_path}")
                print(f"  lilypond --png -o {output_directory} {ly_path}")
        except Exception as e:
            print(f"Error generating PDF/PNG: {str(e)}")
            print("Generated only the .ly file.")
        
        print("Sheet music generation complete!")
        return ly_path


def process_audio_file(file_path, note_min="C4", note_max="C6", onset_method=1, output_format="lily"):
    """Process a single audio file and convert it to sheet music or text notes.
    
    Args:
        file_path: Path to the audio file
        note_min: Minimum note to detect (e.g., C4)
        note_max: Maximum note to detect (e.g., C6)
        onset_method: Onset detection method (0, 1, 2)
        output_format: "lily" for LilyPond/PDF/PNG or "text" for simple text notes
    
    Returns:
        Path to the generated output file
    """
    output_directory = os.path.splitext(os.path.basename(file_path))[0] + "_sheet_music"
    
    converter = AudioToSheetMusicConverter()
    converter.initialize_audio_data(file_path)
    converter.initialize_audio_parameters(note_min, note_max, onset_method)
    converter.convert_to_notes()
    
    if output_format.lower() == "text":
        return converter.generate_text_notes(output_directory=output_directory)
    else:
        return converter.generate_sheet_music(output_directory=output_directory)


def main():
    """Main function to process command line arguments and convert audio files."""
    parser = argparse.ArgumentParser(description='Convert audio files to sheet music')
    parser.add_argument('--file', type=str, help='Path to audio file to convert')
    parser.add_argument('--dir', type=str, default='.', help='Directory containing audio files to convert')
    parser.add_argument('--min-note', type=str, default='C4', help='Minimum note to detect (e.g., C4)')
    parser.add_argument('--max-note', type=str, default='C6', help='Maximum note to detect (e.g., C6)')
    parser.add_argument('--onset-method', type=int, default=1, choices=[0, 1, 2], 
                        help='Onset detection method: 0=Mean(Mel), 1=Median(Mel), 2=Mean(CQT)')
    parser.add_argument('--format', type=str, default='lily', choices=['lily', 'text'],
                        help='Output format: lily for LilyPond/PDF/PNG, text for simple text notes (C, D, A, etc.)')
    
    args = parser.parse_args()
    
    audio_files = []
    if args.file:
        if os.path.isfile(args.file):
            audio_files.append(args.file)
        else:
            print(f"Error: File {args.file} does not exist")
            return
    else:
        # Process all audio files in directory
        for filename in os.listdir(args.dir):
            if filename.lower().endswith(('.mp3', '.wav', '.flac')):
                audio_files.append(os.path.join(args.dir, filename))
    
    if not audio_files:
        print("No audio files found to process.")
        return
    
    print(f"Found {len(audio_files)} audio files to process.")
    for file_path in audio_files:
        print(f"\nProcessing: {file_path}")
        try:
            output_path = process_audio_file(
                file_path, 
                note_min=args.min_note,
                note_max=args.max_note,
                onset_method=args.onset_method,
                output_format=args.format
            )
            print(f"Successfully converted {file_path} to {'text notes' if args.format == 'text' else 'sheet music'}: {output_path}")
        except Exception as e:
            print(f"Error processing {file_path}: {str(e)}")


if __name__ == "__main__":
    main()
