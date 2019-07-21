package com.michaelpohl.oboetest

import android.content.res.AssetManager

class CppAdapter(val assetManager: AssetManager) {
    init {
    System.loadLibrary("native-lib")
    }

    fun getThatString(): String {
        return stringFromJNI()
    }

    fun play() {
       playFromJNI(assetManager)
    }

    private external fun stringFromJNI(): String
    private external fun playFromJNI(assetManager: AssetManager)

}
