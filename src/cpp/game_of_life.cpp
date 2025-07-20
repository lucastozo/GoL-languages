#include <iostream>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <array>

#define BOARD_SIZE 20
#define FPS 15
#define TICKS (1000 / FPS)

class Board {
public:
    std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> grid;

    void print()
    {
        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                if (grid[i][j]) std::cout << "█";
                else std::cout << "░";
            }
            std::cout << std::endl;
        }
    }

    bool computeNextGeneration()
    {
        std::array<std::array<bool, BOARD_SIZE>, BOARD_SIZE> newGrid;
        bool hasChanged = false;

        for (int i = 0; i < BOARD_SIZE; i++)
        {
            for (int j = 0; j < BOARD_SIZE; j++)
            {
                int aliveNeighbours = countAliveNeighbours(this, i,j);
                if (grid[i][j])
                {
                    newGrid[i][j] = aliveNeighbours == 2 || aliveNeighbours == 3;
                }
                else
                {
                    newGrid[i][j] = aliveNeighbours == 3;
                }
                
                if (newGrid[i][j] != grid[i][j])
                {
                    hasChanged = true;
                }
            }
        }

        grid = newGrid;
        return hasChanged;
    }

private:
    int countAliveNeighbours(Board *board, int i, int j)
    {
        int count = 0;
        for (int x = -1; x <= 1; x++)
        {
            for (int y = -1; y <= 1; y++)
            {
                if (x==0 && y==0) continue;
                int neighbourI = i + x;
                int neighbourJ = j + y;

                if (neighbourI >= 0 && neighbourI < BOARD_SIZE && neighbourJ >= 0 && neighbourJ < BOARD_SIZE)
                {
                    count += board->grid[neighbourI][neighbourJ];
                }
            }
        }
        return count;
    }
};

int main()
{
    srand(time(0));

    Board board;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            board.grid[i][j] = rand() % 2;
    
    while (board.computeNextGeneration())
    {
        std::cout << "\033[H\033[J";
        board.print();
        std::this_thread::sleep_for(std::chrono::milliseconds(TICKS));
    }
    return 0;
}