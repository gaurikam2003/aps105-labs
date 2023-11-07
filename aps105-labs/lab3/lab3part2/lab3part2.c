#include <stdio.h>
#include <math.h>

int main() {
  int radius;
  printf("Enter the radius of the circle: ");
  scanf("%d", &radius);
  int row = 0;
  int column = 0;
  int originX;
  int originY;
  double distance;
  for (row = 1; row <= 2 * radius + 1; row++) {
    for (column = 1; column <= 2 * radius + 1; column++) { 
      originX = ((2*radius) + 1)/2 + 1;  
      originY = ((2*radius) + 1)/2 + 1;
      distance = sqrt(pow(row-originX, 2) + pow(column - originY, 2));
      if ((distance) <= radius){
        printf("o");
      }
      else {
        printf(".");
      }
    }
    printf("\n");
  }
  return 0;
}