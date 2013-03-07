#makefile for ex. 2 in c++ course
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also command for archiving the exercise files

INCLUDES := Candidate Alice Bob Colin Danny University College List Errors IO

BIN_NAME := Hire

FLAGS := -Wall -Wvla -g -O3 -Wextra -lm

CC := g++

EX := ex2

all: $(BIN_NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_NAME): $(BIN_NAME).cpp $(foreach HEADER,$(INCLUDES),$(HEADER).o)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.a *.o *~ $(BIN_NAME)

.PHONY : clean tar all default

tar: $(EX).tar

$(EX).tar: README Makefile $(BIN_NAME).cpp $(foreach file,$(INCLUDES),$(file).cpp $(file).h)
	tar cf $(EX).tar $^
