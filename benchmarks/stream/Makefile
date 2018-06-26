CC = gcc
CFLAGS = -O2

FF = g77
FFLAGS = -O2

all: stream

stream: stream.c
	$(CC) $(CFLAGS) stream.c -o stream

clean:
	rm -f stream *.o

# an example of a more complex build line for the Intel icc compiler
stream.icc: stream.c
	icc -O3 -xCORE-AVX2 -ffreestanding -qopenmp -DSTREAM_ARRAY_SIZE=80000000 -DNTIMES=20 stream.c -o stream.omp.AVX2.80M.20x.icc
