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

# Run LLVM IR generation only
generate: all
	./$(TARGET) $(SAMPLE) > output.ll

# Clean build files
clean:
	rm -f *.o lex.yy.c muslang.tab.c muslang.tab.h $(TARGET) output output.o output.ll

.PHONY: all run generate clean