#include "IR.h"

// Symbol table and LLVM context
std::map<std::string, Value *> SymbolTable;
LLVMContext context;
Module *module = nullptr;
IRBuilder<> builder(context);
Function *mainFunction = nullptr;

// Loop management stack
std::stack<LoopInfo> loopStack;

// Conditional management stack
std::stack<IfInfo> ifStack;

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

/**
 * This function is completely disabled to avoid interfering with parsing.
 * Return instructions are now handled in main() after parsing is complete.
 */
void addReturnInstr() {
    // Do nothing - all return handling is now in main()
    return;
}

Value *createDoubleConstant(double val) {
    return ConstantFP::get(context, APFloat(val));
}

void printLLVMIR() {
    module->print(errs(), nullptr);
}

Value *getFromSymbolTable(const char *id) {
    std::string name(id);
    if (SymbolTable.find(name) != SymbolTable.end()) {
        return SymbolTable[name];
    } else {
        Value *defaultValue = builder.CreateAlloca(builder.getDoubleTy(), nullptr, name);
        SymbolTable[name] = defaultValue;
        return defaultValue;
    }
}

void setDouble(const char *id, Value *value) {
    Value *ptr = getFromSymbolTable(id);
    builder.CreateStore(value, ptr);
}

/**
 * General LLVM function to print a value in given format.
 */
void printfLLVM(const char *format, Value *inputValue) {
    // Check if printf function already exists
    Function *printfFunc = module->getFunction("printf");
    // If it does not exist then create it
    if (!printfFunc) {
        // The printf function returns integer and takes variable number of parameters
        std::vector<Type *> printfArgTypes;
        printfArgTypes.push_back(PointerType::get(Type::getInt8Ty(context), 0));
        FunctionType *printfTy = FunctionType::get(builder.getInt32Ty(), printfArgTypes, true);
        printfFunc = Function::Create(printfTy, Function::ExternalLinkage, "printf", module);
    }

    // Create global string for format
    Constant *formatConst = ConstantDataArray::getString(context, format);
    GlobalVariable *formatVar = new GlobalVariable(
        *module,
        formatConst->getType(),
        true,  // isConstant
        GlobalValue::PrivateLinkage,
        formatConst,
        ".str");

    // Get pointer to the string
    Value *formatPtr = builder.CreateBitCast(formatVar, PointerType::get(Type::getInt8Ty(context), 0));

    // Call the printf function using Call LLVM instruction
    std::vector<Value *> args;
    args.push_back(formatPtr);
    if (inputValue) {
        args.push_back(inputValue);
    }
    builder.CreateCall(printfFunc, args, "printfCall");
}

void printString(const char *str) {
    // Create global string constant for the string literal using the same approach as printfLLVM
    Constant *strConst = ConstantDataArray::getString(context, str);
    GlobalVariable *strVar = new GlobalVariable(
        *module,
        strConst->getType(),
        true,  // isConstant
        GlobalValue::PrivateLinkage,
        strConst,
        ".str");

    // Get pointer to the string
    Value *strPtr = builder.CreateBitCast(strVar, PointerType::get(Type::getInt8Ty(context), 0));

    // Pass the string pointer to printfLLVM
    printfLLVM("%s\n", strPtr);
}

void printDouble(Value *value) {
    printfLLVM("%f\n", value);
}

Value *performBinaryOperation(Value *lhs, Value *rhs, int op) {
    switch (op) {
        case '+':
            return builder.CreateFAdd(lhs, rhs, "fadd");
        case '-':
            return builder.CreateFSub(lhs, rhs, "fsub");
        case '*':
            return builder.CreateFMul(lhs, rhs, "fmul");
        case '/':
            return builder.CreateFDiv(lhs, rhs, "fdiv");
        default:
            yyerror("illegal binary operation");
            exit(EXIT_FAILURE);
    }
}

// Create comparison between two values
Value *createComparison(Value *lhs, Value *rhs, CmpInst::Predicate pred) {
    Value *cmp = builder.CreateFCmp(pred, lhs, rhs, "comparison");
    // Convert i1 to double for consistent type handling
    return builder.CreateUIToFP(cmp, builder.getDoubleTy(), "boolToDouble");
}

// Creates the if statement structure
void createIfStatement(Value *condition) {
    // Convert double back to boolean for the branch
    Value *condBool = builder.CreateFPToUI(condition, builder.getInt1Ty(), "doubleToBool");

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

    // Don't add branch to merge block yet - that will be done when handling E E E token
}

// Creates the if-else statement structure
void createIfElseStatement(Value *condition) {
    // Convert double back to boolean for the branch
    Value *condBool = builder.CreateFPToUI(condition, builder.getInt1Ty(), "doubleToBool");

    // Create blocks for 'then', 'else', and merge (after if-else)
    BasicBlock *thenBlock = BasicBlock::Create(context, "then", mainFunction);
    BasicBlock *elseBlock = BasicBlock::Create(context, "else", mainFunction);
    BasicBlock *mergeBlock = BasicBlock::Create(context, "ifcont", mainFunction);

    // Create conditional branch based on condition
    builder.CreateCondBr(condBool, thenBlock, elseBlock);

    // Set insert point to then block

    // Store for nested usage - the if-else structure
    IfInfo ifInfo;
    ifInfo.thenBlock = thenBlock;
    ifInfo.elseBlock = elseBlock;
    ifInfo.mergeBlock = mergeBlock;
    ifInfo.condition = condition;

    ifStack.push(ifInfo);

    // We will NOT add branches yet - they'll be added when we process tokens
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

    // Add code to make the current loop counter available to the MusLang code
    // Convert the counter to double and store it in a symbolic variable "i"
    // This allows the MusLang code to access the internal loop counter
    Value *counterAsDouble = builder.CreateSIToFP(currentCount, builder.getDoubleTy(), "counter_as_double");
    Value *iVar = getFromSymbolTable("i");
    builder.CreateStore(counterAsDouble, iVar);

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
