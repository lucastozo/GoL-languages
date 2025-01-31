algoritmo "Game of Life"
var
BOARD_SIZE: inteiro
i, j: inteiro
board: vetor[0..20, 0..20] de logico

procedimento PrintBoard()
var
    i, j: inteiro
inicio
    para i de 0 ate BOARD_SIZE - 1 faca
        para j de 0 ate BOARD_SIZE - 1 faca
            se board[i, j] entao
                escreva("O")
            senao
                escreva(".")
            fimse
        fimpara
        escreval()
    fimpara
fimprocedimento

funcao ComputeNextGeneration(): logico
var
    newBoard: vetor[0..20, 0..20] de logico
    i, j: inteiro
    aliveNeighbours: inteiro
    hasChanged: logico
inicio
    para i de 0 ate BOARD_SIZE-1 faca
        para j de 0 ate BOARD_SIZE-1 faca
            aliveNeighbours <- CountAliveNeighbours(i, j)
            se (board[i, j]) entao
                newBoard[i, j] <- (aliveNeighbours = 2) ou (aliveNeighbours = 3)
            senao
                newBoard[i, j] <- (aliveNeighbours = 3)
            fimse

            se (newBoard[i, j] <> board[i, j]) entao
                hasChanged <- verdadeiro
            fimse
        fimpara
    fimpara

    para i de 0 ate BOARD_SIZE-1 faca
        para j de 0 ate BOARD_SIZE-1 faca
            board[i, j] <- newBoard[i, j]
        fimpara
    fimpara

    retorne hasChanged
fimfuncao

funcao CountAliveNeighbours(i, j: inteiro): inteiro
var
    count: inteiro
    x, y: inteiro
    neighbourI, neighbourJ: inteiro
inicio
    count <- 0
    para x de -1 ate 1 faca
        para y de -1 ate 1 faca
            se (x <> 0) ou (y <> 0) entao
                neighbourI <- i + x
                neighbourJ <- j + y
                se (neighbourI >= 0) e (neighbourI < BOARD_SIZE) e (neighbourJ >= 0) e (neighbourJ < BOARD_SIZE) entao
                    se (board[neighbourI, neighbourJ]) entao
                        count <- count + 1
                    fimse
                fimse
            fimse
        fimpara
    fimpara
    retorne count
fimfuncao

inicio
    BOARD_SIZE <- 20

    para i de 0 ate BOARD_SIZE-1 faca
        para j de 0 ate BOARD_SIZE-1 faca
            board[i, j] <- 0.5 > Rand()
        fimpara
    fimpara

    enquanto ComputeNextGeneration() faca
        PrintBoard()
        limpatela
    fimenquanto
fimalgoritmo