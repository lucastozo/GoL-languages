#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define BOARD_SIZE 20
#define FPS 15
#define TICKS 1000 / FPS

#ifdef _WIN32
#include <conio.h>
#else
#define clrscr() printf("\e[1;1H\e[2J")
#endif

typedef struct
{
    int size;
    int **cells;
} Board;

void PrintBoard(Board *board);
int ComputeNextGeneration(Board *board);
int CountAliveNeighbours(Board *board, int i, int j);

int main()
{
    Board board;
    board.size = BOARD_SIZE;
    board.cells = (int **)malloc(board.size * sizeof(int *));
    for (int i = 0; i < board.size; i++)
    {
        board.cells[i] = (int *)malloc(board.size * sizeof(int));
    }

    for (int i = 0; i < board.size; i++)
    {
        for (int j = 0; j < board.size; j++)
        {
            board.cells[i][j] = rand() % 2;
        }
    }
    
    clrscr();
    while (ComputeNextGeneration(&board) == 1)
    {
        printf("\033[H");
        PrintBoard(&board);
        usleep(TICKS * 1000);
    }

    return 0;
}

void PrintBoard(Board *board)
{
    for (int i = 0; i < board->size; i++)
    {
        for (int j = 0; j < board->size; j++)
        {
            if (board->cells[i][j] == 1)
            {
                printf("█");
            }
            else
            {
                printf("░");
            }
        }
        printf("\n");
    }
}

int ComputeNextGeneration(Board *board)
{
    Board newBoard;
    newBoard.size = board->size;
    newBoard.cells = (int **)malloc(newBoard.size * sizeof(int *));
    for (int i = 0; i < newBoard.size; i++)
    {
        newBoard.cells[i] = (int *)malloc(newBoard.size * sizeof(int));
    }

    int hasChanged = 0;

    for (int i = 0; i < board->size; i++)
    {
        for (int j = 0; j < board->size; j++)
        {
            int aliveNeighbours = CountAliveNeighbours(board, i, j);
            if (board->cells[i][j] == 1)
            {
                if (aliveNeighbours == 2 || aliveNeighbours == 3)
                {
                    newBoard.cells[i][j] = 1;
                }
                else
                {
                    newBoard.cells[i][j] = 0;
                }
            }
            else
            {
                if (aliveNeighbours == 3)
                {
                    newBoard.cells[i][j] = 1;
                }
                else
                {
                    newBoard.cells[i][j] = 0;
                }
            }

            if (newBoard.cells[i][j] != board->cells[i][j])
            {
                hasChanged = 1;
            }
        }
    }

    for (int i = 0; i < board->size; i++)
    {
        for (int j = 0; j < board->size; j++)
        {
            board->cells[i][j] = newBoard.cells[i][j];
        }
    }

    return hasChanged;
}

int CountAliveNeighbours(Board *board, int i, int j)
{
    int count = 0;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (x == 0 && y == 0)
            {
                continue;
            }

            int neighbourI = i + x;
            int neighbourJ = j + y;

            if (neighbourI >= 0 && neighbourI < board->size && neighbourJ >= 0 && neighbourJ < board->size)
            {
                count += board->cells[neighbourI][neighbourJ];
            }
        }
    }
    return count;
}