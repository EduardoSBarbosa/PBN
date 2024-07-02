#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

// Definições e constantes
#define SIZE 3
#define EMPTY '*'
#define PLAYER_X 'x'
#define PLAYER_O 'o'

// Declarações de Funções
static void singlemode();
static void doublemode();
static void place(int player, int position);  // usada para colocar X ou O
int checkwin();  // verifica se há um vencedor
void display_board();  // exibe o tabuleiro
int minimax(int depth, int isMaximizing);  // Algoritmo Minimax
int findBestMove();  // Encontra o melhor movimento para o computador

// Tabuleiro do jogo da velha representado por um array 2D
static char game_table[SIZE][SIZE];

int main() 
{
    srand((unsigned int)time(NULL));  // Inicializa o gerador de números aleatórios
    int play_again = 0;  // Variável para controlar se o jogador quer jogar novamente

    do 
    {
        int mode = 0;

        // Preenchendo o tabuleiro com asteriscos
        for (int i = 0; i < SIZE; i++)
            for (int j = 0; j < SIZE; j++)
                game_table[i][j] = EMPTY;

        // Exibindo o menu principal
        printf("***************************************\n");
        printf("*************TIC TAC TOE***************\n");
        printf("***************************************\n");
        printf("***********1.YOU vs COMPUTER***********\n");
        printf("***********2.YOU vs PLAYER*************\n");
        printf("***********3.EXIT**********************\n");
        printf("***************************************\n");
        printf("Enter your choice: ");
        scanf("%d", &mode);

        // Escolha do modo de jogo
        switch (mode) 
        {
            case 1:
                singlemode();
                break;
            case 2:
                doublemode();
                break;
            default:
                printf("THANK YOU and EXIT!\n");
        }

        // Pergunta ao jogador se ele quer jogar novamente
        printf("Next game? Enter 1 – YES and 0 - NO: ");
        scanf("%d", &play_again);

    } while (play_again == 1);

    return 0;
}

// Função para exibir o tabuleiro do jogo
void display_board() 
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) 
        {
            printf("%c ", game_table[i][j]);
        }
        printf("\n");
    }
}

// Função para o modo de jogo contra o computador
void singlemode() 
{
    int position;  // Posição onde o jogador deseja colocar 'x'
    int moves = 0;  // Contador de movimentos

    display_board();  // Exibe o tabuleiro inicial

    // Loop até o jogo terminar (vitória, derrota ou empate)
    while (moves < SIZE * SIZE) {
        printf("Where would you like to place 'x' (1-9): ");
        scanf("%d", &position);

        place(PLAYER_X, position);  // Coloca 'x' no tabuleiro

        // Se houver menos de 4 movimentos, o computador faz um movimento
        if (moves < 4) {
            int bestMove = findBestMove();
            place(PLAYER_O, bestMove);
        }

        display_board();  // Exibe o tabuleiro atualizado
        moves++;  // Incrementa o contador de movimentos

        int result = checkwin();  // Verifica se há um vencedor
        if (result != 0) {
            if (result == PLAYER_X) {
                printf("YOU WIN\n");
            } else {
                printf("YOU LOSE\n");
            }
            break;
        }

        // Se todos os movimentos foram feitos, o jogo termina em empate
        if (moves == SIZE * SIZE) {
            printf("\nDRAW\n");
        }
    }
}

