#include <math.h>
#include <stdio.h>

int main() {
  char operation;
  int inputBase;
  int firstOperandOriginal;
  int secondOperandOriginal;
  int outputBase;
  int remainderFirst = 0;
  int remainderSecond = 0;
  int remainderOutput  = 0;
  int firstOperandDecimal = 0;
  int secondOperandDecimal = 0;
  int totalOperandDecimal = 0;
  int totalOperandOutput;
  int testDigit1 = 0;
  
  int testDigit2 = 0;
  printf("Give input ($ to stop): ");
  scanf("%c", &operation);
  while (operation != '$'){
    scanf(" %d %d %d %d", &inputBase, &firstOperandOriginal, &secondOperandOriginal, &outputBase);
      int firstOperand = firstOperandOriginal;
      int secondOperand = secondOperandOriginal;

      if (operation != '*' && operation != '/' && operation != '+' && operation != '-' ){
        printf("Invalid operator");
      } else if ((inputBase <= 2 && inputBase >= 10) || (outputBase <= 2 && outputBase >= 10) ){
        printf("Invalid base");
      }
      else {    //need to add bad input for number too large for base
        while (testDigit1 < inputBase && firstOperand != 0){
          testDigit1 = firstOperand % 10;
          firstOperand = firstOperand / 10;
        }
        while (testDigit2 < inputBase && secondOperand != 0){
          testDigit2 = secondOperand % 10;
          secondOperand = secondOperand / 10;
        }
        firstOperand = firstOperandOriginal;
        secondOperand = secondOperandOriginal;
        if (testDigit1 > inputBase || testDigit2 > inputBase){
          printf("Invalid digits in operand");
        }
        else {
          //converting the first number to decimal
          int i = 0;
          for (i = 0; firstOperand > 0; i++) {
            remainderFirst = firstOperand % 10;
            firstOperandDecimal = firstOperandDecimal + remainderFirst * pow(inputBase, i);
            firstOperand = firstOperand / 10;
          }
          //printf("The first operand in decimal is %d\n", firstOperandDecimal);

          //converting the second number to decimal
          int j = 0;
          for (j = 0; secondOperand > 0; j++) {
            remainderSecond = secondOperand % 10;
            secondOperandDecimal = secondOperandDecimal + remainderSecond * pow(inputBase, j);
            secondOperand = secondOperand / 10;
          }
          //printf("The second operand in decimal is %d\n", secondOperandDecimal);
          //adding up the two numbers in decimal
          if (operation == '+'){
            totalOperandDecimal = (int) firstOperandDecimal + secondOperandDecimal;
          } else if (operation == '-'){
            totalOperandDecimal = (int) firstOperandDecimal - secondOperandDecimal;
          } else if (operation == '*'){
            totalOperandDecimal = (int) firstOperandDecimal * secondOperandDecimal;
          } else if (operation == '/'){
            totalOperandDecimal = (int) firstOperandDecimal / secondOperandDecimal;
          } else {
            printf("Invalid Operator");
          }

          //printf("the total operand in base 10 is: %d\n", totalOperandDecimal);
          //converting the total to the outputBase 
          int k = 0;
          for (k = 1; totalOperandDecimal > 0; k *= 10){
            remainderOutput = totalOperandDecimal % outputBase;
            totalOperandOutput = totalOperandOutput + remainderOutput * k;
            totalOperandDecimal = totalOperandDecimal / outputBase;
          }
          //printf("the total operand in the new base is: %d\n", totalOperandOutput);
          printf("%d %c %d (base %d) = %d %c %d = %d (base %d)", firstOperandOriginal, operation, secondOperandOriginal, inputBase, firstOperandDecimal, operation, secondOperandDecimal, totalOperandOutput, outputBase);
        return 0;
      }
   }
  printf("Give input ($ to stop): ");
  scanf("%c", &operation);
  }
  return 0;
}
