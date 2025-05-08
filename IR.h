#include <string>
#include <map>
#include <stack>
#include <stdio.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/Value.h>
#include <llvm/Support/raw_ostream.h>

using namespace llvm;

// Forward declarations
Value* getFromSymbolTable(const char *id);
void setDouble(const char *id, Value* value);
void printString(const char *str);
void printDouble(Value* value);
Value* performBinaryOperation(Value* lhs, Value* rhs, int op);
void yyerror(const char *err);
void initLLVM();
void printLLVMIR();
void addReturnInstr();
Value* createDoubleConstant(double val);

// Loop handling functions
void createLoopStart(int iterations);
void createLoopEnd();

// Conditional handling functions
Value* createComparison(Value* lhs, Value* rhs, CmpInst::Predicate pred);
void createIfStatement(Value* condition);
void createIfElseStatement(Value* condition);

// Symbol table and LLVM context
static std::map<std::string, Value *> SymbolTable;
static LLVMContext context;
static Module *module = nullptr;
static IRBuilder<> builder(context);
static Function *mainFunction = nullptr;

// Loop management structures
struct LoopInfo {
    BasicBlock *headerBlock;
    BasicBlock *bodyBlock;
    BasicBlock *exitBlock;
    Value *counterVar;
    Value *iterationCount;
};
static std::stack<LoopInfo> loopStack;

// Conditional management structures
struct IfInfo {
    BasicBlock *thenBlock;
    BasicBlock *elseBlock;
    BasicBlock *mergeBlock;
    Value *condition;
};
static std::stack<IfInfo> ifStack;

/**
* Initialize LLVM
* Create main function (similar to C-main) that returns an int but takes no parameters.
*/
void initLLVM() {
    module = new Module("MusLang", context);
    // Returns an int and has fixed number of parameters. Does not take any parameters.
    FunctionType *mainTy = FunctionType::get(builder.getInt32Ty(), false);
    // The main function definition.
    mainFunction = Function::Create(mainTy, Function::ExternalLinkage, "main", module);
    // Create entry basic block of the main function.
    BasicBlock *entry = BasicBlock::Create(context, "entry", mainFunction);
    // Tell builder that instruction to be added in this basic block.
    builder.SetInsertPoint(entry);
}

void addReturnInstr() {
    builder.CreateRet(ConstantInt::get(context, APInt(32, 0)));
}

Value* createDoubleConstant(double val) {
    return ConstantFP::get(context, APFloat(val));
}

void printLLVMIR() {
    module->print(errs(), nullptr);
}

Value* getFromSymbolTable(const char *id) {
    std::string name(id);
    if(SymbolTable.find(name) != SymbolTable.end()) {
        return SymbolTable[name];
    } else {
        Value* defaultValue = builder.CreateAlloca(builder.getDoubleTy(), nullptr, name);
        SymbolTable[name] = defaultValue;
        return defaultValue;
    }
}

void setDouble(const char *id, Value* value) {
    Value *ptr = getFromSymbolTable(id);
    builder.CreateStore(value, ptr);
}

/**
* General LLVM function to print a value in given format.
*/
void printfLLVM(const char *format, Value *inputValue) {
    //check if printf function already exist
    Function *printfFunc = module->getFunction("printf");
    //if it does not exist then create it.
    if(!printfFunc) {
        //The printf function returns integer.
        //It takes variable number of parameters.
        FunctionType *printfTy = FunctionType::get(builder.getInt32Ty(), PointerType::get(builder.getInt8Ty(), 0), true);
        printfFunc = Function::Create(printfTy, Function::ExternalLinkage, "printf", module); // function is created.
    }
    //create global string pointer for format.
    Value *formatVal = builder.CreateGlobalStringPtr(format);
    //Call the printf function using Call LLVM instruction
    builder.CreateCall(printfFunc, {formatVal, inputValue}, "printfCall");
}

void printString(const char *str) {
    Value *strValue = builder.CreateGlobalStringPtr(str);
    printfLLVM("%s\n", strValue);
}

void printDouble(Value *value) {
    printfLLVM("%f\n", value); 
}

Value* performBinaryOperation(Value* lhs, Value* rhs, int op) {
    switch (op) {
        case '+': return builder.CreateFAdd(lhs, rhs, "fadd");
        case '-': return builder.CreateFSub(lhs, rhs, "fsub");
        case '*': return builder.CreateFMul(lhs, rhs, "fmul");
        case '/': return builder.CreateFDiv(lhs, rhs, "fdiv");
        default: yyerror("illegal binary operation"); exit(EXIT_FAILURE);
    }
}

// Create comparison between two values
Value* createComparison(Value* lhs, Value* rhs, CmpInst::Predicate pred) {
    Value* cmp = builder.CreateFCmp(pred, lhs, rhs, "comparison");
    // Convert i1 to double for consistent type handling
    return builder.CreateUIToFP(cmp, builder.getDoubleTy(), "boolToDouble");
}

