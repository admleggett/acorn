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

    int launch(const std::string& className, const std::vector<uint8_t>& byteCode) override {
        // This method is not implemented for SystemJvmLauncher
        return -1; // Indicating that this method is not supported
    }
};

#endif //SYSTEMJVMLAUNCHER_H
