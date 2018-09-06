#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

double **matrix_multiply(double** A, double** B, int N) {

  double **C = new double*[N];
  for(int i = 0; i < N; ++i) {
    C[i] = new double[N];
    std::fill(C[i], C[i]+N, 0);
  }

  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      for (int k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

  return C;
}

int main() {

  int N = 10;
  double **A = new double*[N];
  double **B = new double*[N];
  for(int i = 0; i < N; ++i) {
    A[i] = new double[N];
    B[i] = new double[N];
    for(int j = 0; j < N; ++j) {
      A[i][j] = (double)rand() / (double)RAND_MAX ;
      B[i][j] = (double)rand() / (double)RAND_MAX ;
    }
  }
  double **C = matrix_multiply(A,B,N);

  for(int i = 0; i < N; ++i) {
    for(int j = 0; j < N; ++j) {
      printf("%f ", C[i][j]);
    }
    printf("\n");
  }
}