// Creates the if statement structure
void createIfStatement(Value* condition) {
    // Convert double back to boolean for the branch
    Value* condBool = builder.CreateFPToUI(condition, builder.getInt1Ty(), "doubleToBool");
    
    // Create blocks for 'then' and merge (after if)
    BasicBlock *thenBlock = BasicBlock::Create(context, "then", mainFunction);
    BasicBlock *mergeBlock = BasicBlock::Create(context, "ifcont", mainFunction);
    
    // Create conditional branch based on condition
    builder.CreateCondBr(condBool, thenBlock, mergeBlock);
    
    // Set insert point to then block
    builder.SetInsertPoint(thenBlock);
    
    // Store for nested usage - body code is handled by bison
    IfInfo ifInfo = {thenBlock, nullptr, mergeBlock, condition};
    ifStack.push(ifInfo);
    
    // Add unconditional branch from 'then' to 'merge'
    builder.CreateBr(mergeBlock);
    
    // Set insertion point to merge block for code after if
    builder.SetInsertPoint(mergeBlock);
}

// Creates the if-else statement structure
void createIfElseStatement(Value* condition) {
    // Convert double back to boolean for the branch
    Value* condBool = builder.CreateFPToUI(condition, builder.getInt1Ty(), "doubleToBool");
    
    // Create blocks for 'then', 'else', and merge (after if-else)
    BasicBlock *thenBlock = BasicBlock::Create(context, "then", mainFunction);
    BasicBlock *elseBlock = BasicBlock::Create(context, "else", mainFunction);
    BasicBlock *mergeBlock = BasicBlock::Create(context, "ifcont", mainFunction);
    
    // Create conditional branch based on condition
    builder.CreateCondBr(condBool, thenBlock, elseBlock);
    
    // Set insert point to then block
    builder.SetInsertPoint(thenBlock);
    
    // Store for nested usage - body code is handled by bison
    IfInfo ifInfo = {thenBlock, elseBlock, mergeBlock, condition};
    ifStack.push(ifInfo);
    
    // Add unconditional branch from 'then' to 'merge'
    builder.CreateBr(mergeBlock);
    
    // Set insertion point to else block
    builder.SetInsertPoint(elseBlock);
    
    // Body code is inserted by bison
    
    // Add unconditional branch from 'else' to 'merge'
    builder.CreateBr(mergeBlock);
    
    // Set insertion point to merge block for code after if-else
    builder.SetInsertPoint(mergeBlock);
}

// Creates the beginning of a for loop
void createLoopStart(int iterations) {
    // Create blocks for the loop header, body, and exit
    BasicBlock *headerBlock = BasicBlock::Create(context, "loop_header", mainFunction);
    BasicBlock *bodyBlock = BasicBlock::Create(context, "loop_body", mainFunction);
    BasicBlock *exitBlock = BasicBlock::Create(context, "loop_exit", mainFunction);
    
    // Create and initialize loop counter variable
    Value *counterVar = builder.CreateAlloca(builder.getInt32Ty(), nullptr, "loop_counter");
    builder.CreateStore(ConstantInt::get(context, APInt(32, 0)), counterVar);
    
    // Create constant for iteration count
    Value *iterationCount = ConstantInt::get(context, APInt(32, iterations));
    
    // Jump to the header block
    builder.CreateBr(headerBlock);
    
    // Loop header logic
    builder.SetInsertPoint(headerBlock);
    
    // Load the counter
    Value *currentCount = builder.CreateLoad(builder.getInt32Ty(), counterVar, "current_count");
    
    // Compare counter with iteration count
    Value *conditionVal = builder.CreateICmpSLT(currentCount, iterationCount, "loop_condition");
    
    // Conditional branch based on the condition
    builder.CreateCondBr(conditionVal, bodyBlock, exitBlock);
    
    // Set insert point to the loop body
    builder.SetInsertPoint(bodyBlock);
    
    // Save loop information for later use
    LoopInfo loopInfo = {headerBlock, bodyBlock, exitBlock, counterVar, iterationCount};
    loopStack.push(loopInfo);
}

// Handles the end of a for loop
void createLoopEnd() {
    if (loopStack.empty()) {
        yyerror("loop end without loop start");
        exit(EXIT_FAILURE);
    }
    
    // Get loop information
    LoopInfo loopInfo = loopStack.top();
    loopStack.pop();
    
    // Increment loop counter
    Value *currentCount = builder.CreateLoad(builder.getInt32Ty(), loopInfo.counterVar, "current_count");
    Value *incrementedCount = builder.CreateAdd(currentCount, ConstantInt::get(context, APInt(32, 1)), "incremented_count");
    builder.CreateStore(incrementedCount, loopInfo.counterVar);
    
    // Jump back to header for next iteration check
    builder.CreateBr(loopInfo.headerBlock);
    
    // Set insert point to the exit block for code that follows the loop
    builder.SetInsertPoint(loopInfo.exitBlock);
}

void yyerror(const char *err) {
    fprintf(stderr, "\n%s\n", err);
}