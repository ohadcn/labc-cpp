#include "MyVector.h"

const unsigned int V_SIZE= 1000000;
const unsigned int NUM_RUNS= 10000;

int main() {

      MyVector v(V_SIZE);

      for (unsigned int j=0; j<NUM_RUNS; ++j) {
	    for (unsigned int i=0; i<V_SIZE; ++i) {
		  v[i]= i;
	    }
      }
      
      return 0;
}
