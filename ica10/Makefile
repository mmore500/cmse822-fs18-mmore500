all: diffusion.out

diffusion.out: diffusion.cu
	nvcc -o diffusion.out -O3 diffusion.cu

debug: diffusion.cu
	nvcc -o diffusion.out -DDEBUG -O3 diffusion.cu

clean:
	rm -f diffusion.out

run: diffusion.out
	srun ./diffusion.out

.PHONY: clean debug run
