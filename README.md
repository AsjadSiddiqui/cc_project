# MusLang Compiler

This is a compiler for MusLang, a musical esolang that represents programming concepts through musical notes.

## Language Specification

MusLang uses musical notes to represent different programming constructs:

### Types
- `F♯` - Integer
- `G` - Float
- `G♯` - Boolean
- `A♯` - String

### Arithmetic Operations
- `E` - Addition (+)
- `D♯` - Subtraction (-)
- `C♯` - Multiplication (*)
- `B` - Division (/)

### Logical Operations
- `D` - AND
- `A` - OR
- `F` - NOT

### Variable Declaration
- `C` - variable declaration 
- `C♯` - assignment

### Control Structures
- `A♯ A♯ A♯` - for loop start
- `A♯ B` - in
- `C♯ D♯` - range
- `C C C` - loop body start
- `B B B` - loop body end

### Output
- `E` - print

## Building the Compiler

To build the MusLang compiler, run:

```bash
make
```

This will generate the `muslangc` executable.

## Running MusLang Programs

To compile and run a MusLang program:

```bash
./muslangc sample.muslang > output.ll
llc output.ll -o output.s
gcc output.s -o output
./output
```

## Example Program

The example program provided in `sample.muslang` prints numbers from 0 to 4:

```
# Print numbers 0-4 in MusLang
C F♯ C♯      # Declare variable as integer
A♯ A♯ A♯     # for loop
A♯ B         # in
C♯ D♯ 5      # range 5
C C C        # begin loop body
E A♯         # print A♯
B B B        # end loop body
```

## Implementation

The compiler translates MusLang to LLVM IR using:
- Flex for lexical analysis
- Bison for parsing
- LLVM for code generation

The compiler follows a similar structure to the SSC compiler provided in the template files, with adaptations to handle the musical notation of MusLang.