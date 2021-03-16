package ua.kpi.comsys.factorio

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.widget.Button
import android.widget.TextView
import android.widget.Toast
import com.google.android.material.textfield.TextInputEditText

class MainActivity : AppCompatActivity() {
    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)

        val input = findViewById<TextInputEditText>(R.id.inputField)
        val output = findViewById<TextView>(R.id.outputText)
        val calcBut = findViewById<Button>(R.id.calcBut)

        calcBut.setOnClickListener { v ->
            val original = input.text.toString().toInt()
            val factorsArray = factorize(original)

            if (factorsArray == null) {
                Toast.makeText(applicationContext,"wrong number",Toast.LENGTH_SHORT).show()
            } else {
                output.text = factorsArray.joinToString()
            }
        }

    }
}

fun factorize(original: Int): MutableList<Int>? {

    // Return if the input number is up to 3
    if (original == 0 || original == 1 || original == 2 || original == 3) return mutableListOf(original)
    if (original < 0) return null

    // Initiate the prime factors array
    val factors = mutableListOf<Int>()
    var changer: Int = original

    // Iterate through to half of the original number and find all prime factors
    var i: Int = 2
    while (i <= original / 2) {

        if (changer % i == 0) {
            factors.add(i)
            changer /= i
            if (changer == 1) return factors
            continue
        } else {
            i++
        }
    }

    // If found factors - return them. Otherwise - original is a prime number
    return if (factors.isEmpty()) mutableListOf(original) else factors
}
