#ifndef MY_VECTOR_H
#define MY_VECTOR_H

class MyVector {

 public:
      
      MyVector(unsigned int size);
      ~MyVector();

      int& operator[](unsigned int i);
      
 private:
      int* _data;
      unsigned int _size;
      MyVector(const MyVector&);
      MyVector& operator=(const MyVector&);
      
};

#endif

