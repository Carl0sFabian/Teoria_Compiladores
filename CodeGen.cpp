#include "CodeGen.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Support/raw_ostream.h"

using namespace llvm;

CodeGen::CodeGen(const std::string &moduleName)
    : module(std::make_unique<Module>(moduleName, context)), builder(context) {
    // nothing else required here
}

Function* CodeGen::createMain() {
    FunctionType *funcType = FunctionType::get(IntegerType::get(context, 32), false);
    Function *mainFn = Function::Create(funcType, Function::ExternalLinkage, "main", module.get());
    BasicBlock *bb = BasicBlock::Create(context, "entry", mainFn);
    builder.SetInsertPoint(bb);
    return mainFn;
}

AllocaInst* CodeGen::createEntryBlockAlloca(Function *func, const std::string &varName, Type *type) {
    IRBuilder<> tmpB(&func->getEntryBlock(), func->getEntryBlock().begin());
    return tmpB.CreateAlloca(type, nullptr, varName);
}

Value* CodeGen::castToDoubleIfNeeded(Value* v) {
    if (!v) return nullptr;
    if (v->getType()->isDoubleTy()) return v;
    if (v->getType()->isIntegerTy(32))
        return builder.CreateSIToFP(v, Type::getDoubleTy(context), "itod");
    return v;
}

Value* CodeGen::castToIntIfNeeded(Value* v) {
    if (!v) return nullptr;
    if (v->getType()->isIntegerTy(32)) return v;
    if (v->getType()->isDoubleTy())
        return builder.CreateFPToSI(v, Type::getInt32Ty(context), "ftoi");
    return v;
}
