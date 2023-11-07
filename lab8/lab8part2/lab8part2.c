/**
 * @file reversi.c
 * @author Luna Sun
 * @brief This file is used for APS105 Lab 8. 2023W version
 * @date 2023-03-30
 *
 */

// DO NOT REMOVE THE FOLLOWING LINE
#if !defined(TESTER_P1) && !defined(TESTER_P2)
// DO NOT REMOVE THE ABOVE LINE
// #include "reversi.h"
// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE

#include <stdbool.h>
#include <stdio.h>

// prints the current state of the board
void printBoard(char board[][26], int n) {
  // prints the top row of letters
  printf("  ");
  char letter = 'a';
  for (int next = 0; next < n; next++) {
    printf("%c", letter + next);
  }
  printf("\n");

  // prints the left column of letters and the board
  for (int i = 0; i < n; i++) {
    printf("%c ", letter + i);
    for (int j = 0; j < n; j++) {
      printf("%c", board[i][j]);
    }
    printf("\n");
  }
}

// check whether the specified (row, col) is in the board dimensions
bool positionInBounds(int n, int row, int col) {
  if (row >= 0 && row <= (n - 1) && col >= 0 && col <= (n - 1)) {
    return true;
  } else {
    return false;
  }
}

// checks if (row, col) is a legal position by "looking" in the direction of
// deltaRow and deltaCol deltaRow and deltaCol take on values of -1, 0, and 1,
// they cannot both be 0 if deltaRow = 1 and deltaCol = 0
bool checkLegalInDirection(char board[][26], int n, int row, int col,
                           char colour, int deltaRow, int deltaCol) {
  // check if the space is empty
  if (board[row][col] != 'U') {
    return false;
  }

  // find the opposite player's colour
  char opponent = 'W';
  if (colour == 'W') {
    opponent = 'B';
  }

  // go to the next cell in the specified direction
  row = row + deltaRow;
  col = col + deltaCol;

  // check if in board and if the next cell is occupied by an opponent
  if (!positionInBounds(n, row, col) || board[row][col] != opponent) {
    return false;
  }

  // keep going until an empty space or until player colour is found
  while (true) {
    row = row + deltaRow;
    col = col + deltaCol;
    if (!positionInBounds(n, row, col) || board[row][col] == 'U') {
      return false;
    }
    if (board[row][col] == colour) {
      return true;
    }
  }
}

// flips the opponent's color after a move
bool flip(char board[][26], int n, int row, int col, char colour, int deltaRow,
          int deltaCol) {
  // find the opposite player's colour
  char opponent;
  if (colour == 'W') {
    opponent = 'B';
  } else {
    opponent = 'W';
  }

  // go to the next cell in the specified direction
  row = row + deltaRow;
  col = col + deltaCol;

  // check if in board and if the next cell is occupied by an opponent
  if (!positionInBounds(n, row, col) || board[row][col] != opponent) {
    return false;
  }

  // keep going until an empty space or until player colour is found
  while (true) {
    row = row + deltaRow;
    col = col + deltaCol;
    if (!positionInBounds(n, row, col) || board[row][col] == 'U') {
      return false;
    }
    if (board[row][col] == colour) {
      // flip the opponent's pieces in between
      row -= deltaRow;
      col -= deltaCol;
      while (board[row][col] == opponent) {
        board[row][col] = colour;
        row -= deltaRow;
        col -= deltaCol;
      }
      return true;
    }
  }
}

int getScoreInDirection(char board[][26], int n, int row, int col, char turn,
                        int deltaRow, int deltaCol) {
  int score = 0;
  char opponent;
  if (turn == 'W') {
    opponent = 'B';
  } else {
    opponent = 'W';
  }

  // move to the next cell in the specified direction
  row += deltaRow;
  col += deltaCol;

  // check if the next cell is in bounds and is occupied by an opponent's piece
  if (!positionInBounds(n, row, col) || board[row][col] != opponent) {
    return 0;
  }

  // keep going until an empty space or until player colour is found
  while (positionInBounds(n, row, col)) {
    if (board[row][col] == 'U') {
      return 0;
    } else if (board[row][col] == turn) {
      return score;
    } else {
      score++;
    }

    // move to the next cell in the specified direction
    row += deltaRow;
    col += deltaCol;
  }

  return 0;
}

