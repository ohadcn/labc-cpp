/**
 * file:IO.h
 * this file has written by Ohad Cohen <ohadcn@cs.huji.ac.il> as part of ex. 2 in c++ course.
 */

#ifndef IO_H
#define IO_H

#include "Candidate.h"
#include "List.h"

/**
 * this header declare methods for input & output
 *
 * public methods:
 * redirectIO(int argc,char** args) - redirect the input / output to the required parameters given in args
 * see ex. desc. for info about parameters
 * restoreIO() - restore cin & cout to their default values.
 * setOutputFormat() - set the format cout prints real numbers to the one required by ex.
 *
 * public operators:
 * {istream} >> {Candidate} - read a Candidate description from an istream, see ex. description for expected format.
 * {istream} >> {List<Candidate>} - reads a list of candidates from th istream.
 */


//reading candidates
istream &operator >>(istream &in,Candidate *(&p));
istream &operator >>(istream &in, List<Candidate> *list);

//IO manipulations
void redirectIO(int argc, char **args);
void restoreIO();
void setOutputFormat();

#endif // IO_H
