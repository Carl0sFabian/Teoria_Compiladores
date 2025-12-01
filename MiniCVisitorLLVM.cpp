#include "MiniCVisitorLLVM.h"

#include "llvm/IR/Constants.h"
#include "llvm/IR/Verifier.h"
#include "llvm/IR/Type.h"

#include <string>
#include <any>   
using namespace llvm;

// Constructor
MiniCVisitorLLVM::MiniCVisitorLLVM(CodeGen &cg)
    : cg(cg), sangria(0) {}

// Helpers: printf + sangría
FunctionCallee MiniCVisitorLLVM::getPrintf() {
    std::vector<Type*> args;
    args.push_back(PointerType::get(Type::getInt8Ty(cg.context), 0));

    FunctionType *printfTy =
        FunctionType::get(Type::getInt32Ty(cg.context), args, true);

    return cg.module->getOrInsertFunction("printf", printfTy);
}

std::string MiniCVisitorLLVM::tabs() {
    return std::string(sangria * 2, ' ');  // 2 espacios por nivel
}

void MiniCVisitorLLVM::irPrint(const std::string &msg) {
    std::string final = tabs() + msg + "\n";
    Value *fmt = cg.builder.CreateGlobalStringPtr(final);
    cg.builder.CreateCall(getPrintf(), {fmt});
}

// prog
// prog: (decl | stmt)* EOF;
antlrcpp::Any MiniCVisitorLLVM::visitProg(MiniCParser::ProgContext *ctx) {
    cg.createMain();

    for (auto ch : ctx->children) {
        if (!ch) continue;
        if (!ch->children.empty()) {
            visit(ch);
        }
    }

    // return 0;
    cg.builder.CreateRet(ConstantInt::get(
        Type::getInt32Ty(cg.context), 0));

    // verificación opcional
    if (verifyModule(*cg.module, &errs())) {
        errs() << "Module verification failed\n";
    }

    return nullptr;
}

// block: '{' (decl | stmt)* '}'   #Block
antlrcpp::Any MiniCVisitorLLVM::visitBlock(MiniCParser::BlockContext *ctx) {
    sangria++;
    for (auto ch : ctx->children) {
        if (!ch) continue;
        if (!ch->children.empty()) {
            visit(ch);
        }
    }
    sangria--;
    return nullptr;
}

// Declaraciones y asignaciones
// decl : vtype ID '=' expr ';' | vtype ID ';'
antlrcpp::Any MiniCVisitorLLVM::visitDecl(MiniCParser::DeclContext *ctx) {
    std::string tipo   = ctx->vtype()->getText();
    std::string nombre = ctx->ID()->getText();
    std::string expr   = ctx->expr() ? ctx->expr()->getText() : "";

    if (expr.empty()) {
        irPrint("Se declara " + tipo + " " + nombre);
    } else {
        irPrint("Se declara " + tipo + " " + nombre +
                " con valor " + expr);
    }
    return nullptr;
}

// Assign: ID '=' expr ';'
antlrcpp::Any MiniCVisitorLLVM::visitAssign(MiniCParser::AssignContext *ctx) {
    irPrint("Se actualiza " + ctx->ID()->getText() +
            " con " + ctx->expr()->getText());
    return nullptr;
}

// AugAssignStmt: ID ('+=' | '-=' | '*=' | '/=' | '%=') expr ';'
antlrcpp::Any MiniCVisitorLLVM::visitAugAssignStmt(MiniCParser::AugAssignStmtContext *ctx) {
    std::string nombre_variable = ctx->ID()->getText();

    std::string full = ctx->getText();    // ejemplo: "x+=5;" o "y-=z;"
    std::string operador_compuesto;

    if (full.find("+=") != std::string::npos)      operador_compuesto = "+=";
    else if (full.find("-=") != std::string::npos) operador_compuesto = "-=";
    else if (full.find("*=") != std::string::npos) operador_compuesto = "*=";
    else if (full.find("/=") != std::string::npos) operador_compuesto = "/=";
    else if (full.find("%=") != std::string::npos) operador_compuesto = "%=";

    std::string valor = ctx->expr()->getText();

    std::string simbolo = "+";
    if      (operador_compuesto == "-=") simbolo = "-";
    else if (operador_compuesto == "*=") simbolo = "*";
    else if (operador_compuesto == "/=") simbolo = "/";
    else if (operador_compuesto == "%=") simbolo = "%";

    irPrint("Se actualiza " + nombre_variable + ": " +
            nombre_variable + " = " + nombre_variable + " " +
            simbolo + " " + valor);
    return nullptr;
}

