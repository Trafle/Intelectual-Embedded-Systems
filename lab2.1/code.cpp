#include "labLib.h"
#include <cmath>
#include <complex>
#include <iostream>

int main(int argc, char **argv)
{
    // init variables
    int n = 10;       // Harmonica
    int W = 1500;     // Critical frequency
    int N = 256;      // Discrete vidclick
    double tau = 5.0; // The offset
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

    // Point Furr[256] = {0};
    std::complex<int> complexNum(0, 1);
    std::complex<double> Furr[256] = {0};

    for (int p = 0; p < N; p++)
    {
        for (int k = 0; k < N; k++)
        {
            Furr[p] += xt[k].y * (cos(2 * M_PI * p * k / N) - sin(2 * M_PI * p * k / N) * complexNum.imag());
        }
    }

    double A[256] = {0};

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

// void plotFunction(std::complex complexNum)
// {
//     std::abs(comlexNum);
// }