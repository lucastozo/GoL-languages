class Board 
{
    constructor(size)
    {
        this.Size = size
        this.Grid = new Array(size).fill(null).map(() => new Array(size).fill(false))
    }

    Print()
    {
        for (let i = 0; i < this.Size; i++)
        {
            for (let j = 0; j < this.Size; j++)
            {
                process.stdout.write(this.Grid[i][j] ? '█' : '░')
            }
            process.stdout.write('\n')
        }
    }

    ComputeNextGeneration()
    {
        const newGrid = new Array(this.Size).fill(null).map(() => new Array(this.Size).fill(false))
        let hasChanged = false

        for (let i = 0; i < this.Size; i++)
        {
            for (let j = 0; j < this.Size; j++)
            {
                const aliveNeighbours = this.CountAliveNeighbours(i, j)
                newGrid[i][j] = this.Grid[i][j] ? (aliveNeighbours === 2 || aliveNeighbours === 3) : aliveNeighbours === 3

                if (newGrid[i][j] !== this.Grid[i][j])
                    hasChanged = true
            }
        }

        this.Grid = newGrid
        return hasChanged
    }

    CountAliveNeighbours(i, j)
    {
        let count = 0
        for (let x = -1; x <= 1; x++)
        {
            for (let y = -1; y <= 1; y++)
            {
                if (x === 0 && y === 0)
                    continue

                const neighbourI = i + x
                const neighbourJ = j + y
                if (neighbourI >= 0 && neighbourI < this.Size && neighbourJ >= 0 && neighbourJ < this.Size)
                    count += this.Grid[neighbourI][neighbourJ] ? 1 : 0
            }
        }
        return count
    }

}

const BOARD_SIZE = 20
const FPS = 15, TICKS = 1000 / FPS

const board = new Board(BOARD_SIZE)

for (let i = 0; i < BOARD_SIZE; i++)
    for (let j = 0; j < BOARD_SIZE; j++)
        board.Grid[i][j] = Math.random() < 0.5

console.clear();
main()
async function main()
{
    while (board.ComputeNextGeneration())
    {
        board.Print()
        process.stdout.cursorTo(0, 0)
        await new Promise(resolve => setTimeout(resolve, TICKS))
    }
}