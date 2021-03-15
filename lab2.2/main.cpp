#include <complex>
#include <iostream>
#include <valarray>
#include "labLib.h"

const double PI = 3.141592653589793238460;

typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray;

// Cooley–Tukey FFT (in-place, divide-and-conquer)
// Higher memory requirements and redundancy although more intuitive
void fft(CArray &x)
{
  const size_t N = x.size();
  if (N <= 1)
    return;

  // divide
  CArray even = x[std::slice(0, N / 2, 2)];
  CArray odd = x[std::slice(1, N / 2, 2)];

  // conquer
  fft(even);
  fft(odd);

  // combine
  for (size_t k = 0; k < N / 2; ++k)
  {
    Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
    x[k] = even[k] + t;
    x[k + N / 2] = even[k] - t;
  }
}

void ifft(CArray &x)
{
  x = x.apply(std::conj);

  // forward fft
  fft(x);

  // conjugate the complex numbers again
  x = x.apply(std::conj);

  // scale the numbers
  x /= x.size();
}

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

  const Point *xt = makeFunction(n, W, N);

  Complex signal[N];

  for (std::size_t k = 0; k < N; k++)
  {
    Complex complexNum(xt[k].y, 1);
    signal[k] = complexNum;
  }

  std::cout << "here: " << signal[1] << std::endl;
  CArray data(signal, N);

  // forward fft
  fft(data);

  Point *toShow = makeFunction(n, W, N);
  for (std::size_t i = 0; i < N; i++)
  {
    toShow[i].y = 2 * std::abs(data[i]) / N;
  }

  writeCalcsToFile(toShow, N, "transformed");

  return 0;
}