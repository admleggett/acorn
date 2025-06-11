#ifndef SYSTEMJVMLAUNCHER_H
#define SYSTEMJVMLAUNCHER_H

#include "jvmLauncher.h"

class SystemJvmLauncher : public IJvmLauncher {
public:
    SystemJvmLauncher() = default;
    ~SystemJvmLauncher() override = default;

    int launch(const std::string& className) override {
        // Use the system command to launch the JVM with the specified class name
        int result = std::system(("java " + className).c_str());
        return result == 0 ? 0 : 1;
    }
};

#endif //SYSTEMJVMLAUNCHER_H
