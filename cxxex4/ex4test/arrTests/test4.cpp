#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 200
#define ARR_SIZE 100

/* Forth Test - constructors calls. */

class NonPrem
{
public:
    NonPrem(int val = 0)
    {
        ++_numConstructorCalls;
        _tempVal = val;
    }
    NonPrem(const NonPrem& n)
    {
        ++_numConstructorCalls;
        _tempVal = n._tempVal;
    }
    static int GetNumConstructorsCall() {return _numConstructorCalls;}
    int GetTempVal() const {return _tempVal;}
private:
    static int _numConstructorCalls;
    int _tempVal;
};

int NonPrem::_numConstructorCalls = 0;


int main()
{
    MyQuickInitArray<NonPrem> tempQIA(ARR_SIZE);
    for (int numTest1 = 0 ; numTest1 < NUM_TESTS ; ++numTest1)
    {
        tempQIA[rand() % ARR_SIZE] = NonPrem(5);
    }

    assert(NonPrem::GetNumConstructorsCall() < 1000);

    std::cout << "Done test test4.cpp." << std::endl;
    
    return 0;
}

