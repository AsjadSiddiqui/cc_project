# Makefile for MusLang Compiler
# Configured for macOS with Homebrew LLVM

# Compiler configuration (using Homebrew's LLVM)
CC := /opt/homebrew/Cellar/llvm/20.1.4/bin/clang
CXX := /opt/homebrew/Cellar/llvm/20.1.4/bin/clang++

# LLVM configuration
LLVM_CONFIG := /opt/homebrew/Cellar/llvm/20.1.4/bin/llvm-config
LLC := /opt/homebrew/Cellar/llvm/20.1.4/bin/llc
LLVM_INCLUDE := -I/opt/homebrew/Cellar/llvm/20.1.4/include

# Flags and libraries
LDFLAGS := -L/opt/homebrew/Cellar/llvm/20.1.4/lib -Wl,-rpath,/opt/homebrew/Cellar/llvm/20.1.4/lib
CPPFLAGS := -I/opt/homebrew/Cellar/llvm/20.1.4/include -I/opt/homebrew/Cellar/llvm/20.1.4/include/c++/v1/
CXXFLAGS := $(shell $(LLVM_CONFIG) --cxxflags) $(LLVM_INCLUDE) -std=c++17 -fno-rtti
LIBS := $(shell $(LLVM_CONFIG) --libs core)

# Target and input files
TARGET := muslangc
SAMPLE := sample.muslang
INSERTION_SORT := insertion_sort.muslang
LOOP_DEBUG := loop_debug.muslang

all: $(TARGET)

# Build the MusLang compiler
$(TARGET): lex.yy.o muslang.tab.o IR.o
	$(CXX) -o $@ $^ $(LDFLAGS) $(LIBS)

# Compile lexer
lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

# Compile parser
muslang.tab.o: muslang.tab.c
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

# Compile IR implementation
IR.o: IR.cpp
	$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c -o $@ $<

# Generate lexer source
lex.yy.c: muslang.l muslang.tab.h
	flex muslang.l

# Generate parser source
muslang.tab.c muslang.tab.h: muslang.y
	bison -d muslang.y

# Run complete pipeline: compile -> generate -> run
run: all
	./$(TARGET) $(SAMPLE) > output.ll
	$(LLC) -filetype=obj output.ll -o output.o
	$(CC) output.o -o output
	./output

# Run insertion sort example
run_insertion_sort: all
	./$(TARGET) $(INSERTION_SORT) > insertion_sort.ll
	$(LLC) -filetype=obj insertion_sort.ll -o insertion_sort.o
	$(CC) insertion_sort.o -o insertion_sort
	./insertion_sort

run_generated_insertion_sort: all
	$(LLC) -filetype=obj insertion_sort.ll -o insertion_sort.o
	$(CC) insertion_sort.o -o insertion_sort
	./insertion_sort

# Run loop debugging example
run_loop_debug: all
	./$(TARGET) $(LOOP_DEBUG) > loop_debug.ll
	$(LLC) -filetype=obj loop_debug.ll -o loop_debug.o
	$(CC) loop_debug.o -o loop_debug
	./loop_debug

run_generated_loop_debug: all
	$(LLC) -filetype=obj loop_debug.ll -o loop_debug.o
	$(CC) loop_debug.o -o loop_debug
	./loop_debug

# Run LLVM IR generation only
generate: all
	./$(TARGET) $(SAMPLE) > output.ll

# Clean build files
clean:
	rm -f *.o lex.yy.c muslang.tab.c muslang.tab.h $(TARGET) output output.o output.ll insertion_sort insertion_sort.o insertion_sort.ll loop_debug loop_debug.o loop_debug.ll

.PHONY: all run run_insertion_sort generate clean