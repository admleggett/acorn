#include "scanner.h"
#include <fstream>
#include <sstream>

Scanner::Scanner(std::string source) : source_(std::move(source)) {}

std::vector<std::string> Scanner::tokenize() const
{
    std::vector<std::string> tokens;
    std::ifstream file(source_);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open source file: " + source_);
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        // verify that line contains supported syntax print <integer>
        if (line.find("print") != 0) {
            throw std::runtime_error("Unsupported syntax in line: " + line);
        }
        std::string token;
        while (iss >> token) {
            // Skip empty tokens
            if (!token.empty()) {
                tokens.push_back(token);
            }
        }
    }

    return tokens;
}
