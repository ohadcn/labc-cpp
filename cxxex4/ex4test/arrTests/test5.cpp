#include <vector>
#include <map>
#include <iostream>
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
        ++_numConstructorCalls;
        _tempVal = val;
    }
    NonPrem(const NonPrem& n)
    {
        ++_numConstructorCalls;
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


int main()
{
    for (int numTest1 = 0 ; numTest1 < NUM_TESTS ; ++numTest1)
    {
        MyQuickInitArray<NonPrem> tempQIA(ARR_SIZE);
        std::vector<bool> alreadySel(ARR_SIZE, false);
        int numChanges = 0;
        for (int tempi = 0 ; tempi < ARR_SIZE/2 ; ++tempi)
        {
            int nextCellSel = rand() % ARR_SIZE;
            tempQIA[nextCellSel] = NonPrem(tempi);
            if (!alreadySel[nextCellSel])
            {
                alreadySel[nextCellSel] = true;
                ++numChanges;
            }
        }
        MyQuickInitArray<NonPrem> tempQIA1(tempQIA);
        MyQuickInitArray<NonPrem> tempQIA2(ARR_SIZE);
        tempQIA2 = tempQIA1;
        int numDiffDiff = 0;
        for (int tempi = 0 ; tempi < ARR_SIZE ; ++tempi)
        {
            if (tempQIA[tempi].GetTempVal() + 2 == tempQIA2[tempi].GetTempVal())
                ++numDiffDiff;
        }
        if (numDiffDiff != numChanges)
        {
            std::cout << "numDiffDiff = " << numDiffDiff << std::endl;
            std::cout << "numChanges = " << numChanges << std::endl;
            std::cout << "ARR_SIZE = " << ARR_SIZE << std::endl;
            std::cout << "numTest = " << numTest1 << std::endl;
            assert(0);
        }
    }

    std::cout << "Done test test5.cpp." << std::endl;
    
    return 0;
}

