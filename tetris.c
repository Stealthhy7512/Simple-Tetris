/*
TODO:
-Fix placing                                Done
-Recursive checkLegal function              Done
-Implement rotation
-Get user input to rotate/continue/quit
-Implement score                            Semi done
-Implement line deletion upon filling
-Implement failure                          Done
-De-clutter screen after each action        Done
-Show position about to be placed           Done
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char shapes[][3][3] = {{{'x', 'x', 'x'}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', 'x', ' '}, {'x', 'x', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', 'x', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', ' ', ' '}}, {{' ', 'x', 'x'}, {'x', 'x', ' '}, {' ', ' ', ' '}}};

char* playground;
int size;

const char getRandomInt()
{

    int random = rand() % 7;
    return random;
}

char *createPlayground()
{
    int i;
    playground = (char *)malloc(size * size + 2 * size);
    for (i = 0; i < size * size; i++)
        *(playground + i) = ' ';
    for (i = size * size; i < size * size + 2 * size; i++) /*extra memory to prevent segmentation fault*/
        *(playground + i) = '\0';
    return playground;
}

void printShape(char *shapes)
{
    int i, j;
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            printf("%c", *(shapes + 3 * i + j));
        }
        printf("\n");
    }
}

char *rotateShape(char *shape)
{
    int i, j;
    char *transposed, *rotated;
    transposed = (char *)malloc(9);
    rotated = (char *)malloc(9);
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            *(transposed + 3 * i + j) = *(shape + 3 * j + i);
        }
    }
    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
            *(rotated + 3 * i + j) = *(transposed + 3 * i + 2 - j);
    }
    return rotated;
}

int checkLegal(int coX, int coY, char *shape)
{
    if (coY < 0)
    {
        return -1;
    }
    int i, j;
    for (i = coY; i < coY + 3; i++)
    {
        for (j = coX; j < coX + 3; j++)
        {
            if (*(playground + size * i + j) != ' ' && *(shape + 3 * (i - coY) + (j - coX)) != ' ')
            {
                return checkLegal(coX, coY - 1, shape);
            }
        }
    }
    return coY;
}

int placeShape(int coX, char *shape)
{
    int coY = checkLegal(coX, size - 1, shape);
    if (coY == -1)
    {
        return 0;
    }
    else
    {
        /*printf("cort: %d\n", coY);*/
        int i, j;
        for (i = coY; i < coY + 3; i++)
        {
            for (j = coX; j < coX + 3; j++)
            {
                if (*(playground + size * i + j) == ' ' && *(shape + 3 * (i - coY) + (j - coX)) == 'x')
                    *(playground + size * i + j) = '*';
            }
        }
    }
    return 1;
}

void showPlayground()
{
    int i, j;
    printf("Current playground:\n");
    for (i = 0; i < size; i++)
        printf("-");
    printf("\n");
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            printf("%c", *(playground + size * i + j));
        printf("\n");
    }
    for (i = 0; i < size; i++)
        printf("-");
    printf("\n");
}

char *replacePlayground()
{
    int i, j;
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (*(playground + size * i + j) == '*')
                *(playground + size * i + j) = 'x';
    return playground;
}

const int showRandomShape()
{
    printf("Shape to place:\n");
    int random = getRandomInt();
    printShape(*shapes[random]);
    return random;
}



int main(int argc, char *argv[])
{
    int i, coX, coY;
    int score = 0;
    srand(time(NULL));
    printf("Enter game size: ");
    scanf("%d", &size);
    char *playground = createPlayground();
    while (1)
    {
        int currentShape = showRandomShape();
        showPlayground();
        playground = replacePlayground();
        printf("Score: %d\n", score);
        printf("Enter coordinate to place: ");
        scanf("%d", &coX);
        int result = placeShape(coX, *shapes[currentShape]);
        if (result == 0)
        {
            printf("You lost the game!\n");
            break;
        }
        score++;
        system("cls");
    }

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
    return 0;
}