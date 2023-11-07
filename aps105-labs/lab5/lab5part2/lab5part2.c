#include <stdio.h>
void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]);
int frequentBox(int histogram[], const int BoxesNum);
int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int userOne[ChoicesNum], userOneHisto[BoxesNum];

  for (int i = 0; i < BoxesNum; i++) {
    userOneHisto[i] = 0;
  }

  int numOfTimes = 0;

  while (numOfTimes <= 5) {
    printf("Enter choices: ");
    for (int i = 0; i < 5; i++) {
      scanf("%d", &userOne[i]);
    }
    appendStatistics(userOne, ChoicesNum, userOneHisto);
    numOfTimes++;
  }
  
  for (int j = 0; j < BoxesNum; j++){
      if (j < BoxesNum - 1) {
      printf("%d: %d, ", j, userOneHisto[j]);
    } else if (j == BoxesNum - 1) {
      printf("%d: %d, \n", j, userOneHisto[j]);
    }
  }
  
  printf("The smallest and most frequently used box is: %d\n",
         frequentBox(userOneHisto, BoxesNum));
  return 0;
}

void appendStatistics(int userChoice[], const int ChoicesNum, int histogram[]) {
  for (int i = 0; i < ChoicesNum; i++) {
    histogram[userChoice[i]]++;
  }
  // Fill in the histogram with the number of times each index was picked
  // Print the histogram
}

int frequentBox(int histogram[], const int BoxesNum) {
  int largestBox = histogram[0];
  int largestIndex = 0;
  for (int i = 0; i < BoxesNum; i++) {
    if (histogram[i] > largestBox) {
      largestBox = histogram[i];
      largestIndex = i;
    }
  }
  return largestIndex;
  // Return the index having the maximum number in histogram
}