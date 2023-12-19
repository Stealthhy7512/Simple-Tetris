#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char shapes[7][3][3] = {{{'x', 'x', 'x'}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', 'x', ' '}, {'x', 'x', ' '}, {' ', ' ', ' '}}, 
        {{'x', ' ', ' '}, {'x', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}, 
        {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', 'x', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', ' ', ' '}}, 
        {{' ', 'x', 'x'}, {'x', 'x', ' '}, {' ', ' ', ' '}}};

const char getRandomInt()
{
  srand(time(NULL));
  int random = rand() % 7;
  return random;
}

char* createPlayground(int size)
{
  char* playground;
  int i;
  playground = (char*) malloc(size*size);
  for(i=0; i<size*size; i++)
    *(playground+i) = ' ';
  return playground;
}

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
  char *transposed, *rotated;
  transposed = (char*) malloc(9);
  rotated = (char*) malloc(9);
   for(i = 0; i < 3; i++) {
        for(j = 0; j < 3; j++) {
            *(transposed + 3*i + j) = *(shape + 3*j + i);
        }
    }
    for(i = 0; i < 3; i++) {
      for(j = 0; j < 3; j++)
        *(rotated + 3*i + j) = *(transposed + 3*i + 2 - j); 
    }
  return rotated;
}

int checkLegal(int coX, int coY, char* shape, char* playground, int size)
{
  int i, j;
    for(i = coY; i < coY+3; i++) {
      for(j = coX; j < coX+3; j++) {
        if(*(playground + size*i + j) != ' ' && *(shape + 3*(i - coY) + (j - coX)) != ' ') {
          fprintf(stderr, "Illegal placement, try again.\n");
          return 0;
        }
      }
    }
  return 1;
}

void placeShape(int coX, int coY, char* shape, char* playground, int size)
{
  if(checkLegal(coX, coY, shape, playground, size)){
    int i, j;
    for(i = coY; i < coY+3; i++) {
      for(j = coX; j < coX+3; j++) {
        if(*(shape + 3*(i - coY) + (j - coX)) != ' ')
          *(playground + size*i + j) = *(shape + 3*(i - coY) + (j - coX));
      }
    }
  }
}

void showPlayground(char* playground, int size)
{
  int i, j;
  printf("Current playground:\n");
  for(i=0; i<size; i++)
    printf("_");
  printf("\n");
  for(i=0; i<size; i++) {
    for(j=0; j<size; j++)
      printf("%c", *(playground+size*i+j));
    printf("\n");
  }
  for(i=0; i<size; i++)
    printf("_");
  printf("\n");
}

const int showRandomShape()
{
  printf("Shape to place:\n");
  int random = getRandomInt();
  printShape(*shapes[random]);
  return random;
}

int main(int argc, int argv[])
{
  int i, size, coX, coY;

  /*printf("Enter game size: ");
  scanf("%d", &size);
  char* playground = createPlayground(size);
  do {
    const int currentShape = showRandomShape();
    showPlayground(playground, size);
    printf("Enter coordinates to place: ");
    scanf("%d %d", &coX, &coY);
    placeShape(coX, coY, *shapes[currentShape], playground, size);
  } while(1);*/
    
  /*showRandomShape();
  showPlayground(playground, size);
  char* playground = createPlayground(5);
  showPlayground(playground, 5);
  printf("\n");
  placeShape(0, 0, *shapes[1], playground, 5);
  placeShape(0, 0, *shapes[1], playground, 5);
  showPlayground(playground, 5);
  printf("\n");
  placeShape(0, 0, *shapes[0], playground, 5);
  showPlayground(playground, 5);*/
  system("pause");
  printShape(*shapes[6]);
  
}