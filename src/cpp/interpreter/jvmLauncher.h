#ifndef IJVMLAUNCHER_H
#define IJVMLAUNCHER_H

#include <string>
#include <vector>
#include <cstdint>

class IJvmLauncher {
public:
    virtual ~IJvmLauncher() = default;
    virtual int launch(const std::string& className) = 0;
    virtual int launch(const std::string& className, const std::vector<uint8_t>& bytecode) = 0;
};


#endif //IJVMLAUNCHER_H
