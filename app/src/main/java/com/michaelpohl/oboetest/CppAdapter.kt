package com.michaelpohl.oboetest

class CppAdapter {
    init {
    System.loadLibrary("oboePlayer")
    }

    fun getThatString(): String {
        return stringFromJNI()
    }

    private external fun stringFromJNI(): String

}