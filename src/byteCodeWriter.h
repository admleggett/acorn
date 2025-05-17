#ifndef BYTECODEWRITER_H
#define BYTECODEWRITER_H

#include <string>
#include <vector>

class ByteCodeWriter {
public:
    explicit ByteCodeWriter(std::string className);
    void write(const std::vector<std::string>& tokens, const std::string& outputFile) const;
private:
    std::string className_;
};

#endif //BYTECODEWRITER_H
