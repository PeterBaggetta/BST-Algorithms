CC = gcc
FLAGS = -Wpedantic -std=gnu99

all: P11.o P12.o P2.o main.o main

P11.o: P11.c myHeader.h
	$(CC) $(FLAGS) -c P11.c -o P11.o

P12.o: P12.c myHeader.h
	$(CC) $(FLAGS) -c P12.c -o P12.o

P2.o: P2.c myHeader.h
	$(CC) $(FLAGS) -c P2.c -o P2.o

main.o: main.c myHeader.h
	$(CC) $(FLAGS) -c main.c -o main.o

main: main.o
	$(CC) $(FLAGS) main.o P11.o P12.o P2.o -o main


clean:
	rm -r *.o main
