#include <stdio.h>

int extendedSubStr(int isCyclic, int step, const char* str1, const char* str2);

void testFunc(int isCyclic, int step, const char* str1, const char* str2,int expectedOutput)
{
  static int testNum = 1;
  int result=extendedSubStr(isCyclic, step, str1, str2);
  if ((result=extendedSubStr(isCyclic, step, str1, str2))!=expectedOutput)
	printf("test%d:result %d expected:%d\n", testNum++,result,expectedOutput );
}

int main(int argc, char* argv[])
{
  testFunc(0,1,"a","a",0);

  testFunc(0,1,"aaa","aaaa",-1);

  testFunc(0,6,"abcdefg","ag",0);

  testFunc(1,2,"a,b,c,d,e,f,g,h,","abcdefg",0);

  testFunc(1,2,"+T+E+S+T+","TEST",1);

  testFunc(1,2,"+E+S+T+T","TEST",7);

  testFunc(1,2,"A","AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA",0);

  testFunc(0,0,"A+++b+c++++d+e++++f+g+++++h+i","Abcdefghi",0);

  testFunc(1,1,"TA","ATA",1);

  testFunc(1,8,"ABCDEFGHI","IH",8);

  testFunc(1,10000,"A","AAAAAA",0);

  return 0;
}
