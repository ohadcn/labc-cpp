#include <vector>
#include <map>
#include <iostream>
#include <stdlib.h>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 2500
#define ARR_SIZE 100

/* Second Test - const operator [] existance. */

int main()
{
    MyQuickInitArray<int> tempQIA(ARR_SIZE);
    tempQIA[3] = 9;
    tempQIA[8] = 1;

    const MyQuickInitArray<int> constTempQIA(tempQIA);
    if (tempQIA[3] != 9 || tempQIA[8] != 1 || tempQIA[1] != 0)
        std::cout << "Fail test2.cpp" << std::endl;
    else
        std::cout << "Pass test test2.cpp." << std::endl;
    
    return 0;
}
