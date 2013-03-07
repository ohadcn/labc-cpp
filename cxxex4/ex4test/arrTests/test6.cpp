#include <vector>
#include <iostream>
#include <map>
#include <stdlib.h>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 200
#define ARR_SIZE 100

/* Last Test - Calls for objects copy constructor. */

class NonPrem
{
public:
    NonPrem(int val = 0)
    {
        if (val == 0)
            ++_numConstructorCalls;
        _tempVal = val;
    }
    NonPrem(const NonPrem& n)
    {
//        ++_numConstructorCalls;
        _tempVal = n._tempVal + 1;
    }
    NonPrem& operator=(const NonPrem& n)
    {
        if (this == &n)
            return *this;
        _tempVal = n._tempVal + 1;
        return *this;
    }
    static int GetNumConstructorsCall() {return _numConstructorCalls;}
    int GetTempVal() const {return _tempVal;}
private:
    static int _numConstructorCalls;
    int _tempVal;
};

int NonPrem::_numConstructorCalls = 0;

// Check that operator= set cells that was initialized in the old vector to uninitialized

int main()
{
    int constructorsCheck = 0;
    MyQuickInitArray<NonPrem> tempQIA(ARR_SIZE);
    int beforeCall = NonPrem::GetNumConstructorsCall();
    tempQIA[6] = NonPrem(13);
    int afterCall = NonPrem::GetNumConstructorsCall();
    constructorsCheck += (afterCall - beforeCall);
    MyQuickInitArray<NonPrem> ttempQIA(ARR_SIZE);
    tempQIA = ttempQIA;
    beforeCall = NonPrem::GetNumConstructorsCall();
    tempQIA[6] = NonPrem(13);
    tempQIA[6] = NonPrem(13);
    afterCall = NonPrem::GetNumConstructorsCall();
    constructorsCheck += (afterCall - beforeCall);
    assert(constructorsCheck == 2);
    std::cout << "Done test test6.cpp." << std::endl;
    return 0;
}

