#include "labLib.h"

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

    // Calculating correlation functions
    Point *xtOfsset = offsetFun(xt, tau, N);
    Point *autoCor = mutualCorrelation(xt, xtOfsset, N);

    Point *xtWithDifferentHarmonics = makeFunction(100, W, N);
    Point *mutCor = mutualCorrelation(xt, xtWithDifferentHarmonics, N);

    // Write calculations to file
    writeCalcsToFile(autoCor, N, "Auto_correlation_function");
    writeCalcsToFile(mutCor, N, "Mutual_correlation_function");
    return 0;
}
