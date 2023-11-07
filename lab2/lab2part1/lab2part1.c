#include <math.h>
#include <stdio.h>

int main() {
  double xValue;
  double yValue;
  double hypotenuse;
  double theta;

  printf("Enter X: ");
  scanf("%lf", &xValue);
  printf("Enter Y: ");
  scanf("%lf", &yValue);

  hypotenuse = sqrt(pow(xValue, 2.0) + pow(yValue, 2.0));
  theta = asin(yValue / hypotenuse) * (180.0 / M_PI);

  printf("The Hypotenuse Length is: %.1lf\n", hypotenuse);
  printf("The Angle Theta is: %.1lf degrees", theta);
  return 0;
}