int makeMove(char board[26][26], int n, char turn, int *row, int *col) {
  int deltaRow = 0, deltaCol = 0;
  char opponent = 'W';
  if (turn == 'W') {
    opponent = 'B';
  }
  char moves[676][3];
  int count = 0, bestScore = 0;
  int bestRow = n, bestCol = n;
  int *scoreInDir = 0;

  // check available moves for current player
  for (int availr = 0; availr < n; availr++) {
    for (int availc = 0; availc < n; availc++) {
      if (board[availr][availc] == 'U') {
        int score = 0;
        // check if move is legal in any direction
        for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow != 0 || deltaCol != 0) {
              if (checkLegalInDirection(board, n, availr, availc, turn,
                                        deltaRow, deltaCol)) {
                score += getScoreInDirection(board, n, availr, availc, turn,
                                             deltaRow, deltaCol);
                // check if move already exists in wMoves array
                int moveExists = 0;
                for (int i = 0; i < count; i++) {
                  if (moves[i][0] == availr + 'a' &&
                      moves[i][1] == availc + 'a') {
                    moveExists = 1;
                    i = count;
                  }
                }

                // add move to wMoves array if it does not already exist
                if (!moveExists && score > 0) {
                  moves[count][0] = availr + 'a';
                  moves[count][1] = availc + 'a';
                  moves[count][2] = '\0';
                  count++;

                  // update best move if score is higher or if score is equal
                  // but row
                  // and col are lower
                  if (score > bestScore ||
                      (score == bestScore && availr < bestRow) ||
                      (score == bestScore && availr == bestRow &&
                       availc < bestCol)) {
                    bestScore = score;
                    bestRow = availr;
                    bestCol = availc;
                  }
                }
              }
            }
          }
        }
      }
    }

    // set row and col to best move and return
    *row = bestRow;
    *col = bestCol;
    return 0;
  }
}

// DO NOT REMOVE THE FOLLOWING LINE
#ifndef TESTER_P2
// DO NOT REMOVE THE ABOVE LINE