// IncDecStmt: ID ('++' | '--') ';'
antlrcpp::Any MiniCVisitorLLVM::visitIncDecStmt(MiniCParser::IncDecStmtContext *ctx) {
    std::string nombre = ctx->ID()->getText();
    std::string txt    = ctx->getText();  // "i++;" o "i--;"
    std::string op;

    if (txt.find("++") != std::string::npos) {
        op = "++";
    } else {
        op = "--";
    }

    if (op == "++") {
        irPrint("Se aumenta " + nombre + " en 1");
    } else {
        irPrint("Se disminuye " + nombre + " en 1");
    }
    return nullptr;
}

// cout / cin / expr ;

// CoutStmt: 'cout' ('<<' expr)+ ';'
antlrcpp::Any MiniCVisitorLLVM::visitCoutStmt(MiniCParser::CoutStmtContext *ctx) {
    std::string texto = "Se muestra: ";
    bool primero = true;

    std::vector<antlr4::tree::ParseTree*> l = ctx->children; 
    for (size_t i = 0; i < l.size(); ) {
        std::string tok = l[i]->getText();
        if (tok == "<<" && i + 1 < l.size()) {
            if (!primero) texto += " , ";
            texto += l[i+1]->getText();
            primero = false;
            i += 2;
        } else {
            i += 1;
        }
    }

    irPrint(texto);
    return nullptr;
}

// CinStmt: 'cin' ('>>' ID)+ ';'
antlrcpp::Any MiniCVisitorLLVM::visitCinStmt(MiniCParser::CinStmtContext *ctx) {
    std::string texto = "Se solicitan valores para: ";
    bool primero = true;

    std::vector<antlr4::tree::ParseTree*> l = ctx->children; 
    for (size_t i = 0; i < l.size(); ) {
        std::string tok = l[i]->getText();
        if (tok == ">>" && i + 1 < l.size()) {
            if (!primero) texto += ", ";
            texto += l[i+1]->getText();
            primero = false;
            i += 2;
        } else {
            i += 1;
        }
    }

    irPrint(texto);
    return nullptr;
}

// ExprStmt: expr ';'
antlrcpp::Any MiniCVisitorLLVM::visitExprStmt(MiniCParser::ExprStmtContext *ctx) {
    antlrcpp::Any res = visit(ctx->expr());

    if (auto p = std::any_cast<std::string>(&res)) {
        irPrint(*p);
    } else {
        irPrint("Se calcula: " + ctx->expr()->getText());
    }
    return nullptr;
}

// expr con mensaje

// exprUnary: ('!' | '+' | '-') expr
antlrcpp::Any MiniCVisitorLLVM::visitExprUnary(MiniCParser::ExprUnaryContext *ctx) {
    auto &l = ctx->children;   // ('!' | '+' | '-') expr
    std::string op  = l[0]->getText();
    std::string sub = l[1]->getText();

    if (op == "!") {
        return std::string("Se niega " + sub);
    } else if (op == "+") {
        return std::string("Se aplica signo positivo a " + sub);
    } else { // '-'
        return std::string("Se aplica signo negativo a " + sub);
    }
}

// exprPreIncDec: ('++' | '--') expr
antlrcpp::Any MiniCVisitorLLVM::visitExprPreIncDec(MiniCParser::ExprPreIncDecContext *ctx) {
    auto &l = ctx->children;  // ('++'|'--') expr
    std::string op  = l[0]->getText();
    std::string var = l[1]->getText();

    if (op == "++") {
        return std::string("Se aumenta " + var + " en 1");
    } else {
        return std::string("Se disminuye " + var + " en 1");
    }
}

// exprPostIncDec: expr ('++' | '--')
antlrcpp::Any MiniCVisitorLLVM::visitExprPostIncDec(MiniCParser::ExprPostIncDecContext *ctx) {
    auto &l = ctx->children;  // expr ('++'|'--')
    std::string var = l[0]->getText();
    std::string op  = l[1]->getText();

    if (op == "++") {
        return std::string("Se aumenta " + var + " en 1");
    } else {
        return std::string("Se disminuye " + var + " en 1");
    }
}

// exprEq: expr ('==' | '!=') expr
antlrcpp::Any MiniCVisitorLLVM::visitExprEq(MiniCParser::ExprEqContext *ctx) {
    auto &l = ctx->children;  // expr ('=='|'!=') expr
    std::string op = l[1]->getText();
    std::string op_txt = (op == "==") ? "igual a" : "distinto de";

    std::string txt = "Se compara: " + l[0]->getText() +
                      " " + op_txt + " " + l[2]->getText();
    return std::string(txt);
}

// exprAnd: expr '&&' expr
antlrcpp::Any MiniCVisitorLLVM::visitExprAnd(MiniCParser::ExprAndContext *ctx) {
    auto &l = ctx->children;  // expr '&&' expr
    std::string left_txt  = l[0]->getText();
    std::string right_txt = l[2]->getText();

    std::string txt = "Se evalúa (" + left_txt + ") y (" + right_txt + ")";
    return std::string(txt);
}

