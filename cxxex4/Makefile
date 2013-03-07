#makefile for ex. 4 in c++ course
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also command for archiving the exercise files

INCLUDES := MyQuickInitArray

BIN_NAME := CheckDataStructure

FLAGS := -Wall -Wvla -g -O -Wextra

CC := g++

EX := ex4

all: $(BIN_NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_NAME): $(BIN_NAME).cpp
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.a *.o *~ $(BIN_NAME)

.PHONY : clean tar all

tar: $(EX).tar

$(EX).tar: README Makefile $(foreach file,$(INCLUDES), $(file).h)
	tar cf $(EX).tar $^
