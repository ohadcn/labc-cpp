#makefile for ex. 3 in c++ course
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also command for archiving the exercise files

INCLUDES := RegMatrix SparseMatrix Errors Exround

BIN_NAME := MatrixDriver

#the -std=c++11 is needed for the 'auto' keyword to work
FLAGS := -Wall -Wvla -g -O3 -Wextra -lm -std=c++11

CC := g++

EX := ex3

all: $(BIN_NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_NAME): $(BIN_NAME).cpp $(foreach HEADER,$(INCLUDES),$(HEADER).o)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.a *.o *~ $(BIN_NAME)

.PHONY : clean tar all default

tar: $(EX).tar

$(EX).tar: README Makefile $(foreach file,$(INCLUDES),$(file).cpp $(file).h)
	tar cf $(EX).tar $^
