#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "get_walltime.h"

void matrix_multiply(double **A, double **B, double **C, size_t N) {

  for (size_t i = 0; i < N; ++i) {
    for (size_t j = 0; j < N; ++j) {
      for (size_t k = 0; k < N; ++k) {
        C[i][j] += A[i][k] * B[k][j];
      }
    }
  }

}

double timed_matrix_mutliply(double **A, double **B, double **C, size_t N, bool verbose=false) {

  // for recording elapsed time
  double t_start, t_finish;

  // do matrix multiply and time it
  get_walltime(&t_start);
  matrix_multiply(A,B,C,N);
  get_walltime(&t_finish);

  if(verbose) {
    // print elapsed time
    printf("%f\n",t_finish-t_start);

    // print matrix multiplication result
    for(size_t i = 0; i < N; ++i) {
      for(size_t j = 0; j < N; ++j) {
        printf("%f ", C[i][j]);
      }
      printf("\n");
    }

  }

  // return elapsed time
  return t_finish-t_start;

}

int main(int argc, char *argv[]) {

  FILE *f;

  if (argc >= 2) {
    f = fopen(argv[1], "w");
  } else {
    printf("missing argument: csv output filename");
    return 1;
  }

  // write header row
  fprintf(f, "N,time\n");

  // seed random number generator
  // for repeatability
  srand(0);

  size_t reps = 15;

  double res;
  for(size_t N=1;N<2048;N+=20) {

    //setup
    printf("N=%lu\n",N);

    //setup A and B matrices
    double **A = new double*[N];
    double **B = new double*[N];
    for(size_t i = 0; i < N; ++i) {
      A[i] = new double[N];
      B[i] = new double[N];
      for(size_t j = 0; j < N; ++j) {
        A[i][j] = (double)rand() / (double)RAND_MAX ;
        B[i][j] = (double)rand() / (double)RAND_MAX ;
      }
    }

    // setup C matrix
    // setup outside of matrix_multiply so that memory allocation isn't timed
    double **C = new double*[N];
    for(size_t i = 0; i < N; ++i) {
      C[i] = new double[N];
      std::fill(C[i], C[i]+N, 0);
    }

    for(size_t r=0; r<reps; ++r) {

      res = timed_matrix_mutliply(A,B,C,N);
      // write data row
      fprintf(f, "%lu,%f\n", N, res);
      // progress bar
      fprintf(stderr,".");

    }

    // cleanup
    fprintf(stderr,"\n");

    for(size_t i = 0; i < N; ++i) {
      free(A[i]);
      free(B[i]);
      free(C[i]);
    }
    free(A);
    free(B);
    free(C);

  }

  fclose(f);

}
