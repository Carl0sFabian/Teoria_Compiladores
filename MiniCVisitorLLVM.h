#pragma once

#include "MiniCBaseVisitor.h"
#include "MiniCParser.h"
#include "CodeGen.h"

#include "antlr4-runtime.h"
#include "llvm/IR/Value.h"

#include <string>

class MiniCVisitorLLVM : public MiniCBaseVisitor {
public:
    explicit MiniCVisitorLLVM(CodeGen &cg);

    // programa
    antlrcpp::Any visitProg(MiniCParser::ProgContext *ctx) override;

    // bloques
    antlrcpp::Any visitBlock(MiniCParser::BlockContext *ctx) override;

    // declaraciones y asignaciones
    antlrcpp::Any visitDecl(MiniCParser::DeclContext *ctx) override;
    antlrcpp::Any visitAssign(MiniCParser::AssignContext *ctx) override;
    antlrcpp::Any visitAugAssignStmt(MiniCParser::AugAssignStmtContext *ctx) override;
    antlrcpp::Any visitIncDecStmt(MiniCParser::IncDecStmtContext *ctx) override;

    // cout / cin / expr 
    antlrcpp::Any visitCoutStmt(MiniCParser::CoutStmtContext *ctx) override;
    antlrcpp::Any visitCinStmt(MiniCParser::CinStmtContext *ctx) override;
    antlrcpp::Any visitExprStmt(MiniCParser::ExprStmtContext *ctx) override;

    // expresiones que devuelven mensaje
    antlrcpp::Any visitExprUnary(MiniCParser::ExprUnaryContext *ctx) override;
    antlrcpp::Any visitExprPreIncDec(MiniCParser::ExprPreIncDecContext *ctx) override;
    antlrcpp::Any visitExprPostIncDec(MiniCParser::ExprPostIncDecContext *ctx) override;
    antlrcpp::Any visitExprEq(MiniCParser::ExprEqContext *ctx) override;
    antlrcpp::Any visitExprAnd(MiniCParser::ExprAndContext *ctx) override;
    antlrcpp::Any visitExprOr(MiniCParser::ExprOrContext *ctx) override;

    // control de flujo
    antlrcpp::Any visitIfStmt(MiniCParser::IfStmtContext *ctx) override;
    antlrcpp::Any visitWhileStmt(MiniCParser::WhileStmtContext *ctx) override;
    antlrcpp::Any visitForStmt(MiniCParser::ForStmtContext *ctx) override;

private:
    CodeGen &cg;
    int sangria; // nivel de sangría

    // helpers de impresión en IR
    llvm::FunctionCallee getPrintf();
    void irPrint(const std::string &msg);
    std::string tabs();

    // helpers para el for
    std::string forInitText(MiniCParser::ForInitContext *ctx);
    std::string forPostText(MiniCParser::ForPostContext *ctx);
};
