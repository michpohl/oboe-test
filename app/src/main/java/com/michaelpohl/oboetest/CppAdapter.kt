package com.michaelpohl.oboetest

class CppAdapter {
    init {
    System.loadLibrary("oboePlayer")
    }

    fun getThatString(): String {
        return stringFromJNI()
    }

    external fun stringFromJNI(): String

}