#makefile for ex. 4 in labc
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also commands for testing and archiving the exercise files

FLAGS := -Wall -Wvla -g -O3

CC := gcc

default: all

%.o: %.c %.h
	$(CC) $(FLAGS) -c $< -o $@

all: HashIntsSearch HashStrsSearch GenericHashTable

HashStrsSearch: HashStrSearch.c MyStringFunctions.o libGenericHashTable.a
	$(CC) $(FLAGS) $^ -o $@

HashIntsSearch: HashIntSearch.c MyIntFunctions.o libGenericHashTable.a
	$(CC) $(FLAGS) $^ -o $@

GenericHashTable: libGenericHashTable.a
	

libGenericHashTable.a: GenericHashTable.o TableErrorHandle.o
	ar rcu libGenericHashTable.a $^
	ranlib libGenericHashTable.a

clean:
	rm -f *.a *.o *~ HashIntsSearch HashStrsSearch

test: 
	./ex4test

submit: test tar

tar: README GenericHashTable.c MyIntFunctions.c MyStringFunctions.c Makefile
	tar cf ex4.tar README GenericHashTable.c MyIntFunctions.c MyStringFunctions.c Makefile

.PHONY : clean tar test GenericHashTable all default submit
