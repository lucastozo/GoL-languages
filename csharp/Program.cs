Random Random = new Random();
const int BOARD_SIZE = 20;
const int FPS = 15, TICKS = 1000/FPS;

Board board = new Board(BOARD_SIZE);

for (int i=0; i<board.Size; i++)
    for (int j=0; j<board.Size; j++)
        board.Grid[i,j] = Random.Next(2) == 0;

Console.Clear();
while (board.ComputeNextGeneration())
{
    board.Print();
    Console.SetCursorPosition(0,0);
    Thread.Sleep(TICKS);
}

class Board
{
    public int Size { get; set; }
    public bool[,] Grid { get; set; }

    public Board(int size)
    {
        Size = size;
        Grid = new bool[size, size];
    }

    public void Print()
    {
        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                Console.Write(Grid[i, j] ? "█" : "░");
            }
            Console.Write('\n');
        }
    }

    public bool ComputeNextGeneration()
    {
        bool[,] newGrid = new bool[Size, Size];
        bool hasChanged = false;

        for (int i = 0; i < Size; i++)
        {
            for (int j = 0; j < Size; j++)
            {
                int aliveNeighbours = CountAliveNeighbours(i, j);
                newGrid[i, j] = Grid[i, j] ? aliveNeighbours == 2 || aliveNeighbours == 3 : aliveNeighbours == 3;

                if (newGrid[i, j] != Grid[i, j])
                {
                    hasChanged = true;
                }
            }
        }

        Grid = newGrid;
        return hasChanged;
    }

    private int CountAliveNeighbours(int i, int j)
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
                if (neighbourI >= 0 && neighbourI < Size && neighbourJ >= 0 && neighbourJ < Size)
                {
                    count += Grid[neighbourI, neighbourJ] ? 1 : 0;
                }
            }
        }
        return count;
    }
}