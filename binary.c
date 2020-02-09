#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

int main(int argc, char *argv[]) {
  unsigned long long int i;
  // checking there is a command line argument
  if (argc != 2) {
    printf("Usage: %s number\n", argv[0]);
    return 0;
  }
  // converting the command line argument to a unsigned long
  // and exit program if there is an error during the conversion.
  errno = 0;
  i = strtoul(argv[1], NULL, 16);
  if (errno != 0) {
    perror("Failed to convert number");
    return 0;
  }
  //write your solutions below this line
  if (i == 0)
  {
    printf("%llu\n", i);
    //prints 0 in case of i = 0
  }

  else
  {
    int a[100], j,k;   
    //creates an array to store number of division operations required to bring i to 0, I arbitrarily chose a large number as to ensure no segmentation erros
    for (j = 0; i > 0; j++)
    {
      a[j] = i % 2;
      //this is the remainder that gets stored for our binary representation
      i = i / 2;   
      // reduces i by 2 every iteration 
    } 

    
    for(k = j - 1; k >= 0; k--)
    {
      printf("%d", a[k]); 
      //prints out the values of the array starting with the largest index value as the remainders as concatenated backwards
    }
    printf("\n");
    
 }
  return 0;
  //ensures no control reaches end of non-void function
}
 


 //this is my older code, it did not work since the value of temp got way larger than unsigned long long int supports for any hex values with more than 5 digits

 // long long binarynum = 0;
 // unsigned long long int rem = 1;
 // unsigned long long int temp = 1;
 // int k = 1;
 // int step = 1;
 // while(i!=0)
 // {
   // rem = i%2;
   // i = i/2;
   // binarynum += rem*temp;;
   // temp *= 10;
   // printf("%llu\n",temp);
 // }
 // printf("%llu\n",binarynum);
  // write your solutions above this line
 // return 0;

