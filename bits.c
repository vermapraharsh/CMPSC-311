/*
 * CS:APP Data Lab
 *
 * Praharsh Verma pbv5036
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
/* Copyright (C) 1991-2012 Free Software Foundation, Inc.
   This file is part of the GNU C Library.

   The GNU C Library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   The GNU C Library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with the GNU C Library; if not, see
   <http://www.gnu.org/licenses/>.  */
/* This header is separate from features.h so that the compiler can
   include it implicitly at the start of every compilation.  It must
   not itself include <features.h> or any other header that includes
   <features.h> because the implicit include comes before any feature
   test macros that may be defined in a source file before it first
   explicitly includes a system header.  GCC knows the name of this
   header in order to preinclude it.  */
/* We do support the IEC 559 math functionality, real and complex.  */
/* wchar_t uses ISO/IEC 10646 (2nd ed., published 2011-03-15) /
   Unicode 6.0.  */
/* We do not support C11 <threads.h>.  */
/*
 * allEvenBits - return 1 if all even-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allEvenBits(0xFFFFFFFE) = 0, allEvenBits(0x55555555) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allEvenBits(int x) {
  //The first few lines declares all the varibles required to implement this function
  //a is defined as 0x55 which in binary translates to 0101 (this 4 bit int follows the conditon which returns 1, as all even bits are 1)
  //Next I have to shift the bits by 8 bits, (since I cannot declare any constants larger than 4 bits)
  //After the shift, I have (in binary) 0101 0101 0000 0000
  //Now I add 0x55 to the new bit pattern, which is now 0101 0101 0101 0101 (essentially just concatanating the pattern to the end)
  //Since I have to compare my pattern to a 32 bit input, I have to shift by 16 bits, giving me 0101 0101 0101 0101 0000 0000 0000 0000
  //Again, I have to concatanate the pattern to the end, so I add the two together giving me 0101 0101 0101 0101 0101 0101 0101 0101 (which is the 1 conditon)
  //Now I AND the input with my pattern, so I get a new 32 bit int with only the positions in which both input and pattern have 1
  //Next I XOR the result of the AND with the pattern, this will only return 1 in places where only 1 of the two inputs have 1. This condition return 0 if the
  //input follows the 0101 pattern, and 1 if not
  //Finally, I invert the result of the XOR since the appliction requires 1 if the pattern is followed, and 0 if not\.
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
  a = (0x55);
  b = a << 8;
  c = b + a;
  d = c << 16;
  e = d + c;
  f = x & e;
  g = f ^ e;
  h = ! g;
  return h;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  //The first few lines initialize the variables required
  //The first variable assignment uses the bitwise NOT operator to invert the input
  //then we add 1 so we can convert to 2's compliment
  //this is then ORed with the input, and shifted 31 bits to the right so only the MSB remains
  //we add one to it since we are exploiting the overflow dumping issue, and 0 will turn into 1, whereas any number greater than 0 will have a 0 in the LSB and the one will carry over to the next significant bit, but it will be dropped so we get only the LSB
  int a;
  int b;
  int c;
  int d;
  int e;
  a = ~x;
  b = a + 1;
  c = b | x;
  d = c >> 31;
  e = d + 1;
  return e;
}
/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) {
  unsigned a;
  unsigned b;
  unsigned c;
  unsigned d;
  unsigned e;
  unsigned f;
  unsigned g;
  unsigned h;
  unsigned i;
  unsigned j;
  unsigned k;

  a = (1 << 31);
  b = ~a;
  d = b & ug;
  c = b & uf;
  e = (1 << 23);
  f = ~0 + e;
  g = 0xFF;
  h = c >> 23;
  k = d >> 23;
  i = ((h == g) && (f & uf) != 0); //condition that checks if uf falls into NaN error
  j = ((k == g) && (f & ug) != 0); //condition that checks if ug falls into NaN error

  if (i || j)
  {
    return 0;
  }

  if ((c == 0) && (d == 0))
  {
    return 1;
  }

  return uf == ug;
}

/*
 * floatUnsigned2Float - Return bit-level equivalent of expression (float) u
 *   Result is returned as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point values.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatUnsigned2Float(unsigned u) {
  int a = 31;
  int b = 0xffffffff;
  int c = 0x007fffff;

  if(!u)
  {
    return 0;
  }

  while(!(u&(1<<a)))
  {
    a = a - 1;
  }

  if(a<=23)
  {
    u<<=(23-a);
  }

  else
  {
    u+=(1<<(a-24));

    if(!(u<<(55-a)))
    {
      u&=(b<<(a-22));
    }

    if(!(u&(1<<a)))
    {
      a = a + 1;
    }

    u >>= (a-23);
  }

  u=u&c;
  a=(a+127)<<23;
  return u|a;
}

/*
* isLess - if x < y  then return 1, else return 0
*   Example: isLess(4,5) = 1.
*   Legal ops: ! ~ & ^ | + << >>
*   Max ops: 24
*   Rating: 3
*/
int isLess(int x, int y) {
  //first we must declare the variables
  //next we have to check if there is a difference in the signs between the two inputs, we do this through the XOR operand
  //this allows us to compare the sign bits(we can disregard the other 31 LSBs for now)
  //next we must check if there is a difference between the two, and which is greater if so
  //the trick here is that checking for y-x will cause you overflow as converting x into -x
  //requires you to 2's compliment (~x+1), but this will cause overflow in specifc cases like x = 0
  //so instead we will check for x-y, as y is larger than x, so no overflow will occur
  //we 2's compliment y, then add it to x to fulfill the function x-y
  //next we must compare the difference in signs we stored in variable a earlier to the x input, as a difference in sign will
  //place a 1 in the MSB of variable a, therefore if we AND input x with varible a, we can figure out if x is negative or not
  //afterwards, we compliment variable a, then AND it with varaible c(the x-y term)
  //this allows us to check the sign of the y input
  //finally we can OR the two together
  //this leaves us with a 32 bit int, but we only need to check for the MSB as this bit indicates sign
  //therefore we shift right by 31 bits
  //the last thing we do is then AND the sign bit with 1, if the number(x-y) is negative, the sign bit is 1, and therefore we output 1
  //on the other hand, if the signbit is positive, we output 0
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
  a = x ^ y;
  b = ~y + 1;
  c = x + b;
  d = a & x;
  e = ~a & c;
  f = d|e;
  g = f >> 31;
  h = g & 1;
  return h;

}
/*
* isNonNegative - return 1 if x >= 0, return 0 otherwise
 *   Example: isNonNegative(-1) = 0.  isNonNegative(0) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNonNegative(int x) {
  //we define the varibles first
  //next we need to check for the sign bit, 0 indicating a number >0 or else 0 itself
  //to do this, we isolate the sign bit by shifting 31 bits to the right, the sign extension will fill in the sign bit in the other bit positions
  //finally we can logical NOT this int,if the sign bit is 0, we return 1, if the sign but is 1, we return 0
  int b;
  int n;
  b = x >> 31;
  n = !b;
  return n;
}
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
 //first we define all the variables
 //next we use the bitwise negation operator to invert the input, x
 //then the value is run through the logical NOT operator to output only a single bit value
 //this value (variable c) will be 1 only if x is -1, otherwise it becomes 0
 //next we add the input to 1, in the case that the input is -1, then the variable v will be 0
 //then we use the bitwise compliment operator again to flip it to 1 (in the case of x = -1, if the variable v has another other value than 0, it will become 0)
 //now we can XOR our complimented term with the input x
 //assuming the condition that x = -1, then the outcome of this calculation will be 1 XORed with -1, which the binary 1110
 //we can now OR this 1110 value with the variable c(whose binary form is 0001 under the conditon x = -1) and get 1111 as output
 //when this is then operated by the logical NOT, we recieve a one-bit output 0 (under the condition that x = -1)
 int z;
 int c;
 int v;
 int b;
 int n;
 int m;
 int q;
 z = ~x;
 c = !z;
 v = x + 1;
 b = ~v;
 n = b ^ x;
 m = n | c;
 q = !m;
 return q;
}


/*
 * rotateLeft - Rotate x to the left by n
 *   Can assume that 0 <= n <= 31
 *   Examples: rotateLeft(0x87654321,4) = 0x76543218
 *   Legal ops: ~ & ^ | + << >> !
 *   Max ops: 25
 *   Rating: 3
 */
