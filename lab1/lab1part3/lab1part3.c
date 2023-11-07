/*
* This program converts a base 10 number from 0 to 15 (inclusive) into base 2.
* It then prints out the base 2 conversion with each digit displayed on a new line.
*/
#include <stdio.h>
int main(void) {
    //declaring the base 10 number to be converted, mostSignificantDigit, nextDigit1, leastSignificantDigit
    int number;                 
    int mostSignificantDigit;   
    int nextDigit1;             
    int nextDigit2;             
    int leastSignificantDigit;  
    printf("Enter number to convert to base 2: ");
    scanf("%d", &number);       //taking in user input for the number to be converted 
    leastSignificantDigit = number%2;   //initializing the leastSignificantDigit 
    number = number/2;                  
    nextDigit2 = number % 2;            //initializing the nextDigit2
    number = number/2;                  
    nextDigit1 = number%2;              //initializing the leastSignificantDigit1
    number = number/2;                  
    mostSignificantDigit = number % 2;  //initializing the mostSignificantDigit
    printf("The four digits of that number are as follows:");       
    //printing out the four digits of base 2 conversion
    printf("\nMost significant digit: %d", mostSignificantDigit);   
    printf("\nNext digit: %d", nextDigit1);
    printf("\nNext digit: %d", nextDigit2);
    printf("\nLeast significant digit: %d", leastSignificantDigit);
    return 0;
}