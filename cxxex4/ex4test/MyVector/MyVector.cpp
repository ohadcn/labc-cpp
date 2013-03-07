#include "MyVector.h"
#include <assert.h>

MyVector::MyVector(unsigned int size) : _data(new int[size]) {
}

MyVector::~MyVector() {
      delete[] _data;
}

int& MyVector::operator[](unsigned int i) {
      assert(i<_size);
      return _data[i];
}


