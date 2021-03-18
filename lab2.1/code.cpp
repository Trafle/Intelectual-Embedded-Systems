#include "labLib.h"
#include <cmath>
#include <complex>
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{
    // init variables
    int n = 10;   // Harmonica
    int W = 1500; // Critical frequency
    int N = 256;  // Discrete vidclick
    // The check is conducted to assert having all the three needed arguments
    // if the program is going to be used with a different data set
    if (argc == 4)
    {
        n = convertToInt(argv[1], sizeof(argv[1]));
        W = convertToInt(argv[2], sizeof(argv[2]));
        N = convertToInt(argv[3], sizeof(argv[3]));
    }

    // Init array of Point's
    Point *xt = makeFunction(n, W, N);

    std::complex<double> complexNum(0.0, 1.0);
    std::complex<double> Furr[N];
    memset(Furr, 0, N * sizeof(std::complex<double>));

    for (std::size_t i = 0; i < N; i++)
    {
        Furr[i] = 0;
    }

    double WPK[N][N];

    std::cout << "Ініціюємо масив точок з першої лабораторної: xt, властивості кожного елемента якого включають координати x та y даного елемента.\n";
    std::cout << "Ініціюємо масив Furr[] довжиною N. Він відповідає рядкам матриці, котрі ми будемо колапсувати в акумульовані числа в даному масиві.\n";
    std::cout << "Ітеруємося через матрицю розміром N x N з рядками p та колонками k. У кожній клітині матриці \n";
    std::cout << "Для знаходження значення Furr[p] (колапсування рядка в число), для кожної клітинки обчислюємо інкремент за формулою \n";
    std::cout << "xt[k].y * ((cos(2 * M_PI * p * k / N)) - (sin(2 * M_PI * p * k / N)) * 1i\n";
    std::cout << "Всі ці значення для кожного рядка акумулюються в Furr[]\n";
    std::cout << "Далі знаходимо модуль кожного комплексного числа, нормалізуємо за формулою y = 2 * abs(comlpexNumber / N), та виводимо результати \n";

    for (int p = 0; p < N; p++)
    {
        for (int k = 0; k < N; k++)
        {
            Furr[p] += Furr[p] + xt[k].y * ((cos(2 * M_PI * p * k / N)) - (sin(2 * M_PI * p * k / N)) * complexNum);
            WPK[p][k] = std::abs(Furr[p]);
        }
    }

    // Write the table into file
    std::ofstream wpkTable;
    wpkTable.open("lab2.1/wpkTable.txt");
    for (int i = 0; i < N; i++)
    {
        for (int k = 0; k < N; k++)
        {
            wpkTable << WPK[i][k] << ' ';
        }
        wpkTable << std::endl;
    }
    wpkTable.close();

    double A[N];
    memset(A, 0, N * sizeof(double));

    for (int i = 0; i < N; i++)
    {
        A[i] = std::abs(Furr[i]);
        A[i] = 2 * A[i] / N;
    }

    Point *toShow = makeFunction(n, W, N);
    for (int i = 0; i < N; i++)
    {
        toShow[i].y = A[i];
    }

    writeCalcsToFile(toShow, N, "complex");

    return 0;
}
