#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_RED     "\x1b[31m"

#define SIZE 10
#define NUM_NAVIOS 3
#define TAM_NAVIO 3
//inicia o campo de batalha recebendo um parametro com o SIZE = 10 para o array
void inicializarCampo(int campo[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            campo[i][j] = 0;  // Inicializa tudo com água (0)
        }
    }
}

//imprimi o campo de batalha na tela
void imprimirCampo(int campo[SIZE][SIZE]) {
    printf("\n  ");
    for (int i = 0; i < SIZE; i++) {
        printf(ANSI_COLOR_BLUE "%c " ANSI_COLOR_RESET, 'A' + i); // Índices das colunas em letras azuis
    }
    printf("\n");

    for (int i = 0; i < SIZE; i++) {
        printf(ANSI_COLOR_YELLOW "%d " ANSI_COLOR_RESET, i); // Índices das linhas em números amarelos
        for (int j = 0; j < SIZE; j++) {
            printf("%d ", campo[i][j]);
        }
        printf("\n");
    }
}

// Função para posicionar os navios de forma aleatória no campo de batalha
void posicionarNavios(int campo[SIZE][SIZE], int posicoes[NUM_NAVIOS][3][2]) {
    srand(time(NULL)); //inicializa o gerador de numeros aleatorios

    for (int n = 0; n < NUM_NAVIOS; n++) {
        int x, y, orientacao, valido;

        do {
            valido = 1;
            x = rand() % SIZE;
            y = rand() % SIZE;
            orientacao = rand() % 2; // 0 = horizontal, 1 = vertical

            //verifica se o navio cabe no campo de batalha
            if ((orientacao == 0 && y + TAM_NAVIO > SIZE) || (orientacao == 1 && x + TAM_NAVIO > SIZE)) {
                valido = 0;
                continue;
            }

            //verifica se ja tem um navio na posição
            for (int i = 0; i < TAM_NAVIO; i++) {
                if (orientacao == 0 && campo[x][y + i] != 0) {
                    valido = 0;
                    break;
                } else if (orientacao == 1 && campo[x + i][y] != 0) {
                    valido = 0;
                    break;
                }
            }
        } while (!valido); //repete ate achar uma posição valida

        //posicionando os navios no campo
        for (int i = 0; i < TAM_NAVIO; i++) {
            if (orientacao == 0) {
                campo[x][y + i] = 1;
                posicoes[n][i][0] = x;
                posicoes[n][i][1] = y + i;
            } else {
                campo[x + i][y] = 1;
                posicoes[n][i][0] = x + i;
                posicoes[n][i][1] = y;
            }
        }
    }
}

int main() {
    //inicia um array com o tamanho do campo de batalha usando a variavel SIZE = 10
    int campo_batalha[SIZE][SIZE];
    int posicoes[NUM_NAVIOS][3][2]; // Armagenazer a posição dos navios

    printf("Batalha Naval\n\n");
    printf("Seja bem-vindo ao jogo!\n");

    inicializarCampo(campo_batalha);  // Inicializa o campo de batalha
    posicionarNavios(campo_batalha, posicoes); // Posiciona os navios de forma aleatória
    imprimirCampo(campo_batalha); // Imprime o campo de batalha na tela

    // Exibe as posições dos navios
    printf("\n\nNavios:\n");
    for (int n = 0; n < NUM_NAVIOS; n++) {
        printf("%dº navio nas posições: ", n + 1);
        for (int i = 0; i < TAM_NAVIO; i++) {
            printf("(%c, %d) ", 'A' + posicoes[n][i][1], posicoes[n][i][0]);
        }
        printf("\n");
    }

    return 0;
}