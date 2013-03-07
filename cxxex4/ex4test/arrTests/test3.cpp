#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 2500
#define ARR_SIZE 100

/* Third Test - stable for non premitive objects. */

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
    for (int numTest1 = 0 ; numTest1 < NUM_TESTS ; ++numTest1)
    {
        MyQuickInitArray<NonPrem> tempQIA(ARR_SIZE);
        for (int tempi = 0 ; tempi < ARR_SIZE / 2 ; ++tempi)
        {
            tempQIA[rand() % ARR_SIZE] = NonPrem(tempi);
        }
        MyQuickInitArray<NonPrem> temp2(tempQIA);
        MyQuickInitArray<NonPrem> temp3(ARR_SIZE);
        temp3 = temp2;
        for (int tempi = 0 ; tempi < ARR_SIZE / 2 ; ++tempi)
        {
            assert(tempQIA[tempi].GetTempVal() == temp3[tempi].GetTempVal()); 
        }
    }
    std::cout << "Done test test3.cpp." << std::endl;
    
    return 0;
}

