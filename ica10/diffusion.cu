
#include <iostream>
#include <fstream>
#include <string>
#include <stdio.h>
#include <cmath>
#include <cassert>
#include <cuda_runtime.h>
#include "get_walltime.h"
using namespace std;

const unsigned int NG = 2;
const unsigned int BLOCK_DIM_X = 256;

__constant__ float c_a, c_b, c_c, c_dt, c_dx;

/********************************************************************************
  Error checking function for CUDA
 *******************************************************************************/
// Convenience function for checking CUDA runtime API results
// can be wrapped around any runtime API call. No-op in release builds.
//https://github.com/parallel-forall/code-samples/blob/master/series/cuda-cpp/finite-difference/finite-difference.cu
inline
cudaError_t checkCuda(cudaError_t result)
{
#if defined(DEBUG) || defined(_DEBUG)
  if (result != cudaSuccess) {
    fprintf(stderr, "CUDA Runtime Error: %s\n", cudaGetErrorString(result));
    assert(result == cudaSuccess);
  }
#endif
  return result;
}

/********************************************************************************
  Do one diffusion step, on the host in host memory
 *******************************************************************************/
void host_diffusion(float* u, float *u_new, const unsigned int n,
     const float dx, const float dt){

  //First, do the diffusion step on the interior points
  for(int i = NG; i < n-NG;i++){
    u_new[i] = u[i] + dt/(dx*dx) *(
                    - 1./12.f* u[i-2]
                    + 4./3.f * u[i-1]
                    - 5./2.f * u[i]
                    + 4./3.f * u[i+1]
                    - 1./12.f* u[i+2]);
  }

  //Apply the dirichlet boundary conditions
  u_new[0] = -u_new[NG+1];
  u_new[1] = -u_new[NG];

  u_new[n-NG]   = -u_new[n-NG-1];
  u_new[n-NG+1] = -u_new[n-NG-2];
}
/********************************************************************************
  Do one diffusion step, with CUDA
 *******************************************************************************/
__global__
void cuda_diffusion(
    float* u,
    float *u_new,
    const unsigned int n
  ){

  int i = threadIdx.x;

  if (i >= NG && i < n - NG) {
    //Do the diffusion
     u_new[i] = u[i] + c_dt/(c_dx*c_dx) *(
                    - c_a * u[i-2]
                    + c_b * u[i-1]
                    - c_c * u[i]
                    + c_b * u[i+1]
                    - c_a * u[i+2]);
  //Apply the dirichlet boundary conditions
  //HINT: Think about which threads will have the data for the boundaries
  } else if (i == 0) {
    u_new[0] = -u_new[NG+1];
  } else if (i == 1) {
    u_new[1] = -u_new[NG];
  } else if (i == n-NG) {
    u_new[n-NG]   = -u_new[n-NG-1];
  } else if (i == n-NG+1) {
    u_new[n-NG+1] = -u_new[n-NG-2];
  }
}

/********************************************************************************
  Do one diffusion step, with CUDA, with shared memory
 *******************************************************************************/
__global__
void shared_diffusion(float* u, float *u_new, const unsigned int n){

  //Allocate the shared memory
  //FIXME

  //Fill shared memory with the data needed from global memory
  //HINT:
  //What data does each block need from global memory?
  //When do the threads in the block need to sync?
  //FIXME

  //Do the diffusion
  //FIXME

  //Apply the dirichlet boundary conditions
  //HINT: Think about which threads will have the data for the boundaries
  //FIXME
}

/********************************************************************************
  Dump u to a file
 *******************************************************************************/
void outputToFile(string filename, float* u, unsigned int n){

  ofstream file;
  file.open(filename.c_str());
  file.precision(8);
  file << std::scientific;
  for(int i =0; i < n;i++){
    file<<u[i]<<endl;
  }
  file.close();
};

/********************************************************************************
  main
 *******************************************************************************/
