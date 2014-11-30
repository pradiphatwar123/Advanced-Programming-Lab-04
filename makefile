#------------------------------------------------------------------------------

PROGRAM=heap
EXENAME=pqueue
CC=g++ -g

#------------------------------------------------------------------------------


all:  $(PROGRAM)

heap:  main.o binary.o binom_heap.o fibo_heap.o
	$(CC) main.o binary.o binom_heap.o  fibo_heap.o -o $(EXENAME)

main.o: main.cpp heap.h
	$(CC) -c main.cpp 

binary.o: binary.cpp heap.h
	$(CC) -c binary.cpp

binom_heap.o: binom_heap.cpp heap.h
	$(CC) -c binom_heap.cpp

fibo_heap.o: fibo_heap.cpp heap.h
	$(CC) -c fibo_heap.cpp
clean:
	rm -f *.o *~  $(PROGRAM)



	
		
