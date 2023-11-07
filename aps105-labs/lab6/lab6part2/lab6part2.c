#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void updateRowCol(int* row, int* col, int dir, bool forward);
int calculateScoreInDir(int row, int col, int direction, int Size,
                        char userArray[][Size]);
bool validRowCol(int row, int col, int Size);

int main(void) {
  const int maxDim = 23;
  int Size = 0;
  printf("Enter size: ");
  scanf("%d", &Size);

  int copy[23][23] = {
      {1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1},
      {1, 0, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1},
      {0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0},
      {1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1},
      {1, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1},
      {0, 0, 1, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0},
      {1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1},
      {1, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 1, 0, 0, 1, 0, 0, 0, 1, 1},
      {1, 1, 1, 1, 1, 1, 0, 0, 1, 0, 1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 1},
      {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0},
      {1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 1, 1, 1, 0, 0, 0, 1},
      {0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1},
      {0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1},
      {1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 1},
      {0, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1},
      {1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0, 1},
      {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0},
      {0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1},
      {1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0},
      {1, 1, 0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
      {1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 0, 1, 1, 0, 1},
      {1, 1, 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1}};

  char grid[Size][Size];
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      grid[row][col] = copy[row][col] + '0';
      printf("%c ", grid[row][col]);
    }
    printf("\n");
  }

  // call calculateScoreInDir here to check if it works as expected!
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      printf("Row: %d, Col: %d, in direction\n", row, col);
      printf(" 0 ");
      printf("Score: %d.\n", calculateScoreInDir(row, col, 0, Size, grid));
      printf(" 1 ");
      printf("Score: %d.\n", calculateScoreInDir(row, col, 1, Size, grid));
      printf(" 2 ");
      printf("Score: %d.\n", calculateScoreInDir(row, col, 2, Size, grid));
      printf(" 3 ");
      printf("Score: %d.\n", calculateScoreInDir(row, col, 3, Size, grid));
    }
  }

  return 0;
}

int calculateScoreInDir(int row, int col, int direction, int Size,
                        char userArray[][Size]) {
  // Check in the forward direction how many 1s are there,
  // plus how many 1s are there in the backward direction
  int numOfOnes = 0;
  int testingRow = row;
  int testingCol = col;
  bool forward = true;
  bool found = true;

  while (validRowCol(testingRow, testingCol, Size) && found) {
    if (userArray[testingRow][testingCol] == '1') {
      numOfOnes++;
    } else {
      found = false;
    }
    updateRowCol(&testingRow, &testingCol, direction, forward);
  }

  forward = false;
  testingRow = row;
  testingCol = col;
  updateRowCol(&testingRow, &testingCol, direction, forward);

  while (validRowCol(testingRow, testingCol, Size) && found) {
    if (userArray[testingRow][testingCol] == '1') {
      numOfOnes++;
    } else {
      found = false;
    }
    updateRowCol(&testingRow, &testingCol, direction, forward);
  }
  return numOfOnes;
}

void updateRowCol(int* row, int* col, int dir, bool forward) {
  // update Row and Col in forward/backward direction given direction
  // If direction is 0: row--, 1: row-- and col++, 2: col++, 3: row-- and col--
  if (forward == true) {
    if (dir == 0) {
      *row += -1;
      *col += 0;
    } else if (dir == 1) {
      *row -= 1;
      *col += 1;
    } else if (dir == 2) {
      *row += 0;
      *col += 1;
    } else if (dir == 3) {
      *row -= 1;
      *col -= 1;
    } else {
      // invalid direction, do nothing
      return;
    }
  } else {
    // backward movement
    if (dir == 0) {
      *row += 1;
      *col += 0;
    } else if (dir == 1) {
      *row += 1;
      *col -= 1;
    } else if (dir == 2) {
      *row += 0;
      *col -= 1;
    } else if (dir == 3) {
      *row += 1;
      *col += 1;
    } else {
      // invalid direction, do nothing
      return;
    }
  }
}

bool validRowCol(int row, int col, int Size) {
  // from part 1
  bool isValid = false;
  if ((row < 0 || row >= Size) || (col < 0 || col >= Size)) {
    isValid = false;
  } else {
    isValid = true;
  }
  return isValid;
}