int rotateLeft(int x, int n) {
  //First all the variables are declared
  //next we need to find how many bits we need to preserve
  //we know we will shift by n, and n can be between 0 and 31 (so 32 bits long) therefore we want to subtract 32-n
  //since we cannot use the subtract operator, we must convert n into 2's compliment by using the bitwise NOT operator, then adding 1
  //once n is negated, we can add 32 (0x20) with the negated n
  //Now that we have the number of bits to preserve and shift, we can start storing the MSBs, else they will be wiped from left shift operations
  //we create an int which has all 1's (32 1's to be precise) by negating 0 and shifting by the number of bits to preserve
  //this creates an int which stores 1's only in the bit positions to be preserved in x
  //next we do the same thing for preserving the bits which will only get shifted, however we need to create an opposite bit pattern
  //so we negate the whole term, leaving 0's in the positions the shifted bits will be placed
  //now we AND the bit pattern for preservation(MSBs) with the input itself
  //this leaves us with only the terms present in the original preservation bits, and removes excess 1's as they could cause sign error isses
  //now we shift the whole pattern to the right by the previously calculated number of bits to be preserved, effectivly moving the MSBs to the LSB position
  //note: the new bit pattern will lead with 1's since we negated the term earlier
  //we must now remove the excess 1's by ANDing the bit pattern with the opposite bit pattern (the one which preserves the shfiting bits)
  //next we shift the original input by the shift amount passed on
  //our bit pattern will be of the form ([shifted bits] ....0000) so we just need to concatenate the MSBs to the end
  //we can accomplish this by using the OR operator between the above bit pattern, and the preserved bit pattern
  //note: we must utilize bit masks since shift operators on the input itself will cause sign errors when working with negative numbers as the sign bit will be dropped in a
  //shift left operation
  int a;
  int b;
  int c;
  int d;
  int e;
  int g;
  int h;
  int i;
  int f;
  e = ~n + 1;
  b = 0x20;
  g = b + e;
  c = ~0 << g;
  a = ~0 << n;
  d = ~a;
  e = c & x;
  f = e >> g;
  g = f & d;
  h = x << n;
  i = h | g;
  return i;
}
/*
 * signMag2TwosComp - Convert from sign-magnitude to two's complement
 *   where the MSB is the sign bit
 *   Example: signMag2TwosComp(0x80000005) = -5.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 4
 */
