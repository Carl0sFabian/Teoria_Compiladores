#include <iostream>
#include <fstream>
#include "antlr4-runtime.h"
#include "MiniCLexer.h"
#include "MiniCParser.h"
#include "MiniCVisitorLLVM.h"
#include "CodeGen.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Uso: minic <archivo.mc>\n";
        return 1;
    }

    std::ifstream stream(argv[1]);
    if (!stream.good()) {
        std::cerr << "No se pudo abrir " << argv[1] << "\n";
        return 1;
    }

    antlr4::ANTLRInputStream input(stream);
    MiniCLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    MiniCParser parser(&tokens);
    auto tree = parser.prog();

    CodeGen cg("MiniCModule");
    MiniCVisitorLLVM visitor(cg);
    visitor.visit(tree);

    std::error_code EC;
    llvm::raw_fd_ostream os("out.ll", EC);
    cg.module->print(os, nullptr);
    std::cout << "Generado out.ll\n";
    return 0;
}
