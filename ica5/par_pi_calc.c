/***************************************************************************
 * FILE: par_pi_calc.c
 * DESCRIPTION:
 *   Parallel pi Calculation - C Version
 *   This program calculates pi using a "dartboard" algorithm.  See
 *   Fox et al.(1988) Solving Problems on Concurrent Processors, vol.1
 *   page 207.
 * AUTHOR: unknown
 * REVISED: 09/26/12 Matthew Andres Moreno and Ian Whalen
***************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>

void srandom (unsigned seed);
double dboard (int darts);

#define ROUNDS 100    	/* number of times "darts" is iterated */

int main(int argc, char *argv[])
{
    const int ROOT = 0;
    double runtime = MPI_Wtime();
    MPI_Init(&argc, &argv);

    int divvy = atoi(argv[1]); /* divvy up rounds between procs? */
    int darts = atoi(argv[2]); /* number of throws at dartboard */

    double pi;          	/* average of pi after "darts" is thrown */
    double avepi;       	/* average pi value for all iterations */
    int i, n;

    int rank, size;

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    srandom(rank + 1);            /* seed the random number generator */

    MPI_Comm_size(MPI_COMM_WORLD, &size);

    avepi = 0;

    // divide up rounds between processes...
    int my_rounds = divvy ? ROUNDS / size : ROUNDS;
    for (i = 0; i < my_rounds; i++) {
       /* Perform pi calculation on serial processor */
       pi = dboard(darts);
       avepi += pi;
   }
   // ... if divvying and division is uneven, 1 extra job for n=remainder procs
   if (divvy && rank <= ROUNDS % size) {
      pi = dboard(darts);
      avepi += pi;
      my_rounds++;
   }

   avepi /= my_rounds;

   double result = 0;
   MPI_Reduce(&avepi, &result, 1, MPI_DOUBLE, MPI_SUM, ROOT, MPI_COMM_WORLD);
   result /= size;

   if (rank == ROOT) {
       printf("Average value of pi = %10.8f\n", result);
       runtime = MPI_Wtime() - runtime;
       printf("This took %f seconds.\n", runtime);
   }

    printf("\nReal value of PI: 3.1415926535897 \n");
    MPI_Finalize();
}


/*****************************************************************************
 * dboard
 *****************************************************************************/
#define sqr(x)	((x)*(x))
long random(void);

double dboard(int darts)
{
   double x_coord,       /* x coordinate, between -1 and 1  */
          y_coord,       /* y coordinate, between -1 and 1  */
          pi,            /* pi  */
          r;             /* random number scaled between 0 and 1  */
   int score,            /* number of darts that hit circle */
       n;
   unsigned int cconst;  /* must be 4-bytes in size */
/*************************************************************************
 * The cconst variable must be 4 bytes. We check this and bail if it is
 * not the right size
 ************************************************************************/
   if (sizeof(cconst) != 4) {
      printf("Wrong data size for cconst variable in dboard routine!\n");
      printf("See comments in source file. Quitting.\n");
      exit(1);
      }
   /* 2 bit shifted to MAX_RAND later used to scale random number between 0 and 1 */
   cconst = 2 << (31 - 1);
   score = 0;

/***********************************************************************
 * Throw darts at board.  Done by generating random numbers
 * between 0 and 1 and converting them to values for x and y
 * coordinates and then testing to see if they "land" in
 * the circle."  If so, score is incremented.  After throwing the
 * specified number of darts, pi is calculated.  The computed value
 * of pi is returned as the value of this function, dboard.
 ************************************************************************/

   for (n = 1; n <= darts; n++) {
      /* generate random numbers for x and y coordinates */
      r = (double)random()/cconst;
      x_coord = (2.0 * r) - 1.0;
      r = (double)random()/cconst;
      y_coord = (2.0 * r) - 1.0;

      /* if dart lands in circle, increment score */
      if ((sqr(x_coord) + sqr(y_coord)) <= 1.0)
         score++;
      }

   /* calculate pi */
   pi = 4.0 * (double)score/(double)darts;
   return(pi);
}
