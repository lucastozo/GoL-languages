import random
import time
import os
import sys

class Board:
    Size: int
    Grid: list

    def __init__(self, size):
        self.Size = size
        self.Grid = [[False for _ in range(size)] for _ in range(size)]
    
    def Print(self):
        for i in range(self.Size):
            for j in range(self.Size):
                if self.Grid[i][j]:
                    sys.stdout.write('█')
                else:
                    sys.stdout.write('░')
            print()

    def ComputeNextGeneration(self) -> bool:
        new_grid = [[False for _ in range(self.Size)] for _ in range(self.Size)]
        hasChanged = False

        for i in range(self.Size):
            for j in range(self.Size):
                aliveNeighbours = self.CountAliveNeighbours(i, j)
                if self.Grid[i][j]:
                    new_grid[i][j] = aliveNeighbours == 2 or aliveNeighbours == 3
                else:
                    new_grid[i][j] = aliveNeighbours == 3

                if new_grid[i][j] != self.Grid[i][j]:
                    hasChanged = True

        self.Grid = new_grid
        return hasChanged

    def CountAliveNeighbours(self, i, j) -> int:
        count = 0
        for x in range(-1, 2):
            for y in range(-1, 2):
                if x == 0 and y == 0:
                    continue
                neighbourI = i + x
                neighbourJ = j + y
                if neighbourI >= 0 and neighbourI < self.Size and neighbourJ >= 0 and neighbourJ < self.Size:
                    if self.Grid[neighbourI][neighbourJ]:
                        count += 1
        return count

BOARD_SIZE = 20
FPS = 15
TICKS = 1000/FPS / 1000 # Python sleep() uses seconds

board = Board(BOARD_SIZE)

for i in range(BOARD_SIZE):
    for j in range(BOARD_SIZE):
        board.Grid[i][j] = random.randint(0, 1) < 0.5

os.system('cls') if os.name == 'nt' else os.system('clear')
while(board.ComputeNextGeneration()):
    print('\033[0;0H')
    board.Print()
    time.sleep(TICKS)