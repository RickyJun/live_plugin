package com.rick.live.live_plugin
import java.util.*
object StatusBarUtils {


    fun getRandomAlphaString(length: Int): String {
        val base = "abcdefghijklmnopqrstuvwxyz"
        val random = Random()
        val sb = StringBuilder()
        for (i in 0 until length) {
            val number = random.nextInt(base.length)
            sb.append(base[number])
        }
        return sb.toString()
    }

    fun getRandomAlphaDigitString(length: Int): String {
        val base = "abcdefghijklmnopqrstuvwxyz0123456789"
        val random = Random()
        val sb = StringBuilder()
        for (i in 0 until length) {
            val number = random.nextInt(base.length)
            sb.append(base[number])
        }
        return sb.toString()
    }
}