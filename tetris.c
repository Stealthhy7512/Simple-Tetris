#include <stdio.h>
#include <stdlib.h>
#include <time.h>

const char shapes[7][3][3] = {{{'x', 'x', 'x'}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', 'x', ' '}, {'x', 'x', ' '}, {' ', ' ', ' '}}, 
        {{'x', ' ', ' '}, {'x', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}, 
        {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', 'x', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', ' ', ' '}}, 
        {{' ', 'x', 'x'}, {'x', 'x', ' '}, {' ', ' ', ' '}}};

void printShape(char* shapes)
{
  int i, j;
  for(i = 0; i < 3; i++) {
    for(j = 0; j < 3; j++) {
      printf("%c", *(shapes + 3*i + j));
    }
    printf("\n");
  }
}

char* rotateShape(char* shape)
{
  int i, j;
  char* transposed;
  transposed = (char*) malloc(9);
   for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            *(transposed + 3*i + j) = *(shape + 3*j + i);
        }
    }
  return transposed;
}

void placeShape(int coX, int coY, char* shape, char* playground, int size)
{
  int i, j;
  for(i = coY; i < coY+3; i++) {
    for(j = coX; j < coX+3; j++) {
      if(*(shape + 3*i + j) != ' ')
        *(playground + size*i + j) = *(shape + 3*i + j);
    }
  }
}

char* createPlayground(int size)
{
  char* playground;
  playground = (char*) malloc(size*size);
  for(int i=0; i<size*size; i++)
    *(playground+i) = 'y';
  return playground;
}

void showPlayground(char* playground, int size)
{
  int i, j;
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++)
      printf("%c", *(playground+size*i+j));
    printf("\n");
  }
}

const char getRandomInt()
{
  srand(time(NULL));
  int random = rand() % 7;
  return random;
}

int main(void)
{
  /*print(*shapes[0]);*/
  int i, size;
  /*printShape(*shapes[getRandomInt()]);
  printf("Enter game size: ");
  scanf("%d", &size);
  char* playground = createPlayground(size);
  showPlayground(playground, size);
  system("pause");*/
  char* playground = createPlayground(5);
  showPlayground(playground, 5);
  printf("\n");
  /*placeShape(0, 0, *shapes[1], playground, 5);*/
  printf("\n");
  placeShape(0, 0, *shapes[1], playground, 5);
  placeShape(2, 1, *shapes[1], playground, 5);
  showPlayground(playground, 5);
}