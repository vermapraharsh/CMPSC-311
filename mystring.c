// Author: Praharsh Verma
// Email: pbv5036@psu.edu

#include <string.h>
#include "mystring.h"
#include <stdlib.h>
int mystrcmp(const char *s1, const char *s2) {

  while(*s1 == *s2) //first checks to see if both the first pointers are pointing to the same object
                    //if they are then we iterate through the entire string until they are different

  {
                    //if pointer to s1 is at '\0', then we know we have reached the end of the string
    if(*s1 == '\0')

    {

      return 0; //we return 0, since both strings have reached their end and the values have been the same throughout, so they are the same strings
                //and strcmp would return 0 in this case

    }

    s1 = s1 + 1; //if the loop has not terminated yet (not reached the end of s1), then we move the indexes of both strings up 1 to compare the next values
    s2 = s2 + 1;

  }

  int diff = *s1 - *s2;
  return(diff); //if the loop exits, it is because there is some difference between the strings, in this case the difference of the two is calculated and returned.
                    //the difference will be negative if s2 is greater and positive if s1 is greater, just as strcmp would behave

}

char *mystrdup(const char *s) {

  int lenstr = 0; //here we create a way to calculate the length of the string without the use of string functions in C
  while (s[lenstr++] != '\0');
  int len = lenstr - 1; //the length is 1 less than recorded since the '\0' is present and we only want the actual length of the string
  int k;
  char *dupStr = (char*)malloc(len + 1); //here we use the malloc() function to create space for the new pointer which will store the current pointers
                                        //then add one to the len since we need to add the '\0' afterwards
  for (k = 0; k < len; k++)  //the loop iterates through the string and copies the values from each index to the new pointer

  {

    dupStr[k] = s[k];

  }

  dupStr[k] = '\0'; //finally we add the '\0' to the end and return the result just as strdup function would
  return dupStr;

}
