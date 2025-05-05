CXX = g++
CXXFLAGS = -g -O0 -std=c++17 `llvm-config --cxxflags`
LDFLAGS = `llvm-config --ldflags --system-libs --libs core`

all: muslangc

muslangc: lex.yy.o muslang.tab.o IR.o
	$(CXX) -o $@ $^ $(LDFLAGS)

lex.yy.o: lex.yy.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

muslang.tab.o: muslang.tab.c
	$(CXX) $(CXXFLAGS) -c -o $@ $<

IR.o: IR.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

lex.yy.c: muslang.l muslang.tab.h
	flex muslang.l

muslang.tab.c muslang.tab.h: muslang.y
	bison -d muslang.y

IR.cpp: IR.h
	echo "#include \"IR.h\"" > IR.cpp

clean:
	rm -f *.o lex.yy.c muslang.tab.c muslang.tab.h IR.cpp muslangc

.PHONY: all clean