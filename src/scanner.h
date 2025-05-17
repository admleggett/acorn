#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>

class Scanner {
public:
    explicit Scanner(std::string source);
    std::vector<std::string> tokenize();
private:
    std::string source_;
};

#endif //SCANNER_H
