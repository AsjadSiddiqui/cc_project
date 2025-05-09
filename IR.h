#ifndef IR_H
#define IR_H

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>
#include <stdio.h>

#include <map>
#include <stack>
#include <string>

using namespace llvm;

// Forward declarations
Value *getFromSymbolTable(const char *id);
void setDouble(const char *id, Value *value);
void printString(const char *str);
void printDouble(Value *value);
Value *performBinaryOperation(Value *lhs, Value *rhs, int op);
void yyerror(const char *err);
void initLLVM();
void printLLVMIR();
void addReturnInstr();
Value *createDoubleConstant(double val);

// Loop handling functions
void createLoopStart(int iterations);
void createLoopEnd();

// Conditional handling functions
Value *createComparison(Value *lhs, Value *rhs, CmpInst::Predicate pred);
void createIfStatement(Value *condition);
void createIfElseStatement(Value *condition);

// Symbol table and LLVM context
extern std::map<std::string, Value *> SymbolTable;
extern LLVMContext context;
extern Module *module;
extern IRBuilder<> builder;
extern Function *mainFunction;

// Loop management structures
struct LoopInfo {
    BasicBlock *headerBlock;
    BasicBlock *bodyBlock;
    BasicBlock *exitBlock;
    Value *counterVar;
    Value *iterationCount;
};
extern std::stack<LoopInfo> loopStack;

// Conditional management structures
struct IfInfo {
    BasicBlock *thenBlock;
    BasicBlock *elseBlock;
    BasicBlock *mergeBlock;
    Value *condition;
};
extern std::stack<IfInfo> ifStack;

#endif  // IR_H