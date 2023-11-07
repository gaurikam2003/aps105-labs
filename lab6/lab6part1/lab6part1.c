#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void printBoard(int Size, int grid[][Size]);
void getInput(int* row, int* col, int Size);
void getLevelAndDimensions(int* size, int* difficultyLevel, const int maxDim);
bool validRowCol(int row, int col, int Size);

int main(void) {
  const int maxDim = 23;
  int Size = 0, difficultyLevel = 0;

  getLevelAndDimensions(&Size, &difficultyLevel, maxDim);

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

  int grid[Size][Size];
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      grid[row][col] = copy[row][col];
    }
  }
  printBoard(Size, grid);

  int userInputRow = 0, userInputCol = 0;
  getInput(&userInputRow, &userInputCol, Size);
  printf("row, col = %d, %d\n", userInputRow, userInputCol);
  grid[userInputRow][userInputCol] = 9;  // any arbitrary number
  printBoard(Size, grid);

  return 0;
}

void getInput(int* row, int* col, int Size) {
  printf("Enter user input: ");
  scanf("%d %d", row, col);

  while (validRowCol(*row, *col, Size) == false) {
    printf("Please enter your row and col to be between 0 and Size - 1: ");
    scanf("%d %d", row, col);
  }
}

bool validRowCol(int row, int col, int Size) {
  bool isValid = false;
  if ((row < 0 || row >= Size) || (col < 0 || col >= Size)) {
    isValid = false;
  } else {
    isValid = true;
  }
  return isValid;
}

void getLevelAndDimensions(int* Size, int* levelOfDiff, const int maxDim) {
  printf("Enter the difficulty level: ");
  scanf("%d", levelOfDiff);

  while (*levelOfDiff < 1 || *levelOfDiff > maxDim) {
    printf("Please enter a difficulty level between 1 and %d: ", maxDim);
    scanf("%d", levelOfDiff);
  }

  printf("Enter the dimensions of the grid: ");
  scanf("%d", Size);
  while (*Size < *levelOfDiff || *Size > maxDim) {
    printf("Please enter dimensions >= %d: ", *levelOfDiff);
    scanf("%d", Size);
  }
  return;
}

void printBoard(int Size, int grid[][Size]) {
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      printf("%d", grid[row][col]);
    }
    printf("\n");
  }
}