// Função para o modo de jogo contra outro jogador
void doublemode() 
{
    int position_x, position_o;  // Posições onde os jogadores desejam colocar 'x' e 'o'
    int moves = 0;  // Contador de movimentos

    display_board();  // Exibe o tabuleiro inicial

    // Loop até o jogo terminar (vitória, derrota ou empate)
    while (moves < SIZE * SIZE) {
        printf("PLAYER1 - where would you like to place 'x' (1-9): ");
        scanf("%d", &position_x);

        place(PLAYER_X, position_x);  // Coloca 'x' no tabuleiro

        // Se houver menos de 4 movimentos, o segundo jogador faz um movimento
        if (moves < 4) {
            printf("PLAYER2 - where would you like to place 'o' (1-9): ");
            scanf("%d", &position_o);

            place(PLAYER_O, position_o);  // Coloca 'o' no tabuleiro
        }

        display_board();  // Exibe o tabuleiro atualizado
        moves++;  // Incrementa o contador de movimentos

        int result = checkwin();  // Verifica se há um vencedor
        if (result != 0) {
            if (result == PLAYER_X) {
                printf("PLAYER 1 WIN\n");
            } else {
                printf("PLAYER 2 WIN\n");
            }
            break;
        }

        // Se todos os movimentos foram feitos, o jogo termina em empate
        if (moves == SIZE * SIZE) {
            printf("\nDRAW\n");
        }
    }
}

// Função para colocar 'X' ou 'O' no tabuleiro
void place(int player, int position) {
    int row = (position - 1) / SIZE;
    int col = (position - 1) % SIZE;

    // Verifica se a posição é válida
    if (position < 1 || position > 9 || game_table[row][col] != EMPTY) {
        printf("Invalid move. Try again.\n");
        return;
    }

    // Coloca o jogador ('X' ou 'O') na posição indicada
    game_table[row][col] = player;
}

// Função para verificar se há um vencedor
int checkwin() {
    // Verificar linhas
    for (int i = 0; i < SIZE; i++) {
        if (game_table[i][0] == game_table[i][1] && game_table[i][1] == game_table[i][2]) {
            if (game_table[i][0] != EMPTY) {
                return game_table[i][0];
            }
        }
    }

    // Verificar colunas
    for (int i = 0; i < SIZE; i++) {
        if (game_table[0][i] == game_table[1][i] && game_table[1][i] == game_table[2][i]) {
            if (game_table[0][i] != EMPTY) {
                return game_table[0][i];
            }
        }
    }

    // Verificar diagonais
    if (game_table[0][0] == game_table[1][1] && game_table[1][1] == game_table[2][2]) {
        if (game_table[0][0] != EMPTY) {
            return game_table[0][0];
        }
    }
    if (game_table[0][2] == game_table[1][1] && game_table[1][1] == game_table[2][0]) {
        if (game_table[0][2] != EMPTY) {
            return game_table[0][2];
        }
    }

    return 0;  // Retorna 0 se não há vencedor
}

// Função Minimax para a IA do computador
int minimax(int depth, int isMaximizing) {
    int score = checkwin();

    // Verifica se há um vencedor
    if (score == PLAYER_O) {
        return 10 - depth;  // Computador ganha
    }
    if (score == PLAYER_X) {
        return depth - 10;  // Jogador ganha
    }
    if (depth == SIZE * SIZE) {
        return 0;  // Empate
    }

    if (isMaximizing) {
        int bestScore = -1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (game_table[i][j] == EMPTY) {
                    game_table[i][j] = PLAYER_O;
                    int score = minimax(depth + 1, 0);
                    game_table[i][j] = EMPTY;
                    bestScore = score > bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = 1000;
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                if (game_table[i][j] == EMPTY) {
                    game_table[i][j] = PLAYER_X;
                    int score = minimax(depth + 1, 1);
                    game_table[i][j] = EMPTY;
                    bestScore = score < bestScore ? score : bestScore;
                }
            }
        }
        return bestScore;
    }
}

// Função para encontrar o melhor movimento para o computador
int findBestMove() {
    int bestMove = -1;
    int bestScore = -1000;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (game_table[i][j] == EMPTY) {
                game_table[i][j] = PLAYER_O;
                int score = minimax(0, 0);
                game_table[i][j] = EMPTY;
                if (score > bestScore) {
                    bestScore = score;
                    bestMove = i * SIZE + j + 1;
                }
            }
        }
    }

    return bestMove;
}