int signMag2TwosComp(int x) {
  //first we declare all the variables
  //next we shift the input by 31 bits to the left to isolate the sign bit
  //once this is done, we create a new bit pattern to store the magnitude
  //first we shift 1 by 31 bits to the left, bringing the sign to the MSB position
  //then we use the compliment operator to make all bits 1 except the MSB, which then becomes 0
  //this value is then ANDed with the input to isolate all bits except those signifying magnitude
  //next we need to convert this magnitude into two's compliment, which we achieve by using the compliment operator and adding 1
  //nex the sign is ANDed with the two's compliment magnitude, and the sign is preserved since the leading bit for the magnitude in 2'c compliment
  //is the same as the stored sign bit
  //now we must negative the sign bit and then AND it with the magnitude to remove the leading sign bits
  //finally we can OR the two pieces together, as they will preserve the magnitude only, since the sign bits are set to 0
  int a;
  int b;
  int c;
  int d;
  int e;
  int f;
  int g;
  int h;
  a = x >> 31;//sign
  b = (1 << 31);
  c = ~b;
  d = x & c;//magnitude
  e = ~d + 1;
  f = a & e;
  g = ~a & d;
  h = f | g;
  return h;
}
/*
 * thirdBits - return word with every third bit (starting from the LSB) set to 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 8
 *   Rating: 1
 */
int thirdBits(void) {
  //The first few lines declare the varibles
  //a is defined as 0x49 which in binary is 0100 1001 (all the third bits are set to 1)
  //Next we have to shift left by 9 bits since we need to append more bits to the end
  //9 bits was specfically choosen since the LSB on my constant is 1 and the MSB on my constant is 0, and they would be trailing
  //At the point they meet, there would only be 1 zero between the 1's, and we need 2 zeros to repeat the pattern
  //Then the shifted bit pattern is ORed with the constant to contatanate the pattern at the end
  //The pattern is now repeating for the first 17 bits, while the leading 15 bits are still 0
  //Now we must shift the pattern again, this time by 18 bits for the same reason as above, to ensure the 2 0's between every 1
  //Finally we OR the shifted bit pattern with the constant to concatanate the remaining  bits
  int a;
  int b;
  int c;
  int d;
  int e;
  a = 0x49;
  b = a << 9;
  c = a | b;
  d = c << 18;
  e = d | c;
  return e;
}
