#makefile for ex. 3 in labc
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also commands for testing and archiving the exercise files

FLAGS := -Wall -Wvla -Wextra -g

default: PlayBoard

all: PlayBoard

PlayBoard: Board.o PlayBoard.o ErrorHandle.o
	gcc $(FLAGS) $^ -o PlayBoard

%.o: %.c %.h
	gcc $(FLAGS) -c $< -o $@

clean:
	rm -f *.o *~ XO Q3Testbin PlayBoard

install: PlayBoard
	cp -f PlayBoard /usr/sbin

distclean: clean
	rm -f /usr/sbin/PlayBoard

Q3test: Q3.o
	gcc  Q3Test.c Q3.o -o  Q3Testbin
	./Q3Testbin
	rm Q3Testbin Q3.o

Q4test: PlayBoard
	./Q4test

submit: Q3test Q4test tar

tar: README Q3.c Board.c Makefile
	tar cf ex3.tar README Q3.c Board.c Makefile
