CC=g++
CFLAGS=-g -std=c++17
FILENAME=bigint

all: main.cc number.o BigInt2.o
	$(CC) $(CLFAGS) -o $(FILENAME) main.cc BigInt2.o number.o

BigInt2.o: big_int.hpp BigInt2.cc
	$(CC) $(CFLAGS) -c -o BigInt2.o BigInt2.cc

number.o: number.hpp number.cc
	$(CC) $(CFLAGS) -c -o number.o number.cc

.PHONY: clean

clean:
	rm -rf *.o
