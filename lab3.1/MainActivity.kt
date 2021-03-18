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
    // У функції fermatFactorization з аргументом n, відразу робимо перевірку,
    // на те чи число парне. Якщо так - повертаємо два фактори [2, n / 2]
    if (n % 2 == 0) return listOf(2, n / 2)
    if (n <= 0) return null

    var a = ceil(sqrt(n.toDouble()))
    var b = 0.0

    // Далі ми знаходимо корінь з n (назвемо його a) та, якщо це ціле число,
    // то повертаємо два фактори - [a, a].
    if (a * a == n.toDouble()) return listOf(a.toInt(), a.toInt())

    // Якщо ж це число неціле, то шукаємо таке ціле число a (що більше за теперішнє)
    // котре за формулою a^2 - n дасть число з котрого можна здобути цілий корінь
    while(true) {
        val b1 = a * a - n
        b = floor(sqrt(b1))
        // Цей цілий корінь назвемо b.
        if (b1 == b * b) break else a++
    }

    // Фактори, котрі функція повинна повернути знаходяться за формулами
    // a + b та a - b. (виводиться математично з n = a^2 + b^2)
    return listOf((a - b).toInt(), (a + b).toInt())
}
