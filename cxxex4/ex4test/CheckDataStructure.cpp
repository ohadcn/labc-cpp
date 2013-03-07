#include <vector>
#include <map>
#include <assert.h>
#include "MyQuickInitArray.h"

#define NUM_TESTS 250
#define ARR_SIZE 10000

/////////////////////////////////////
// A non primitve class for tests //
////////////////////////////////////
class NonPrem
{
public:
  NonPrem(int val = 0)
  {
    _size = val;
    init();
  }
  NonPrem(const NonPrem& n)
  {
    _size = n.getSize();
    init();
  }
  friend NonPrem operator+(const NonPrem &r1, const NonPrem &r2) throw (std::exception());
  int getSize() const;
private:
  int* _arr;
  int _size;
  void init();
};

NonPrem operator+(const NonPrem &r1, const NonPrem &r2) throw (std::exception())
{
  int size = r1.getSize() < r2.getSize() ? r1.getSize() : r2.getSize();
  return NonPrem(size);
}
void NonPrem::init() {
  _arr = new int[_size];
  for (int i = 0; i < _size; i++)
  {
      _arr[i] = i*2+1;
  }
}
int NonPrem::getSize() const
{
  return _size;
}

///////////////////////////
// End of class NonPrem //
//////////////////////////

void MyQuickInitArrayRun()
{
  // Test number 1 - my quick init array
  for (int numTest = 0 ; numTest < NUM_TESTS ; ++numTest)
  {
      MyQuickInitArray<NonPrem> tempQIA(ARR_SIZE);
      tempQIA[5] = NonPrem(999);
      tempQIA[3007] = tempQIA[5] + tempQIA[5];
      tempQIA[5209] = tempQIA[5] + tempQIA[3007];
      for (int tempi = 306 ; tempi < 608 ; tempi += 6) 
      {
	tempQIA[tempi] = tempQIA[5];
      }
  }
}

void RegularVectorRun()
{
  // Test number 2 - regular vector, slow initialize, quick variable approch
  for (int numTest = 0 ; numTest < NUM_TESTS ; ++numTest)
  {
      std::vector<NonPrem> tempV(ARR_SIZE);
      tempV[5] = NonPrem(999);
      tempV[3007] = tempV[5] + tempV[5];
      tempV[5209] = tempV[5] + tempV[3007];
      for (int tempi = 306 ; tempi < 608 ; tempi += 6) 
      {
	tempV[tempi] = tempV[5];
      }
  }
}

void RegularMapRun()
{
  // Test number 3 - regular map, quick initialize, slow variable approch
  for (int numTest = 0 ; numTest < NUM_TESTS ; ++numTest)
  {
      std::map<int, NonPrem> tempM;
      tempM[5] = NonPrem(999);
      tempM[3007] = tempM[5] + tempM[5];
      tempM[5209] = tempM[5] + tempM[3007];
      for (int tempi = 306 ; tempi < 608 ; tempi += 6) 
      {
	tempM[tempi] = tempM[5];
      }
  }
}

int main()
{
  MyQuickInitArrayRun();
  RegularVectorRun();
  RegularMapRun();
  std::cout << "Done all tests." << std::endl;
  return 0;
}