int main(int argc, char** argv){

  //Number of steps to iterate
  // const unsigned int n_steps = 10;
  const unsigned int n_steps = 100;
  // const unsigned int n_steps = 1000000;

  //Whether and how ow often to dump data
  const bool outputData = true;
  const unsigned int outputPeriod = n_steps/10;

  //Size of u
  //const unsigned int n = (1<<11) +2*NG;
  const unsigned int n = (1<<16) +2*NG;

  //Block and grid dimensions
  const unsigned int blockDim = BLOCK_DIM_X;
  const unsigned int gridDim = (n-2*NG)/blockDim;

  //Physical dimensions of the domain
  const float L = 2*M_PI;
  const float dx = L/(n-2*NG-1);
  const float dt = 0.25*dx*dx;

  //Create constants for 6th order centered 2nd derivative
  float const_a = 1.f/12.f * dt/(dx*dx);
  float const_b = 4.f/3.f  * dt/(dx*dx);
  float const_c = 5.f/2.f  * dt/(dx*dx);

  //Copy these the cuda constant memory
  checkCuda(
    cudaMemcpyToSymbol(c_a, &const_a, sizeof(float), 0, cudaMemcpyHostToDevice)
  );
  checkCuda(
    cudaMemcpyToSymbol(c_b, &const_b, sizeof(float), 0, cudaMemcpyHostToDevice)
  );
  checkCuda(
    cudaMemcpyToSymbol(c_c, &const_c, sizeof(float), 0, cudaMemcpyHostToDevice)
  );
  checkCuda(
    cudaMemcpyToSymbol(c_dt, &dt, sizeof(float), 0, cudaMemcpyHostToDevice)
  );
  checkCuda(
    cudaMemcpyToSymbol(c_dx, &dx, sizeof(float), 0, cudaMemcpyHostToDevice)
  );

  //iterator, for later
  int i;

  //Create cuda timers
	cudaEvent_t start, stop;
	cudaEventCreate(&start);
	cudaEventCreate(&stop);

  //Timing variables
  float milliseconds;
  double startTime,endTime;

  //Filename for writing
  char filename[256];

  //Allocate memory for the initial conditions
  float* initial_u = new float[n];

  //Initialize with a periodic sin wave that starts after the left hand
  //boundaries and ends just before the right hand boundaries
  for( i = NG; i < n-NG; i++){
    initial_u[i] = sin( 2*M_PI/L*(i-NG)*dx);
  }
  //Apply the dirichlet boundary conditions
  initial_u[0] = -initial_u[NG+1];
  initial_u[1] = -initial_u[NG];

  initial_u[n-NG]   = -initial_u[n-NG-1];
  initial_u[n-NG+1] = -initial_u[n-NG-2];

/********************************************************************************
  Test the host kernel for diffusion
 *******************************************************************************/

  //Allocate memory in the host's heap
  float* host_u  = new float[n];
  float* host_u2 = new float[n];//buffer used for u_new

  //Initialize the host memory
  for( i = 0; i < n; i++){
    host_u[i] = initial_u[i];
  }

  outputToFile("data/host_uInit.dat",host_u,n);


  get_walltime(&startTime);
  //Perform n_steps of diffusion
  for( i = 0 ; i < n_steps; i++){

    if(outputData && i%outputPeriod == 0){
      sprintf(filename,"data/host_u%08d.dat",i);
      outputToFile(filename,host_u,n);
    }

    host_diffusion(host_u,host_u2,n,dx,dt);

    //Switch the buffer with the original u
    float* tmp = host_u;
    host_u = host_u2;
    host_u2 = tmp;

  }
  get_walltime(&endTime);

  cout<<"Host function took: "<<(endTime-startTime)*1000./n_steps<<"ms per step"<<endl;

  outputToFile("data/host_uFinal.dat",host_u,n);

/********************************************************************************
  Test the cuda kernel for diffusion
 *******************************************************************************/
  //Allocate a copy for the GPU memory in the host's heap
  float* cuda_u  = new float[n];

  //Initialize the cuda memory
  for( i = 0; i < n; i++){
    cuda_u[i] = initial_u[i];
  }
  outputToFile("data/cuda_uInit.dat",cuda_u,n);

  //Allocate memory on the GPU
  float *d_u, *d_u2;
  checkCuda(
    cudaMalloc(&d_u, n*sizeof(float))
  );
  checkCuda(
    cudaMalloc(&d_u2, n*sizeof(float))
  );

  //Copy cuda_u into d_u
  checkCuda(
    cudaMemcpy(d_u, cuda_u, n*sizeof(float), cudaMemcpyHostToDevice)
  );


	cudaEventRecord(start);//Start timing
  //Perform n_steps of diffusion
  for( i = 0 ; i < n_steps; i++){

    if(outputData && i%outputPeriod == 0){

      sprintf(filename,"data/cuda_u%08d.dat",i);

      //Copy data off the device for writing
      checkCuda(
        cudaMemcpy(cuda_u, d_u, n*sizeof(float), cudaMemcpyDeviceToHost)
      );
      outputToFile(filename,cuda_u,n);

    }

    //Call the cuda_diffusion kernel
    cuda_diffusion<<<gridDim,blockDim>>>(d_u,d_u2,n);

    //Switch the buffer with the original u
    float *temp = d_u;
    d_u = d_u2;
    d_u2 = temp;

  }
	cudaEventRecord(stop);//End timing


  //one last data dump...
  sprintf(filename,"data/cuda_u%08d.dat",i);

  // Copy the memory back for one last data dump
  checkCuda(
    cudaMemcpy(cuda_u, d_u, n*sizeof(float), cudaMemcpyDeviceToHost)
  );
  outputToFile(filename,cuda_u,n);

  //Get the total time used on the GPU
	cudaEventSynchronize(stop);
	milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

  cout<<"Cuda Kernel took: "<<milliseconds/n_steps<<"ms per step"<<endl;


/********************************************************************************
  Test the cuda kernel for diffusion with shared memory
 *******************************************************************************/

  //Allocate a copy for the GPU memory in the host's heap
  float* shared_u  = new float[n];

  /*
  //Initialize the cuda memory
  for( i = 0; i < n; i++){
    shared_u[i] = initial_u[i];
  }
  outputToFile("data/shared_uInit.dat",shared_u,n);

  //Copy the initial memory onto the GPU
  //FIXME copy shared_u to d_u



	cudaEventRecord(start);//Start timing
  //Perform n_steps of diffusion
  for( i = 0 ; i < n_steps; i++){

    if(outputData && i%outputPeriod == 0){
      //Copy data off the device for writing
      sprintf(filename,"data/shared_u%08d.dat",i);
      //FIXME

      outputToFile(filename,shared_u,n);
    }

    //Call the shared_diffusion kernel
    //FIXME

    //Switch the buffer with the original u
    //FIXME

  }
	cudaEventRecord(stop);//End timing


  //Copy the memory back for one last data dump
  sprintf(filename,"data/shared_u%08d.dat",i);
  //FIXME


  //Get the total time used on the GPU
	cudaEventSynchronize(stop);
	milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

  cout<<"Shared Memory Kernel took: "<<milliseconds/n_steps<<"ms per step"<<endl;
  */

/********************************************************************************
  Test the cuda kernel for diffusion, with excessive memcpys
 *******************************************************************************/

  /*
  //Initialize the cuda memory
  for( i = 0; i < n; i++){
    shared_u[i] = initial_u[i];
  }

	cudaEventRecord(start);//Start timing
  //Perform n_steps of diffusion
  for( i = 0 ; i < n_steps; i++){

    //Copy the data from host to device
    //FIXME copy shared_u to d_u

    //Call the shared_diffusion kernel
    //FIXME

    //Copy the data from host to device
    //FIXME copy d_u2 to cuda_u


  }
	cudaEventRecord(stop);//End timing



  //Get the total time used on the GPU
	cudaEventSynchronize(stop);
	milliseconds = 0;
	cudaEventElapsedTime(&milliseconds, start, stop);

  cout<<"Excessive cudaMemcpy took: "<<milliseconds/n_steps<<"ms per step"<<endl;
  */

  //Clean up the data
  delete[] initial_u;
  delete[] host_u;
  delete[] host_u2;

  delete[] cuda_u;
  delete[] shared_u;

  //free d_u and d_u2
  cudaFree(d_u);
  cudaFree(d_u2);
}
