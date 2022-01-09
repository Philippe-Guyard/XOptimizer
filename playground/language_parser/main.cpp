#include <fstream>
#include <iostream>
#include <sstream>
#include <limits>
#include "parser.h"
#include "assumptions.h"
#include "utils.h"

int main() {
    std::string filepath = "myfile.txt";
    std::ifstream t(filepath);
    if (!t.good()) return 1;
    std::stringstream buffer;
    buffer << t.rdbuf();
    std::string code = buffer.str();
    XOptimizer::Parser::Parser parser(code, filepath);
    auto res = parser.parseProgram();
    std::cout << res->toString();
    return 0;
}
