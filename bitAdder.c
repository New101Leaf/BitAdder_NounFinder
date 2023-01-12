#include <stdio.h>
//Forward reference functions

void binaryPrinter(unsigned int byte);
unsigned int and(unsigned int a , unsigned int b);
unsigned int exOr(unsigned int a , unsigned int b);
unsigned int bitAdd(unsigned int a, unsigned int b);

int main() {
    unsigned int firstByte;
    unsigned int secondByte; 
    unsigned int sum1;
 
  

    //User input
    printf("Enter 1st byte: ");
    scanf("%u", &firstByte);
    printf("Enter 2nd byte: ");
    scanf("%u", &secondByte);
    printf("a = ");
    binaryPrinter(firstByte);
    printf(" = %3u\n", firstByte);
    printf("b = ");
    binaryPrinter(secondByte);
    printf(" = %3u\n", secondByte);
    printf("-------------------\n");
    printf("c = ");
    sum1 =  bitAdd(firstByte,secondByte);
    binaryPrinter(sum1);
    printf(" = %u", sum1);


}

/*
   Function: Function adds the decimal numebers using a switch recursive statement
   in: takes in the two bit values
   out: returns the sum

*/

unsigned int bitAdd(unsigned int a, unsigned int b){
  
   switch (b)
   {
   case 0:
       return a;
        
   default:
       return bitAdd(exOr(a,b) , and(a,b) << 1);
       
   }
}
/*
   Function: helper function for ex or operation
   in: takes in the two bit values
   out: returns the new value

*/
unsigned int exOr(unsigned int a , unsigned int b){
    return a ^ b;
}
/*
   Function: helper function for and operation
   in: takes in the two bit values
   out: returns the new value

*/
unsigned int and(unsigned int a , unsigned int b){
    return a & b;
}


/*
   Function: Functions brints the binary form
   in: takes in the new summed value
   out: returns the new value

*/
void binaryPrinter(unsigned int byte){
    printf("%u", (byte & (1 << 7)) >> 7);
    printf("%u", (byte & (1 << 6)) >> 6);
    printf("%u", (byte & (1 << 5)) >> 5);
    printf("%u", (byte & (1 << 4)) >> 4);
    printf("%u", (byte & (1 << 3)) >> 3);
    printf("%u", (byte & (1 << 2)) >> 2);
    printf("%u", (byte & (1 << 1)) >> 1);
    printf("%u", (byte & (1 << 0)) >> 0);
}