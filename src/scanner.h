/**
 * @file scanner.h
 * @brief Declaration of the Scanner class for tokenizing source code.
 *
 * This file declares the Scanner class, which is responsible for tokenizing
 * a given source code string into a vector of tokens.
 */
#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

class Scanner {
public:
    explicit Scanner(std::string source);
    [[nodiscard]] std::vector<std::string> tokenize() const;
private:
    std::string source_;
};

#endif //SCANNER_H
