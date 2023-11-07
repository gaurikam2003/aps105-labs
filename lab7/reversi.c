//
// Author: Gaurika Mahajan
//
#include "reversi.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void updateBoard(char board[][26], char color, int row, int col);
void printUpdatedBoard(char board[][26], int n);
void possibleMoves(char board[][26], int n, char color);
bool flipTiles(char board[][26], int n, char color, int row, int col);

int main() {
  int dimension;
  char boardConfig[4];
  char board[26][26];
  char move[4];

  printf("Enter the board dimension:");
  scanf("%d", &dimension);

  // where the function prints the board
  printBoard(board, dimension);

  printf("Enter board configuration:\n");
  scanf("%s", boardConfig);

  while (boardConfig[0] != '!') {
    char enteredColor = boardConfig[0];
    int enteredRow = boardConfig[1] - 'a';
    int enteredCol = boardConfig[2] - 'a';
    // board[enteredRow][enteredCol] = enteredColor;

    updateBoard(board, enteredColor, enteredRow, enteredCol);
    scanf("%s", boardConfig);
  }

  printUpdatedBoard(board, dimension);

  printf("Available moves for W:\n");
  possibleMoves(board, dimension, 'W');

  printf("Available moves for B:\n");
  possibleMoves(board, dimension, 'B');

  printf("Enter a move:\n");
  scanf("%s", move);
  char color = move[0];
  int row = move[1] - 'a';
  int col = move[2] - 'a';

  if (!flipTiles(board, dimension, color, row, col)){
    printf("Invalid move.\n");
  } else {
    printf("Valid move.\n");
  }
  /*
  if (flipTiles(board, dimension, move[0], move[1] - 'a', move[2] - 'a')) {
    printf("Valid move.\n");
  } else {
    printf("Invalid move.\n");
  }
  */

  printUpdatedBoard(board, dimension);
  return 0;
}

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
  printf("   ");
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

bool flipTiles(char board[][26], int n, char color, int row, int col) {
  bool empty = false;
  int originalRow = row;
  int originalCol = col;
  for (int k = -1; k < 2; k++) {
    for (int m = -1; m < 2; m++) {
      if (checkLegalInDirection(board, n, row, col, color, k, m)) {
        board[row][col] = color;
        empty = true;
        while (empty) {
          row = row + k;
          col = col + m;
          if (board[row][col] != color) {
            board[row][col] = color;
          } else {
            row = originalRow;
            col = originalCol;
            break;
          }
        }
      }
    }
  }
  return empty;
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