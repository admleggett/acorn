#ifndef JNIJVMLAUNCHER_H
#define JNIJVMLAUNCHER_H

#include "jvmLauncher.h"
#include <iostream>

class JniJvmLauncher final : public IJvmLauncher {

public:
    JniJvmLauncher() = default;
    ~JniJvmLauncher() override = default;

    int launch(const std::string& className) override{
        return doLaunch(className, std::vector<uint8_t>{});
    }
    int launch(const std::string& className, const std::vector<uint8_t>& bytecode) override {
        return doLaunch(className, bytecode);
    }
private:
    int doLaunch(const std::string& className, const std::vector<uint8_t>& bytecode);
};



#endif //JNIJVMLAUNCHER_H
