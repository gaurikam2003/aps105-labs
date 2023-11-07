/*
* This program converts an inputted amount of money into Canadian Dollars 
* based on an inputted conversion rate
*/
#include <stdio.h>
int main(){
    //declaring conversationRate, amount, and newAmount variables 
    double conversionRate;
    double amount;
    double newAmount;
    printf("Enter the conversion rate: ");
    scanf("%lf", &conversionRate);          //receiving user input for conversion rate
    printf("Enter the amount to be converted (in foreign currency): "); 
    scanf("%lf", &amount);                  //receiving user input for amount to be converted
    newAmount = conversionRate * amount;    //initializing newAmount variable for amount of Canadian Dollars
    printf("The amount in Canadian Dollars is: %.2lf", newAmount);  //printing out the converted amount with rounding to 2 points after decimal 
    return 0;
}