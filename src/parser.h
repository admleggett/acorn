/**
 * @file parser.h
 * @brief Declaration of the Parser class.
 *
 * This file declares the Parser class, which is responsible for parsing a sequence of tokens
 * into an abstract syntax tree (AST).
 */
#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <string>
#include <memory>
#include "ast/astNode.h"

class Parser {
public:
    explicit Parser(const std::vector<std::string>& tokens);
    std::vector<std::unique_ptr<ASTNode>> parse();
private:
    const std::vector<std::string> tokens_;
    size_t pos_;
};



#endif //PARSER_H
