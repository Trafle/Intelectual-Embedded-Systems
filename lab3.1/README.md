# Presentation

## Method
```kotlin
fun fermatFactorization(n: Int): List<Int>? {
    // У функції fermatFactorization з аргументом n, відразу робимо перевірку, на те чи число парне. Якщо так - повертаємо два фактори [2, n / 2]
    if (n % 2 == 0) return listOf(2, n / 2)
    if (n <= 0) return null

    var a = ceil(sqrt(n.toDouble()))
    var b = 0.0

    // Далі ми знаходимо корінь з n (назвемо його a) та, якщо це ціле число, то повертаємо два фактори - [a, a].
    // if n is a perfect root, then both its square roots are its factors
    if (a * a == n.toDouble()) return listOf(a.toInt(), a.toInt())

    // Якщо ж це число неціле, то шукаємо таке ціле число a (що більше за теперішнє) котре за формулою a^2 - n дасть число з котрого можна здобути цілий корінь
    while(true) {
        val b1 = a * a - n
        b = floor(sqrt(b1))
        // Цей цілий корінь назвемо b.
        if (b1 == b * b) break else a++
    }

    // Фактори, котрі функція повинна повернути знаходяться за формулами a + b та a - b. (виводиться математично з n = a^2 + b^2)
    return listOf((a - b).toInt(), (a + b).toInt())
}
```

## Screenshots:
![Big](pictures/big.png)
![Prime](pictures/primeNum.png)
