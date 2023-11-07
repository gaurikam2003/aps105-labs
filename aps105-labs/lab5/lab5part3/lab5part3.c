#include <stdbool.h>
#include <stdio.h>
void calculateScore(int[], const int, int[], int[], const int, int*,
                    int*);  // calculate the score of each user
int main(void) {
  const int BoxesNum = 20;
  const int ChoicesNum = 5;
  int boxes[BoxesNum], userOne[ChoicesNum], userTwo[ChoicesNum];
  printf("Enter boxes content: ");
  for (int i = 0; i < BoxesNum; i++) {
    scanf("%d", &boxes[i]);
  }
  printf("Enter player 1 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userOne[i]);
  }
  printf("Enter player 2 choices: ");
  for (int i = 0; i < ChoicesNum; i++) {
    scanf("%d", &userTwo[i]);
  }
  int userOneScore = 0, userTwoScore = 0;
  calculateScore(boxes, BoxesNum, userOne, userTwo, ChoicesNum, &userOneScore,
                 &userTwoScore);
  printf("Player 1: %d.\nPlayer 2: %d.\n", userOneScore, userTwoScore);
  return 0;
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
