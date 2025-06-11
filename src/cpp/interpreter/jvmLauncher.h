#ifndef IJVMLAUNCHER_H
#define IJVMLAUNCHER_H

#include <string>

class IJvmLauncher {
public:
    virtual ~IJvmLauncher() = default;
    virtual int launch(const std::string& className) = 0;
};


#endif //IJVMLAUNCHER_H
