#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 2500
#define ARR_SIZE 100

/* First Test - Stability check. */

int main()
{
    for (int numTest1 = 0 ; numTest1 < NUM_TESTS ; ++numTest1)
    {
        MyQuickInitArray<int> tempQIA(ARR_SIZE);
        for (int tempi = 0 ; tempi < ARR_SIZE / 2 ; ++tempi)
        {
            tempQIA[rand() % ARR_SIZE] = tempi;
        }
        MyQuickInitArray<int> temp2(tempQIA);
        MyQuickInitArray<int> temp3(ARR_SIZE);
        temp3 = temp2;
        for (int tempi = 0 ; tempi < ARR_SIZE / 2 ; ++tempi)
        {
            assert(tempQIA[tempi] == temp3[tempi]); 
        }
    }
    std::cout << "Done test test1.cpp." << std::endl;
    
    return 0;
}
