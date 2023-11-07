/**
 * @file reversi.c
 * @author Gaurika Mahajan
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-14
 *
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
#include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printBoard(char board[][26], int n);
bool positionInBounds(int n, int row, int col);
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol);
void updateBoard(char board[][26], char color, int row, int col);
void printUpdatedBoard(char board[][26], int n);
void possibleMoves(char board[][26], int n, char color);
void flipTiles(char board[][26], int n, char color, int row, int col);
void flipTilesInDirection(char board[][26], int n, char color, int row, int col,
                          int deltaRow, int deltaCol);
void makeMove(char board[26][26], int n, char turn, int *row, int *col);
int scoringMove(char board[][26], int n, char color, int row, int col);
int scoringMoveInDirection(char board[][26], int n, char color, int row,
                           int col, int deltaRow, int deltaCol);
int playerWin(char board[][26], int n, char playerColor);
bool isValidMove(char board[][26], int n, char color, int row, int col);
bool moveAvailable(char board[][26], int n, char color);
bool boardFull(char board[][26], int n);

//*******************************************************
// Note: Please only put your main function below
// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
  // Write your own main function here
  int dimension;
  char board[26][26];
  char compColor;
  char playerColor;
  char moveRow;
  char moveCol;
  int moveRowNumber = 0;
  int moveColNumber = 0;
  int randomRow;
  int randomCol;

  printf("Enter the board dimension: ");
  scanf("%d", &dimension);

  printf("Computer plays (B/W): ");
  scanf(" %c", &compColor);

  if (compColor == 'W') {
    playerColor = 'B';
    printBoard(board, dimension);
  } else if (compColor == 'B') {
    playerColor = 'W';
    printBoard(board, dimension);
    makeMove(board, dimension, compColor, &randomRow, &randomCol);
    printUpdatedBoard(board, dimension);

  } else {
    printf("Invalid color. Restart the program.");
  }

 

  do {
    if (!moveAvailable(board, dimension, playerColor) && !moveAvailable(board, dimension, compColor) && boardFull(board, dimension)){
      playerWin(board, dimension, playerColor);
      break;
    }
    if (moveAvailable(board, dimension, playerColor)) {
      printf("Enter move for colour %c (RowCol): ", playerColor);
      scanf(" %c%c", &moveRow, &moveCol);

      moveRowNumber = moveRow - 'a';
      moveColNumber = moveCol - 'a';

      if (positionInBounds(dimension, moveRowNumber, moveColNumber) &&
          isValidMove(board, dimension, playerColor, moveRowNumber,
                      moveColNumber)) {
        flipTiles(board, dimension, playerColor, moveRowNumber, moveColNumber);
        board[moveRowNumber][moveColNumber] = playerColor;
        printUpdatedBoard(board, dimension);
      } else {
        printf("Invalid move.\n%c player wins.", compColor);
        //printf("%c player wins" , compColor);
        break;
      }
    } else if (moveAvailable(board, dimension, compColor)) {
      printf("%c player has no valid move.\n", playerColor);
    }

    if (moveAvailable(board, dimension, compColor)) {
      makeMove(board, dimension, compColor, &randomRow, &randomCol);
      printUpdatedBoard(board, dimension);
    } else if (moveAvailable(board, dimension, playerColor)) {
      printf("%c player has no valid move.\n", compColor);
    }
  } while (true);


  return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************

void printBoard(char board[][26], int n) {
  // char letterRow = 'a';
  // char letterCol = 'a';

  // assigning values to board
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if ((i == n / 2 - 1 && j == n / 2 - 1) || (i == n / 2 && j == n / 2)) {
        board[i][j] = 'W';
      } else if ((i == n / 2 - 1 && j == n / 2) ||
                 (i == n / 2 && j == n / 2 - 1)) {
        board[i][j] = 'B';
      } else {
        board[i][j] = 'U';
      }
    }
  }

  // actually printing the board here
  // printing the row of letters at the top
  char colLetter = 'a';
  printf("  ");
  for (int j = 0; j < n; j++) {
    printf("%c", colLetter);
    colLetter++;
  }
  printf("\n");
  char rowLetter = 'a';

  for (int i = 0; i < n; i++) {
    printf("%c ", rowLetter);
    rowLetter++;
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

bool positionInBounds(int n, int row, int col) {
  if (row >= n || row < 0 || col >= n || col < 0) {
    return false;
  } else {
    return true;
  }
}
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  char oppositeColor;
  int originalRow = row;
  int originalCol = col;
  int newRow = 0;
  int newCol = 0;
  bool empty = true;

  if (colour == 'W') {
    oppositeColor = 'B';
  } else if (colour == 'B') {
    oppositeColor = 'W';
  }

  if (!positionInBounds(n, row, col)) {
    return false;
  }

  if (deltaRow == 0 && deltaCol == 0) {
    return false;
  }
  newRow = row + deltaRow;
  newCol = col + deltaCol;

  if (!positionInBounds(n, newRow, newCol) ||
      board[newRow][newCol] != oppositeColor) {
    return false;
  }
  while (true) {
    newRow = newRow + deltaRow;
    newCol = newCol + deltaCol;
    // printf("%d%d", newRow, newCol);
    if (positionInBounds(n, newRow, newCol)) {
      if (board[newRow][newCol] == 'U') {
        return false;
      } else if (board[newRow][newCol] == oppositeColor) {
        continue;
        // empty = false;
      } else {
        return true;
      }
    } else {
      return false;
    }
  }
}

void updateBoard(char board[][26], char color, int row, int col) {
  // printf("%c", board[row][col]);
  board[row][col] = color;
}

void printUpdatedBoard(char board[][26], int n) {
  // actually printing the board here
  // printing the row of letters at the top
  char colLetter = 'a';
  printf("  ");
  for (int j = 0; j < n; j++) {
    printf("%c", colLetter);
    colLetter++;
  }
  printf("\n");
  char rowLetter = 'a';

  for (int i = 0; i < n; i++) {
    printf("%c ", rowLetter);
    rowLetter++;
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

void possibleMoves(char board[][26], int n, char color) {
  if (color == 'W') {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        bool random = false;
        if (board[i][j] == 'U') {
          for (int k = -1; k < 2; k++) {
            for (int m = -1; m < 2; m++) {
              if (checkLegalInDirection(board, n, i, j, 'W', k, m) && !random) {
                printf("%c%c", i + 97, j + 97);
                printf("\n");
                random = true;
                break;
              }
            }
          }
        }
      }

      // printf("%c%c", 97 + i, 97 + j);
    }
    // printf("\n");
  } else if (color == 'B') {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        bool random = false;
        if (board[i][j] == 'U') {
          for (int k = -1; k < 2; k++) {
            for (int m = -1; m < 2; m++) {
              if (checkLegalInDirection(board, n, i, j, 'B', k, m) && !random) {
                printf("%c%c", i + 97, j + 97);
                printf("\n");
                random = true;
              }
            }
          }
        }
      }

      // printf("%c%c", 97 + i, 97 + j);
    }
  }
}

void flipTiles(char board[][26], int n, char colour, int row, int col) {
  // calls another function to both check if it can flip tiles in a certain
  // direction, and then to actually flip them
  flipTilesInDirection(board, n, colour, row, col, -1, -1);
  flipTilesInDirection(board, n, colour, row, col, -1, 0);
  flipTilesInDirection(board, n, colour, row, col, -1, 1);
  flipTilesInDirection(board, n, colour, row, col, 0, -1);
  flipTilesInDirection(board, n, colour, row, col, 0, 1);
  flipTilesInDirection(board, n, colour, row, col, 1, -1);
  flipTilesInDirection(board, n, colour, row, col, 1, 0);
  flipTilesInDirection(board, n, colour, row, col, 1, 1);
}

void flipTilesInDirection(char board[][26], int n, char color, int row, int col,
                          int deltaRow, int deltaCol) {
  int counter;
  char oppColour;

  if (color == 'W') {
    oppColour = 'B';
  } else if (color == 'B') {
    oppColour = 'W';
  }

  if (board[row][col] == 'U') {
    if (checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol)) {
      for (counter = 1;; counter++) {
        if (board[row + deltaRow * counter][col + deltaCol * counter] ==
            oppColour) {
          board[row + deltaRow * counter][col + deltaCol * counter] = color;
        } else if (board[row + deltaRow * counter][col + deltaCol * counter] ==
                   color) {
          return;
        }
      }
    } else {
      return;
    }
  }
  return;
}
//char board[26][26], int n, char turn, int *row, int *col
void makeMove(char board[26][26], int n, char turn, int *row, int *col) {
  int score = 0;
  int bestRow = 0;
  int bestCol = 0;
  int maxScore = 0;

  for (int i = n-1; i >= 0 ; i--) {
    for (int j = n-1; j >= 0; j--) {
      if (board[i][j] == 'U' && isValidMove(board, n, turn, i, j)) {
        score = scoringMove(board, n, turn, i, j);
        if (score >= maxScore) {
          maxScore = score;
          bestRow = i;
          bestCol = j;
          *row = i;
          *col = j;
        }
      }
    }
  }
  // flipping the tiles in the best scoring position, and then informing the
  // player
  flipTiles(board, n, turn, bestRow, bestCol);
  board[bestRow][bestCol] = turn;
  printf("Computer places %c at %c%c.\n", turn, bestRow + 'a', bestCol + 'a');
}

int scoringMove(char board[][26], int n, char color, int row, int col) {
  int score = 0;
  score = scoringMoveInDirection(board, n, color, row, col, -1, -1) +
          scoringMoveInDirection(board, n, color, row, col, -1, 0) +
          scoringMoveInDirection(board, n, color, row, col, -1, 1) +
          scoringMoveInDirection(board, n, color, row, col, 0, -1) +
          scoringMoveInDirection(board, n, color, row, col, 0, 1) +
          scoringMoveInDirection(board, n, color, row, col, 1, -1) +
          scoringMoveInDirection(board, n, color, row, col, 1, 0) +
          scoringMoveInDirection(board, n, color, row, col, 1, 1);
  return score;
}

int scoringMoveInDirection(char board[][26], int n, char color, int row,
                           int col, int deltaRow, int deltaCol) {
  int counter;
  int score = 0;
  char oppositeColour;

  if (color == 'W') {
    oppositeColour = 'B';
  } else if (color == 'B') {
    oppositeColour = 'W';
  }

  if (board[row][col] == 'U') {
    if (checkLegalInDirection(board, n, row, col, color, deltaRow, deltaCol)) {
      for (counter = 1;; counter++) {
        if (board[row + deltaRow * counter][col + deltaCol * counter] ==
            oppositeColour) {
          score++;
        } else if (board[row + deltaRow * counter][col + deltaCol * counter] ==
                   color) {
          return score;
        }
      }
    } else {
      return 0;
    }
  }
  return 0;
}

int playerWin(char board[][26], int n, char playerColor) {
  int playerScore = 0;
  int compScore = 0;
  char oppositeColor;

  if (playerColor == 'W') {
    oppositeColor = 'B';
  } else if (playerColor == 'B') {
    oppositeColor = 'W';
  }

  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (board[row][col] == playerColor) {
        playerScore++;
      } else if (board[row][col] == oppositeColor) {
        compScore++;
      }
    }
  }

  if (playerScore > compScore) {
    printf("%c player wins.", playerColor);
    return 0;
  } else if (playerScore == compScore) {
    printf("The game ended in a tie.");
    return 0;
  } else {
    printf("%c player wins.", oppositeColor);
    return 0;
  }
  return 0;
}

bool isValidMove(char board[][26], int n, char color, int row, int col) {
  if (board[row][col] == 'U') {
    if (checkLegalInDirection(board, n, row, col, color, -1, -1)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, -1, 0)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, -1, 1)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, 0, -1)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, 0, 1)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, 1, -1)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, 1, 0)) {
      return true;
    } else if (checkLegalInDirection(board, n, row, col, color, 1, 1)) {
      return true;
    } else {
      return false;
    }
  } else {
    return false;
  }
}

bool moveAvailable(char board[][26], int n, char color) {
  for (int row = 0; row < n; row++) {
    for (int col = 0; col < n; col++) {
      if (isValidMove(board, n, color, row, col)) {
        return true;
      }
    }
  }
  return false;
}

bool boardFull(char board[][26], int n){
  for(int i = 0; i < n; i ++){
    for (int j = 0; j< n; j++){
      if(board[i][j] == 'U'){
        return false;
      } else {
        return true;
      }
    }
  }
}