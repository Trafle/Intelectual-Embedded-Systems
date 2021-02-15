#include <iostream>
#include <fstream>
#include <omp.h>
#include <random>

// It's better to just use std::stoi
int convertToInt(char* a, int size) {
    // Always init your variables. For this occasion it doesn't matter but it will save you a lot of time 
    int i; 
    std::string s = ""; 
    for (i = 0; i < size; i++) { 
        s = s + a[i]; 
    } 
    // C-style cast. Use static_cast<> 
    return (int) std::stoi(s); 
} 

struct Point {
    
    double x;
    double y;
    // There is no need for this constructor. Compiler automatically generates it
    Point (float xCoor = 0, float yCoor = 0) {
        x = xCoor;
        y = yCoor;
    }
};

// Inconsistent formatting ") {"
int main(int argc, char** argv){

    // init variables
    int n = 10; // Harmonica
    int W = 1500; // Critical frequency
    int N = 256; // Discrete vidclick
    if(argc == 4) {
        n = convertToInt(argv[1], sizeof(argv[1]));
        W = convertToInt(argv[2], sizeof(argv[2]));
        N = convertToInt(argv[3], sizeof(argv[3]));
    }

    // Init randomizer
    std::default_random_engine generator;
    std::uniform_real_distribution<double> amp_and_fi(0,1);

    // Init array of Point's
    const float T = 0.15;  // Time of signal in seconds
    const double stepSize = 0.000005;
    // Inconsistent formatting "T / stepSize"
    const int amountOfPoints = T/stepSize;
    
    // For this case it doesn't matter but it's good practice to init your arrays. 
    // It can save you from some debugging and if you care about speed, compilers can easily optimise initialization
    // Just put "Point xt [amountOfPoints]{};" or "Point xt [amountOfPoints] = {};"
    Point xt [amountOfPoints];
    
    // Inconsistent formatting "W / n" and "for( "
    // Iterate through the several harmonics
    for( int w = W/n; w <= W; w += W/n) {
        double A = amp_and_fi(generator);
        double fi = amp_and_fi(generator);

        // Iterate through one harmonica 
        for (int t = 0; t < amountOfPoints; t += 1) {
            double x = t * stepSize;
            xt[t].x = x;
            double y = A * sin(w * x + fi);
            xt[t].y += y;
        }
    }   

    // Calculating mathematical expectation
    // You can use standart algorithms for it, but it's ok
    // initialize sumOfPoints
    double sumOfPoints;
    for(int i = 0; i < amountOfPoints; i++) {
        sumOfPoints += xt[i].y;
    }
    const double mathematicalExpectation = sumOfPoints / amountOfPoints;

    // Calculating dispersion
    double sumOfDiffs;
    for(int i = 0; i < amountOfPoints; i++) {
        sumOfDiffs += (xt[i].y - mathematicalExpectation) * (xt[i].y - mathematicalExpectation);
    }
    const double dispersion = sumOfDiffs / amountOfPoints;

    std::cout << "Mathematical Expectation: " << mathematicalExpectation << '\n';
    std::cout << "Dispersion: " << dispersion << '\n';    

    // Write calculations to file
    std::ofstream dataSheet;
    dataSheet.open ("data.xlsx");
    // it's good practice to check if file is opened because of permissions and other stuff. 
    for(int i = 0; i < amountOfPoints; i++) {
        dataSheet << xt[i].x << "\t" << xt[i].y << '\n';
    }

    return 0;
}

