//
// Created by Michael on 2019-07-13.
//
#include <string.h>
#include <jni.h>

extern "C"
JNIEXPORT jstring JNICALL
Java_com_michaelpohl_oboetest_CppAdapter_stringFromJNI(JNIEnv *env,
                                                 jobject thiz) {

    return (env) -> NewStringUTF("Hello from JNI !");
}
