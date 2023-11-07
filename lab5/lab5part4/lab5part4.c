#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
void populateBoxes(int[], int);
void takeUserChoices(int[], int[], const int, const int);
bool validateChoices(int[], const int, const int);
void calculateScore(int[], const int, int[], int[], const int, int*,
                    int*);  // calculate the score of each user
void appendStatistics(int[], const int, int[]);
int frequentBox(int[], const int);

int main(void) {
  // don't set srand!
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int boxes[BoxesNum], userOne[ChoicesNum], userTwo[ChoicesNum],
      histogramUserOne[BoxesNum], histogramUserTwo[BoxesNum];
  int difference;
  bool done = false;
  int userOneScore = 0, userTwoScore = 0;
  for (int i = 0; i < BoxesNum; i++) {
    histogramUserOne[i] = 0;
    histogramUserTwo[i] = 0;
  }
  do {
    difference = userOneScore - userTwoScore;
    if (abs(difference) > 50) {
      done = true;
      break;
    } else if (difference < 50) {
      populateBoxes(boxes, BoxesNum);

      takeUserChoices(userOne, userTwo, ChoicesNum, BoxesNum);

      calculateScore(boxes, BoxesNum, userOne, userTwo, ChoicesNum,
                     &userOneScore, &userTwoScore);

      // Append Statistics for User One
      appendStatistics(userOne, ChoicesNum, histogramUserOne);
      // Append Statistics for User Two

      appendStatistics(userTwo, ChoicesNum, histogramUserTwo);

      printf("Player 1: %d.\nPlayer 2: %d.\n", userOneScore, userTwoScore);
    }
  } while (done == false);

  if (userOneScore - 50 > userTwoScore) {
    printf("User 1 wins, ");
    printf("and the first box they chose most frequently is: %d\n",
           frequentBox(histogramUserOne, BoxesNum));
  } else if (userTwoScore - 50 > userOneScore) {
    printf("User 2 wins, ");
    printf("and the first box they chose most frequently is: %d\n",
           frequentBox(histogramUserTwo, BoxesNum));
  }
  return 0;
}

void populateBoxes(int boxes[], const int BoxesNum) {
  // Fill each element randomly by either
  // 0 empty
  // -10 bomb
  // 10 candy
  // Print the contents of the boxes
  for (int i = 0; i < BoxesNum; i++) {
    boxes[i] = ((rand() % 3 - 1) * 10);
    if (i < BoxesNum - 1) {
      printf("%d: %d, ", i, boxes[i]);
    } else if (i == BoxesNum - 1) {
      printf("%d: %d, \n", i, boxes[i]);
    }
  }
}

void takeUserChoices(int userOne[], int userTwo[], const int ChoicesNum,
                     const int BoxesNum) {
  // Can check if the inputs are distinct and if they are between 1 and BoxesNum
  // - 1
  do {
    printf("Player 1, please enter distinct box choices between 0 and 19: ");
    for (int choiceInd = 0; choiceInd < ChoicesNum; choiceInd++) {
      scanf("%d", &userOne[choiceInd]);
    }
  } while (!validateChoices(userOne, ChoicesNum, BoxesNum));
  do {
    printf("Player 2, please enter distinct box choices between 0 and 19: ");
    for (int choiceInd = 0; choiceInd < ChoicesNum; choiceInd++) {
      scanf("%d", &userTwo[choiceInd]);
    }
  } while (!validateChoices(userTwo, ChoicesNum, BoxesNum));
}

bool validateChoices(int choices[], const int ChoicesNum, const int BoxesNum) {
  bool valid = true;
  // Check if elements in choices is between 0 and BoxesNum - 1
  // Check if elements in choices is distinct
  for (int i = 0; i < 5; i++) {
    if (choices[i] >= 0 && choices[i] <= BoxesNum - 1) {
      for (int j = i + 1; j < 5; j++) {
        if (choices[i] == choices[j]) {
          valid = false;
        }
      }
    } else {
      valid = false;
    }
  }
  return valid;
}

void calculateScore(int boxes[], const int BoxesNum, int userOne[],
                    int userTwo[], const int ChoicesNum, int* score1,
                    int* score2) {
  *score1 = 0;
  *score2 = 0;
  bool foundOne = false;
  bool foundTwo = true;
  for (int i = 0; i < BoxesNum; i++) {
    foundOne = false;
    foundTwo = false;

    if (boxes[i] == 10) {
      printf("Found 10 in boxes[%d].\n", i);
      for (int j = 0; j < ChoicesNum; j++) {
        if (i == userOne[j]) {
          foundOne = true;
        }
        if (i == userTwo[j]) {
          foundTwo = true;
        }
      }
      if (foundOne == true && foundTwo == true) {
        printf("Found index %d in player 1.\n", i);
        printf("Found index %d in player 2.\n", i);
        printf("+%d to players 1 and 2 scores.\n", 5);
        *score1 = *score1 + 5;
        *score2 = *score2 + 5;
        foundOne = false;
        foundTwo = false;
      } else if (foundOne == true) {
        printf("Found index %d in player 1.\n", i);
        printf("+%d to player 1 score.\n", boxes[i]);
        *score1 = *score1 + 10;
        foundOne = false;
      } else if (foundTwo == true) {
        printf("Found index %d in player 2.\n", i);
        printf("+%d to player 2 score.\n", boxes[i]);
        *score2 = *score2 + 10;
        foundTwo = false;
      }

    } else if (boxes[i] == -10) {
      printf("Found -10 in boxes[%d].\n", i);
      for (int j = 0; j < ChoicesNum; j++) {
        if (i == userOne[j]) {
          foundOne = true;
        }
        if (i == userTwo[j]) {
          foundTwo = true;
        }
        if (foundOne == true && foundTwo == true) {
          printf("Found index %d in player 1.\n", i);
          printf("Found index %d in player 2.\n", i);
          printf("-%d from player 1 score.\n", 10);
          printf("-%d from player 2 score.\n", 10);
          *score1 = *score1 - 10;
          *score2 = *score2 - 10;
          foundOne = false;
          foundTwo = false;
        } else if (foundOne == true) {
          printf("Found index %d in player 1.\n", i);
          printf("-%d from player 1 score.\n", 10);
          *score1 = *score1 - 10;
          foundOne = false;
        } else if (foundTwo == true) {
          printf("Found index %d in player 2.\n", i);
          printf("-%d from player 2 score.\n", 10);
          *score2 = *score2 - 10;
          foundTwo = false;
        }
      }
    }
  }
  // Get the score of each user
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
