#include <iostream>
#include <fstream>
#include <omp.h>
#include <random>
#include <math.h>

int convertToInt(char *a, int size)
{
  int i;
  std::string s = "";
  for (i = 0; i < size; i++)
  {
    s = s + a[i];
  }
  return (int)std::stoi(s);
}

struct Point
{
  double x = 0.0;
  double y = 0.0;

  Point(double xCoor = 0.0, double yCoor = 0.0)
  {
    x = xCoor;
    y = yCoor;
  }
};

Point *makeFunction(int n, int W, int N)
{
  Point *xt = reinterpret_cast<Point *>(malloc(sizeof(Point) * N + 1));

  // Init randomizer
  std::default_random_engine generator;
  std::uniform_real_distribution<double> amp_and_fi(0, 1);

  // Iterate through the several harmonics
  for (int w = W / n; w <= W; w += W / n)
  {
    double A = amp_and_fi(generator);
    double fi = amp_and_fi(generator);

    // Iterate through one harmonica
    for (int x = 0; x < N; x++)
    {
      xt[x].x = (double)x;
      double y = A * sin(w * x + fi);
      xt[x].y += y;
    }
  }
  return xt;
}

double calcMathExp(Point *xt, int N)
{
  double sumOfPoints = 0.0;

  for (int i = 0; i < N; i++)
  {
    sumOfPoints += xt[i].y;
  }
  return sumOfPoints / N;
}

double calcDispersion(Point *xt, int N, double mathematicalExpectation)
{
  double sumOfDiffs = 0.0;
  for (int i = 0; i < N; i++)
  {
    sumOfDiffs += (xt[i].y - mathematicalExpectation) * (xt[i].y - mathematicalExpectation);
  }
  return sumOfDiffs / N;
}

void writeCalcsToFile(Point *xt, int N, std::string fileName)
{
  std::ofstream dataSheet;
  dataSheet.open("lab2.1/" + fileName + ".xlsx");
  for (int i = 0; i < N; i++)
  {
    dataSheet << xt[i].x << "\t" << xt[i].y << '\n';
  }
  dataSheet.close();
}

Point *mutualCorrelation(Point *firstFunc, Point *secondFunc, int N)
{
  Point *mutCorFunVals = reinterpret_cast<Point *>(malloc(sizeof(Point) * N + 1));
  double mathExpFirstFun = calcMathExp(firstFunc, N);
  double mathExpSecondFun = calcMathExp(secondFunc, N);
  double dispFirstFun = calcDispersion(firstFunc, N, mathExpFirstFun);
  double dispSecondFun = calcDispersion(secondFunc, N, mathExpSecondFun);

  // Loop through function values
  for (int x = 0; x < N; x++)
  {
    mutCorFunVals[x] = Point(x, ((firstFunc[x].y - mathExpFirstFun) * (secondFunc[x].y - mathExpSecondFun)) / ((N - 1) * sqrt(dispFirstFun) * sqrt(dispSecondFun)));
  }
  return mutCorFunVals;
}

Point *offsetFun(Point *xt, double Tau, int N)
{
  Point *offsetFunVals = reinterpret_cast<Point *>(malloc(sizeof(Point) * N + 1));

  for (int i = 0; i < N; i++)
  {
    offsetFunVals[i].x = xt[i].x + Tau;
    offsetFunVals[i].y = xt[i].y;
  }

  return offsetFunVals;
}