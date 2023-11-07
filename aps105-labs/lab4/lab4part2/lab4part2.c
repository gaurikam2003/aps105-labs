#include <math.h>
#include <stdio.h>

int main() {
  int order = 0;
  printf("Enter the order of the function: ");
  scanf("%d", &order);

  while (order != -1) {
    int row = 0;
    int column = 0;
    int zeroCoefficient = 0;
    int firstCoefficient = 0;
    int secondCoefficient = 0;
    int thirdCoefficient = 0;
    if (order < 0 || order > 3) {
      printf("The order must be between [0, 3].\n");
    } else {
      if (order == 0) {
        printf("Enter coefficient of x^%d: ", 0);
        scanf("%d", &zeroCoefficient);

      } else if (order == 1) {
        printf("Enter coefficient of x^%d: ", 0);
        scanf("%d", &zeroCoefficient);
        printf("Enter coefficient of x^%d: ", 1);
        scanf("%d", &firstCoefficient);
      } else if (order == 2) {
        printf("Enter coefficient of x^%d: ", 0);
        scanf("%d", &zeroCoefficient);
        printf("Enter coefficient of x^%d: ", 1);
        scanf("%d", &firstCoefficient);
        printf("Enter coefficient of x^%d: ", 2);
        scanf("%d", &secondCoefficient);
      } else if (order == 3) {
        printf("Enter coefficient of x^%d: ", 0);
        scanf("%d", &zeroCoefficient);
        printf("Enter coefficient of x^%d: ", 1);
        scanf("%d", &firstCoefficient);
        printf("Enter coefficient of x^%d: ", 2);
        scanf("%d", &secondCoefficient);
        printf("Enter coefficient of x^%d: ", 3);
        scanf("%d", &thirdCoefficient);
      }
      for (row = 10; row >= -10; row--) {
        for (column = -10; column <= 10; column++) {
          if ((thirdCoefficient * pow(column, 3) +
               secondCoefficient * pow(column, 2) +
               firstCoefficient * pow(column, 1) + zeroCoefficient) == row) {
            printf(" * ");
          } else if (column == 0) {
            printf(" | ");
          } else if (row == 0) {
            printf(" - ");
          } else {
            printf("   ");
          }
        }
        printf("\n");
      }
    }
    printf("Enter the order of the function: ");
    scanf("%d", &order);
  }
  return 0;
}