#include <math.h>
#include <stdio.h>

// This function prompts the user to enter a number
// and returns the entered number
int getNumber();
// This function reverses the digits of the given number
int reverseNumber(int);
int getAscendingOrderedDigits(int);

int main(void) {
  int x = getNumber();
  int ascendingNumber = 0;
  int descendingNumber = 0;
  int newNumber = 0;
  const int kaprekar = 6174;
  while (x != -1) {
    if (x < 1000) {
      printf("Error: The number is too small.\n");
    } else if (x > 9999) {
      printf("Error: The number is too large.\n");
    } else {
      int i = 1;
      while (x != kaprekar) {
        printf("Number %d: %d\n", i, x);
        ascendingNumber = getAscendingOrderedDigits(x);
        descendingNumber = reverseNumber(ascendingNumber);
        x = descendingNumber - ascendingNumber;
        i++;
      }
      printf("Number %d: %d\n", i, x);
      i = i - 1;
      printf("Kaprekar's Constant was reached in %d iteration(s)\n", i);
    }

    x = 0;
    x = getNumber();
  }
  return 0;
}

int getNumber() {
  int userInput;
  printf("Enter a number (-1 to stop): ");
  scanf(" %d", &userInput);
  return userInput;
}

int reverseNumber(int num){
  int reversedNumber = 0; 
  int remainder = 0;
  for (int i = 1; i<= 4; i++){
    remainder = num %10;
    num = num/10;
    reversedNumber = reversedNumber + remainder * (int) pow(10,4-i);
  }
  return reversedNumber;
}

/*int reverseNumber(int num) {
  int reversedNumber = 0;
  int remainder;

  if (num < 10) {
    num = num * 1000;
  } else if (num < 100) {
    num = num * 100;
  } else if (num < 1000) {
    num = num * 10;
  }

  while (num != 0) {
    remainder = num % 10;
    reversedNumber = reversedNumber * 10 + remainder;
    num /= 10;
  }
  return reversedNumber;
}
*/
int getAscendingOrderedDigits(int number) {
  int digits[10] = {0};
  while (number > 0) {
    digits[number % 10]++;
    number /= 10;
  }
  int i = 0;
  while (i < 10) {
    if (digits[i] > 0) {
      number *= 10;
      number += i;
      digits[i]--;
    } else {
      i++;
    }
  }
  return number;
}
