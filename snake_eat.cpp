#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char BLANK_CHAR      = ' ';
char WALL_CHAR       = '*';
char SNAKE_HEAD_CHAR = 'H';
char SNAKE_BODY_CHAR = 'X';
char FOOD_CHAR       = '$';

char map[12][13] = {
  "************",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "*          *",
  "************",
};

int snakeHeadX = 1, snakeHeadY = 1;
int snakeBodyX[100] = {0}, snakeBodyY[100] = {0};
int snakeBodyLen = 0;
int snakeTailIndex = -1;
int willBeLonger = 0;

int foodX = 0, foodY = 0;

int gameRunning = 1;

void printMap() {
  system("cls");
  for (int i = 0; i < 12; ++i) {
    printf("%s\n", map[i]);
  }
}

void spawnFood() {
  // Random food position
  foodX = rand() % 10 + 1;
  foodY = rand() % 10 + 1;
  while (map[foodX][foodY] != BLANK_CHAR) {
    foodX = rand() % 10 + 1;
    foodY = rand() % 10 + 1;
  }
  map[foodX][foodY] = FOOD_CHAR;
}

void initGame() {
  // Initialize snake
  snakeHeadX = snakeHeadY = 1;
  map[snakeHeadX][snakeHeadY] = SNAKE_HEAD_CHAR;
  snakeBodyLen = 0;
  gameRunning = 1;
  snakeTailIndex = -1;
  willBeLonger = 0;
  // Initialize food
  spawnFood();
  // Initialize game
  gameRunning = 1;

  printMap();
}

void gameOver() {
  printf("GAME OVER!!\n");
  gameRunning = 0;
}

void snakeMove(char control) {
  map[snakeHeadX][snakeHeadY] = BLANK_CHAR;
  // record the previous snake head position
  int prevSnakeHeadX = snakeHeadX;
  int prevSnakeHeadY = snakeHeadY;
  switch (control) {
   case 'w':
    snakeHeadX--;
    break;
   case 'a':
    snakeHeadY--;
    break;
   case 's':
    snakeHeadX++;
    break;
   case 'd':
    snakeHeadY++;
    break;
   default:
    return;
  }
  if (map[snakeHeadX][snakeHeadY] != BLANK_CHAR && map[snakeHeadX][snakeHeadY] != FOOD_CHAR) {
    // DIED
    gameOver();
  }
  map[snakeHeadX][snakeHeadY] = SNAKE_HEAD_CHAR;

  int moved = 0;
  // If willBeLonger, then make it longer
  if (willBeLonger) {
    willBeLonger = 0;
    moved = 1;
    // make space
    for (int i = snakeBodyLen - 1; i > snakeTailIndex; --i) {
      snakeBodyX[i + 1] = snakeBodyX[i];
      snakeBodyY[i + 1] = snakeBodyY[i];
    }
    snakeBodyX[snakeTailIndex + 1] = prevSnakeHeadX;
    snakeBodyY[snakeTailIndex + 1] = prevSnakeHeadY;
    if (snakeTailIndex < 0) snakeTailIndex = 0;
    map[prevSnakeHeadX][prevSnakeHeadY] = SNAKE_BODY_CHAR;
    snakeBodyLen++;
  }

  // Check if ate food
  if (snakeHeadX == foodX && snakeHeadY == foodY) {
    willBeLonger = 1;
    spawnFood();
  }

  // Head has already moved, **Move the body**
  // if "no body" here or added tail just now, then it needn't move
  if (snakeBodyLen <= 0 || moved) return;
  map[snakeBodyX[snakeTailIndex]][snakeBodyY[snakeTailIndex]] = BLANK_CHAR;
  snakeBodyX[snakeTailIndex] = prevSnakeHeadX;
  snakeBodyY[snakeTailIndex] = prevSnakeHeadY;
  map[prevSnakeHeadX][prevSnakeHeadY] = SNAKE_BODY_CHAR;
  // Move tail index
  snakeTailIndex = (snakeTailIndex - 1 + snakeBodyLen) % snakeBodyLen;
}

int main() {
  // Initialize random seed
  srand(time(NULL));

  initGame();

  char control = 0;
  while (gameRunning) {
    scanf(" %c", &control); // " %c": the space is used to skip blank character, like '\n'
    snakeMove(control);
    printMap();
  }

  return 0;
}
