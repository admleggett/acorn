#ifndef JNIJVMLAUNCHER_H
#define JNIJVMLAUNCHER_H

#include "jvmLauncher.h"

class JniJvmLauncher : public IJvmLauncher {

public:
    JniJvmLauncher() = default;
    ~JniJvmLauncher() override = default;

    int launch(const std::string& className) override;
};



#endif //JNIJVMLAUNCHER_H