// exprOr: expr '||' expr
antlrcpp::Any MiniCVisitorLLVM::visitExprOr(MiniCParser::ExprOrContext *ctx) {
    auto &l = ctx->children;  // expr '||' expr
    std::string left_txt  = l[0]->getText();
    std::string right_txt = l[2]->getText();

    std::string txt = "Se evalúa (" + left_txt + ") o (" + right_txt + ")";
    return std::string(txt);
}

// if /  while

// IfStmt: 'if' '(' expr ')' stmt ('else' stmt)?
antlrcpp::Any MiniCVisitorLLVM::visitIfStmt(MiniCParser::IfStmtContext *ctx) {
    std::string condicion = ctx->expr() ? ctx->expr()->getText() : "";
    irPrint("Si " + condicion + ", se realiza lo siguiente:");
    sangria++;
    visit(ctx->stmt(0));
    sangria--;

    if (ctx->stmt().size() > 1) {
        irPrint("Si no, se realiza lo siguiente:");
        sangria++;
        visit(ctx->stmt(1));
        sangria--;
    }
    irPrint("Fin del si");
    return nullptr;
}

// WhileStmt: 'while' '(' expr ')' stmt
antlrcpp::Any MiniCVisitorLLVM::visitWhileStmt(MiniCParser::WhileStmtContext *ctx) {
    std::string condicion = ctx->expr() ? ctx->expr()->getText() : "";
    irPrint("Mientras " + condicion + ", se repite:");
    sangria++;
    visit(ctx->stmt());
    sangria--;
    irPrint("Fin del mientras");
    return nullptr;
}

// Helpers del for: forInitText / forPostText
// forInit: vtype ID ('=' expr)? (',' ID ('=' expr)? )*
//        | postItem (',' postItem)*
std::string MiniCVisitorLLVM::forInitText(MiniCParser::ForInitContext *ctx) {
    if (ctx->vtype() != nullptr) {
        std::string tipo = ctx->vtype()->getText();
        std::string texto;
        bool primera = true;

        auto &l = ctx->children;
        for (size_t i = 0; i < l.size();) {
            std::string tok = l[i]->getText();
            if (tok == tipo || tok == ",") {
                i++;
                continue;
            }
            if (tok == "=" && i + 1 < l.size()) {
                texto += " con " + l[i+1]->getText();
                i += 2;
                continue;
            }
            if (!primera) texto += " , ";
            texto += "se declara " + tipo + " " + tok;
            primera = false;
            i++;
        }
        return texto;
    }

    // caso: forInit con postItem (i=0, j+=2, k++)
    std::string texto;
    bool primero = true;
    std::string actual;

    for (auto hijo : ctx->children) {
        std::string tok = hijo->getText();
        if (tok == ",") {
            if (primero) {
                texto += actual;
                primero = false;
            } else {
                texto += " , " + actual;
            }
            actual.clear();
        } else {
            actual += tok;
        }
    }

    if (!actual.empty()) {
        if (primero) texto += actual;
        else texto += " , " + actual;
    }

    return texto;
}

// forPost: postItem (',' postItem)*
std::string MiniCVisitorLLVM::forPostText(MiniCParser::ForPostContext *ctx) {
    std::string texto;
    bool primero = true;
    std::string actual;

    for (auto ch : ctx->children) {
        std::string tok = ch->getText();
        if (tok == ",") {
            if (primero) {
                texto += actual;
                primero = false;
            } else {
                texto += " , " + actual;
            }
            actual.clear();
        } else {
            actual += tok;
        }
    }

    if (!actual.empty()) {
        if (primero) texto += actual;
        else texto += " , " + actual;
    }

    return texto;
}

// ForStmt: 'for' '(' forInit? ';' forCond? ';' forPost? ')' stmt
antlrcpp::Any MiniCVisitorLLVM::visitForStmt(MiniCParser::ForStmtContext *ctx) {
    std::string txt_init;
    if (ctx->forInit() != nullptr) {
        txt_init = forInitText(ctx->forInit());
    }

    std::string txt_cond;
    if (ctx->forCond() != nullptr && ctx->forCond()->expr() != nullptr) {
        txt_cond = ctx->forCond()->expr()->getText();
    }

    std::string txt_post;
    if (ctx->forPost() != nullptr) {
        txt_post = forPostText(ctx->forPost());
    }

    if (txt_init.empty()) txt_init = "—";
    if (txt_cond.empty()) txt_cond = "—";
    if (txt_post.empty()) txt_post = "—";

    irPrint("Se ejecuta un ciclo para ( inicialización: " + txt_init +
            " ; condición: " + txt_cond +
            " ; actualización: " + txt_post + " ):");

    sangria++;
    visit(ctx->stmt());
    sangria--;
    irPrint("Fin del para");
    return nullptr;
}
