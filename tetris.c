/*
TODO:
-Fix placing                                Done
-Recursive checkLegal function              Done
-Implement rotation
-Get user input to rotate/continue/quit
-Implement score                            Done
-Implement line deletion upon filling       Done
-Implement failure                          Done
-De-clutter screen after each action        Done
-Show position about to be placed           Done
-Check input validity
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

char shapes[][3][3] = {{{'x', 'x', 'x'}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', 'x', ' '}, {'x', 'x', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', 'x', ' '}}, {{'x', ' ', ' '}, {'x', ' ', ' '}, {'x', ' ', ' '}}, {{' ', 'x', 'x'}, {'x', 'x', ' '}, {' ', ' ', ' '}}};

char *playground;
int size;
int score = 0;

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
    printf("\nCurrent playground:\n");
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
    for (i = 0; i < size; i++)
        printf("%d", i + 1);

    printf("\n\n");
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

void moveLines(int coY)
{
    int i, j;
    for (i = coY - 1; i >= 0; i--)
        for (j = 0; j < size; j++)
            *(playground + size * (i + 1) + j) = *(playground + size * i + j);
}

void deleteLine()
{
    int *fullFlag = (int *)calloc(size, sizeof(int));
    int i, j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
            if (*(playground + size * i + j) == ' ')
                fullFlag[i] = 1;
    }
    for (i = 0; i < size; i++)
        for (j = 0; j < size; j++)
            if (fullFlag[i] == 0)
                *(playground + size * i + j) = ' ';
    i = 1;
    while (i < size)
    {
        if (fullFlag[i] == 0)
        {
            moveLines(i);
            score += 5;
        }
        i++;
    }
}

int main(int argc, char *argv[])
{
    int i, coX, coY;
    srand(time(NULL));

    printf("Enter game size: ");
    scanf("%d", &size);
    system("cls");

    char *playground = createPlayground();
    while (1)
    {
        int currentShape = showRandomShape();
        showPlayground();
        playground = replacePlayground();
        printf("Score: %d\n", score);
        do
        {
            printf("Input 0 to rotate shape and -1 to quit the game.\n");
            printf("Enter coordinate to place: ");
            scanf("%d", &coX);
            if(coX == -1)
                return 0;
            /*else if(coX == 0)
                rotateShape(currentShape);*/
            else if (coX > size)
                fputs("Impossible, try again.\n", stderr);
        } while (coX > size);

        int result = placeShape(coX - 1, *shapes[currentShape]);
        deleteLine();
        if (result == 0)
        {
            printf("You lost the game!\n");
            break;
        }
        score++;
        system("cls");
    }

    system("pause");
    return 0;
}