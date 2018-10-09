all: pingpong_blocking.out pingpong_nonblocking.out

pingpong_blocking.out: pingpong_blocking.c
	mpicc -o pingpong_blocking.out pingpong_blocking.c

pingpong_nonblocking.out: pingpong_nonblocking.c
	mpicc -o pingpong_nonblocking.out pingpong_nonblocking.c

clean:
	rm -f pingpong_blocking.out pingpong_nonblocking.out

.PHONY: clean
