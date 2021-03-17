package ua.kpi.comsys.factorio

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import com.google.android.material.textfield.TextInputEditText
import kotlin.math.ceil
import kotlin.math.floor
import kotlin.math.sqrt

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val input = findViewById<TextInputEditText>(R.id.inputField)
        val output = findViewById<TextView>(R.id.outputText)
        val calcBut = findViewById<Button>(R.id.calcBut)

        calcBut.setOnClickListener { v ->
            val original = input.text.toString().toInt()
            val factorsArray = fermatFactorization(original)

            if (factorsArray == null) {
                Toast.makeText(applicationContext,"bad argument",Toast.LENGTH_SHORT).show()
                output.text = original.toString()
            } else {
                output.text = factorsArray.joinToString()
            }
        }

    }
}

fun fermatFactorization(n: Int): List<Int>? {
    if (n % 2 == 0) return listOf(2, n / 2)
    if (n <= 0) return null

    var a = ceil(sqrt(n.toDouble()))
    var b = 0.0

    // if n is a perfect root, then both its square roots are its factors
    if (a * a == n.toDouble()) return listOf(a.toInt(), a.toInt())

    while(true) {
        val b1 = a * a - n
        b = floor(sqrt(b1))
        if (b1 == b * b) break else a++
    }

    return listOf((a - b).toInt(), (a + b).toInt())
}
