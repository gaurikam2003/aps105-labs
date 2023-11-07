#include <stdio.h>
int main() {
  const double CmPerInch = 2.54;
  const double CmPerMetre = 100.00;
  const int InchesPerFoot = 12;
  const int InchesPerYard = 36;
  double distance;            //changed variable type to be double instead of integer 
  printf("Please provide a distance in metres: ");  //this ensures that decimal numbers are correctly compiled 
  scanf("%lf", &distance);
  double distanceInInches = distance * CmPerMetre / CmPerInch;
  // truncate fractional part to get # of inches
  int inches = distanceInInches;
  distanceInInches = distanceInInches - inches;
  int yards = inches / InchesPerYard;
  // how many inches are left after extracting yards
  inches = inches % InchesPerYard;
  int feet = inches / InchesPerFoot;
  // how many inches are left after extracting feet
  inches = inches % InchesPerFoot;
  printf("%d yards, %d feet, %d inches, %.2f inches remainder\n", yards, feet,
         inches, distanceInInches);
  return 0;
}