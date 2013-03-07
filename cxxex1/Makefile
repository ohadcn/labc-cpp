#makefile for ex. 1 in c++ course
#written by ohad cohen <ohadcn@cs.huji.ac.il>
#this makefile contains also command for archiving the exercise files

INCLUDES := GrahamScan Point PointList Stack PointComperator

BIN_NAME := ConvexHull

FLAGS := -Wall -Wvla -g -O3 -Wextra -lm

CC := g++

all: $(BIN_NAME)

%.o: %.cpp %.h
	$(CC) $(FLAGS) -c $< -o $@

$(BIN_NAME): $(BIN_NAME).cpp $(foreach HEADER,$(INCLUDES),$(HEADER).o)
	$(CC) $(FLAGS) $^ -o $@

clean:
	rm -f *.a *.o *~ $(BIN_NAME)

.PHONY : clean tar all default

tar: README Makefile $(BIN_NAME).cpp $(foreach file,$(INCLUDES),$(file).cpp $(file).h)
	tar cf ex1.tar $^
