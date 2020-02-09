// Author: Praharsh Verma
// Email: pbv5036@psu.edu
#include <stdlib.h>
#include <string.h>
// rotate the values pointed to by three pointers
// so values move from xp to yp, yp to zp and zp to xp
void rotate(int *xp, int *yp, int *zp) {
  int a = *xp;
  int b = *yp;
  int c = *zp;

  *xp = c;
  *yp = a;
  *zp = b;
   
  return;
}

// Write a function that returns 0 if x is 0, returns -1 
// if x < 0, returns 1 if x > 0
// Your code must follow the Bit-Level Integer Coding Rules
// on the textbook (located between hw 2.60 and 2.61).
// You can assume w = 32. 
// The only allowed operations in your code are:
// ! ~ & ^ | + << >>
// This requirement is more restrictive than the coding rules. 

int sign(int x) {
  int k = 0;
  if((x>>31)&1)
  {
    return -1;
  }
  
  if(x|0)
  {
    return 1;
  }

  return k;

 // else if((x>>31)&0)
 // {
  // if((~x)) 
  // return 0;
 // }
 
 // return k;
  
}

// Given a source string, and a destination string, write the
// reversed source string into destination. Make sure you terminate
// the reversed string properly with an integer value 0.
// You may assume that the destination array is big enough to hold
// the reversed string. 
void reverse(const char source[], char destination[]) {
  int length = strlen(source)-1;
  int k;
  int j = 0;
  for(k = length;k>=0; k--)
  { 
   destination[j] = source[k];
   j = j+1;
  }
  destination[j] = 0; 
  return;
}
