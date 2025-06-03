#include "jniJvmLauncher.h"
#include <jni.h>
#include <iostream>

int JniJvmLauncher::launch(const std::string& className) {

    //console out invocation of the JVM via JNI
    //std::cout << "Launching JVM with class: " << className << std::endl;

    JavaVM* jvm;
    JNIEnv* env;

    JavaVMInitArgs vm_args;
    JavaVMOption options[1];
    options[0].optionString = const_cast<char*>("-Djava.class.path=.");
    vm_args.version = JNI_VERSION_1_8; // Use the appropriate version
    vm_args.nOptions = 1;
    vm_args.options = options;
    vm_args.ignoreUnrecognized = false;

    // Create the JVM
    jint res = JNI_CreateJavaVM(&jvm, (void**)&env, &vm_args);
    if (res != JNI_OK) {
        return -1; // Failed to create JVM
    }

    // Find the class
    jclass cls = env->FindClass(className.c_str());
    if (cls == nullptr) {
        jvm->DestroyJavaVM();
        return -1; // Class not found
    }

    // Call the main method
    jmethodID mainMethod = env->GetStaticMethodID(cls, "main", "([Ljava/lang/String;)V");
    if (mainMethod == nullptr) {
        jvm->DestroyJavaVM();
        return -1; // Main method not found
    }

    jobjectArray args = env->NewObjectArray(0, env->FindClass("java/lang/String"), nullptr);

    env->CallStaticVoidMethod(cls, mainMethod, args);

    // Destroy the JVM
    jvm->DestroyJavaVM();

    return 0; // Success
}
