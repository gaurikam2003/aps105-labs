#include <stdio.h>
#include <math.h>

int main() {
  double weightInKg;
  double heightInM;
  double bmi;
  double userWeight;
  char userWeightUnit;
  char userWeightUnit2nd;
  double userHeight;
  char userHeightUnit;
  char userHeightUnit2nd;
  
  const double poundsToKilograms = 0.4536;
  const double InchesToMeters = 39.37;
  const double feetToMeters = 3.28;

  printf("Enter the body weight: ");
  scanf("%lf", &userWeight);
  scanf("%c", &userWeightUnit);
  scanf("%c", &userWeightUnit2nd);

  printf("Enter the height: ");
  scanf("%lf", &userHeight);
  scanf("%c", &userHeightUnit);
  scanf("%c", &userHeightUnit2nd);

  if (userWeightUnit == 'k') {
    weightInKg = userWeight;
  } else if (userWeightUnit == 'l') {
    weightInKg = userWeight * poundsToKilograms;
  }
  
  if (userHeightUnit == 'm'){
      heightInM = userHeight;
  }
  else if (userHeightUnit == 'f'){
      heightInM = userHeight / feetToMeters;
  }
  else if (userHeightUnit == 'i'){
      heightInM = userHeight / InchesToMeters;
  }


  bmi = weightInKg / pow(heightInM, 2);

  printf("\nThe Body Mass Index (BMI) is: %.1lf\n", bmi);
  if (bmi <18.5){
      printf("Category: Underweight");
  }
  else if (bmi >= 18.5 && bmi <=24.9){
      printf("Category: Healthy Weight");
  }
  else if (bmi >= 25.0 && bmi <30.0){
      printf("Category: Overweight");
  }
  else{
      printf("Category: Obesity");
  }
  return 0;
}