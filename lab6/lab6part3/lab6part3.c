#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

// Part 3: 4 marks
// Using calculateScoreInDir, it checks for each row/col,
// if it sees a line of 1's resulting from that startRow and startCol
// that is equal to difficulty level! Amazing it should return gameOver
bool gameStatus(int Size, char userArray[][Size], int difficultyLevel);

// You need to have implemented to proceed! But on Examify, we will add ours
void printBoard(int Size, char grid[][Size]);
bool validRowCol(int row, int col, int Size);
void updateRowCol(int* row, int* col, int dir, bool forward);
int calculateScoreInDir(int row, int col, int direction, int Size,
                        char userArray[][Size]);

int main(void) {
  const int maxDim = 23;
  int Size = 0, difficultyLevel = 0;
  printf("Enter size and difficulty level: ");
  scanf("%d %d", &Size, &difficultyLevel);

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
    }
  }

  int userInputRow = 0, userInputCol = 0;

  // test gameStatus
  char userArray[Size][Size];
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      userArray[row][col] = '-';
    }
  }
  bool gameOver = true;
  int steps = 0;
  do {
    printf("Enter row and col: ");
    scanf("%d %d", &userInputRow, &userInputCol);

    userArray[userInputRow][userInputCol] = grid[userInputRow][userInputCol];
    printBoard(Size, userArray);
    gameOver = gameStatus(Size, userArray, difficultyLevel);
    steps++;
  } while (!gameOver && steps < Size * Size);
  if (steps == Size * Size) {
    printf("Not a valid game!");
  } else {
    printf("Game over!");
  }

  return 0;
}

bool gameStatus(int Size, char userArray[][Size], int difficultyLevel) {
    bool status = false;
    for(int row = 0; row < Size; row++){
        for(int col = 0; col < Size; col++){
            for(int dir = 0; dir < 4; dir++)
            if( (calculateScoreInDir(row, col, dir, Size, userArray)) == difficultyLevel){
                status = true;
            } 
        }
    }
    return status;
  // you will need to call calculateScoreInDir
}

int calculateScoreInDir(int row, int col, int direction, int Size,
                        char userArray[][Size]) {
  // from part 2
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

void updateRowCol(int* row, int* col, int dir, bool forward) {
  // update Row and Col in forward/backward direction given direction
  // If direction is 0: row--, 1: row--, col++, 2: col++, 3: row--, col--
  // from part 2
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

void printBoard(int Size, char grid[][Size]) {
  // similar to part 1
  for (int row = 0; row < Size; row++) {
    for (int col = 0; col < Size; col++) {
      printf("%d", grid[row][col]);
    }
    printf("\n");
  }
}