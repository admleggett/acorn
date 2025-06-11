#include "parser.h"

#include <iostream>

#include "ast/intLiteralNode.h"
#include "ast/printNode.h"

Parser::Parser(const std::vector<std::string>& tokens) : tokens_(tokens), pos_(0) {}

std::vector<std::unique_ptr<ASTNode>> Parser::parse() {
    std::vector<std::unique_ptr<ASTNode>> statements;

    //print the tokens size for debugging
    //std::cout << "Parsing " << tokens_.size() << " tokens." << std::endl;


    while (pos_ + 1 < tokens_.size()) {
        if (tokens_[pos_] != "print")
            throw std::runtime_error("Syntax error: expected 'print <int>'");
        int value = std::stoi(tokens_[pos_ + 1]);
        auto intNode = std::make_unique<IntLiteralNode>(value);
        statements.push_back(std::make_unique<PrintNode>(std::move(intNode)));
        pos_ += 2;
    }
    if (pos_ != tokens_.size())
        throw std::runtime_error("Syntax error: incomplete statement at end");
    return statements;
}