int main(void) {
  // n is the board dimension
  int n = 0;
  char board[26][26];
  int gameOver = 0;
  printf("Enter the board dimension: ");
  scanf(" %d", &n);

  // asks user what color they want to play; black always gets the first move
  int compRow = 0, compCol = 0;
  char compColor, userColor = 'B';
  printf("Computer plays (B/W): ");
  scanf(" %c", &compColor);
  if (compColor == 'B') {
    userColor = 'W';
  }

  // print beginning board of n size with the four beginning pieces
  for (int r = 0; r < n; r++) {
    for (int c = 0; c < n; c++) {
      board[r][c] = 'U';
    }
  }
  board[n / 2 - 1][n / 2 - 1] = 'W';
  board[n / 2][n / 2] = 'W';
  board[n / 2 - 1][n / 2] = 'B';
  board[n / 2][n / 2 - 1] = 'B';
  printBoard(board, n);

  do {
    int deltaRow, deltaCol;
    char wMoves[676][3], bMoves[676][3];
    int wCount = 0, bCount = 0;

    // check available moves for each player
    for (int availr = 0; availr < n; availr++) {
      for (int availc = 0; availc < n; availc++) {
        if (board[availr][availc] == 'U') {
          // check if move is legal in any direction
          for (deltaRow = -1; deltaRow <= 1; deltaRow++) {
            for (deltaCol = -1; deltaCol <= 1; deltaCol++) {
              if (deltaRow != 0 || deltaCol != 0) {
                if (checkLegalInDirection(board, n, availr, availc, 'W',
                                          deltaRow, deltaCol)) {
                  // check if move already exists in wMoves array
                  int moveExists = 0;
                  for (int i = 0; i < wCount; i++) {
                    if (wMoves[i][0] == availr + 'a' &&
                        wMoves[i][1] == availc + 'a') {
                      moveExists = 1;
                      i = wCount;
                    }
                  }

                  // add move to wMoves array if it does not already exist
                  if (!moveExists) {
                    wMoves[wCount][0] = availr + 'a';
                    wMoves[wCount][1] = availc + 'a';
                    wMoves[wCount][2] = '\0';
                    wCount++;
                  }
                } else if (checkLegalInDirection(board, n, availr, availc, 'B',
                                                 deltaRow, deltaCol)) {
                  // check if move already exists in bMoves array
                  int moveExists = 0;
                  for (int i = 0; i < bCount; i++) {
                    if (bMoves[i][0] == availr + 'a' &&
                        bMoves[i][1] == availc + 'a') {
                      moveExists = 1;
                      i = bCount;
                    }
                  }

                  // add move to bMoves array if it does not already exist
                  if (!moveExists) {
                    bMoves[bCount][0] = availr + 'a';
                    bMoves[bCount][1] = availc + 'a';
                    bMoves[bCount][2] = '\0';
                    bCount++;
                  }
                }
              }
            }
          }
        }
      }
    }

    if (compColor == 'B') {
      makeMove(board, n, 'B', &compRow, &compCol);
      board[compRow][compCol] = compColor;
      for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
        for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
          if (deltaRow != 0 || deltaCol != 0) {
            if (flip(board, n, compRow, compCol, userColor, deltaRow,
                     deltaCol)) {
              int r = compRow + deltaRow;
              int c = compCol + deltaCol;
              while (board[r][c] != compColor) {
                board[r][c] = compColor;
                r = r + deltaRow;
                c = c + deltaCol;
              }
            }
          }
        }
      }
      printBoard(board, n);

      // player turn
      // asks for player move
      char rowLetter, colLetter;
      int rowToNum = 0, colToNum = 0;
      printf("Enter move for colour %c (RowCol): ", userColor);
      scanf(" %c%c", &rowLetter, &colLetter);
      rowToNum = rowLetter - 'a';
      colToNum = colLetter - 'a';

      // check if move is valid
      int validMove = 0;
      for (int i = 0; i < wCount; i++) {
        if (wMoves[i][0] == rowLetter && wMoves[i][1] == colLetter) {
          validMove = 1;
          i = wCount;
        }
      }

      // print result
      if (validMove) {
        // update board with player's move
        board[rowToNum][colToNum] = userColor;
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow != 0 || deltaCol != 0) {
              if (flip(board, n, rowToNum, colToNum, userColor, deltaRow,
                       deltaCol)) {
                int r = rowToNum + deltaRow;
                int c = colToNum + deltaCol;
                while (board[r][c] != userColor) {
                  board[r][c] = userColor;
                  r = r + deltaRow;
                  c = c + deltaCol;
                }
              }
            }
          }
        }
        printBoard(board, n);
      } else {
        printf("Invalid move.\n%c player wins.", compColor);
        gameOver = 1;
      }
    } else {
      // asks for player move
      char rowLetter, colLetter;
      int rowToNum = 0, colToNum = 0;
      printf("Enter move for colour %c (RowCol): ", userColor);
      scanf(" %c%c", &rowLetter, &colLetter);
      rowToNum = rowLetter - 'a';
      colToNum = colLetter - 'a';

      // check if move is valid
      int validMove = 0;
      for (int i = 0; i < bCount; i++) {
        if (bMoves[i][0] == rowLetter && bMoves[i][1] == colLetter) {
          validMove = 1;
          i = bCount;
        }
      }

      // print result
      if (validMove) {
        // update board with player's move
        board[rowToNum][colToNum] = userColor;
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow != 0 || deltaCol != 0) {
              if (flip(board, n, rowToNum, colToNum, userColor, deltaRow,
                       deltaCol)) {
                int r = rowToNum + deltaRow;
                int c = colToNum + deltaCol;
                while (board[r][c] != userColor) {
                  board[r][c] = userColor;
                  r = r + deltaRow;
                  c = c + deltaCol;
                }
              }
            }
          }
        }

        makeMove(board, n, 'W', &compRow, &compCol);
        board[compRow][compCol] = compColor;
        for (int deltaRow = -1; deltaRow <= 1; deltaRow++) {
          for (int deltaCol = -1; deltaCol <= 1; deltaCol++) {
            if (deltaRow != 0 || deltaCol != 0) {
              if (flip(board, n, compRow, compCol, userColor, deltaRow,
                       deltaCol)) {
                int r = compRow + deltaRow;
                int c = compCol + deltaCol;
                while (board[r][c] != compColor) {
                  board[r][c] = compColor;
                  r = r + deltaRow;
                  c = c + deltaCol;
                }
              }
            }
          }
        }

        printBoard(board, n);
      } else {
        printf("Invalid move.\n%c player wins.", compColor);
        gameOver = 1;
      }
    }
  } while (gameOver = 0);

  return 0;
}

// DO NOT REMOVE THE FOLLOWING LINE
#endif
// DO NOT REMOVE THE ABOVE LINE
//*******************************************************