#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_MAX 7
#define CAMADAS_MAX 3

void sAntiHorario_1camada(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;
    char temp;

    int linhaInicial = 0, linhaFinal = TAMANHO_MAX - 1;
    int colunaInicial = 0, colunaFinal = TAMANHO_MAX - 1;

    // cima para a esquerda
    temp = matriz[linhaInicial][colunaInicial];
    for (j = colunaInicial; j < colunaFinal; j++) {
        matriz[linhaInicial][j] = matriz[linhaInicial][j + 1];
    }

    // direita para cima
    for (i = linhaInicial; i < linhaFinal; i++) {
        matriz[i][colunaFinal] = matriz[i + 1][colunaFinal];
    }

    // baixo para a direita
    for (j = colunaFinal; j > colunaInicial; j--) {
        matriz[linhaFinal][j] = matriz[linhaFinal][j - 1];
    }

    // esquerda para baixo
    for (i = linhaFinal; i > linhaInicial + 1; i--) {
        matriz[i][colunaInicial] = matriz[i - 1][colunaInicial];
    }

    matriz[linhaInicial + 1][colunaInicial] = temp;
}


void sHoraio_2camada(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;
    char temp;

    int linhaInicial = 1, linhaFinal = TAMANHO_MAX - 2;
    int colunaInicial = 1, colunaFinal = TAMANHO_MAX - 2;

    // esquerda para cima
    temp = matriz[linhaInicial][colunaInicial];
    for (i = linhaInicial; i < linhaFinal; i++) {
        matriz[i][colunaInicial] = matriz[i + 1][colunaInicial];
    }

    // baixo para a esquerda
    for (j = colunaInicial; j < colunaFinal; j++) {
        matriz[linhaFinal][j] = matriz[linhaFinal][j + 1];
    }

    // direita para baixo
    for (i = linhaFinal; i > linhaInicial; i--) {
        matriz[i][colunaFinal] = matriz[i - 1][colunaFinal];
    }

    // cima para a direita
    for (j = colunaFinal; j > colunaInicial + 1; j--) {
        matriz[linhaInicial][j] = matriz[linhaInicial][j - 1];
    }

    matriz[linhaInicial][colunaInicial + 1] = temp;
}


void sAntiHorario_3camada(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;
    char temp;

    int linhaInicial = 2, linhaFinal = TAMANHO_MAX - 3;
    int colunaInicial = 2, colunaFinal = TAMANHO_MAX - 3;

    // cima para a esquerda
    temp = matriz[linhaInicial][colunaInicial];
    for (j = colunaInicial; j < colunaFinal; j++) {
        matriz[linhaInicial][j] = matriz[linhaInicial][j + 1];
    }

    // direita para cima
    for (i = linhaInicial; i < linhaFinal; i++) {
        matriz[i][colunaFinal] = matriz[i + 1][colunaFinal];
    }

    // baixo para a direita
    for (j = colunaFinal; j > colunaInicial; j--) {
        matriz[linhaFinal][j] = matriz[linhaFinal][j - 1];
    }

    // esquerda para baixo
    for (i = linhaFinal; i > linhaInicial + 1; i--) {
        matriz[i][colunaInicial] = matriz[i - 1][colunaInicial];
    }

    matriz[linhaInicial + 1][colunaInicial] = temp;
}


void imprimirMatriz(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    for (i = 0; i < TAMANHO_MAX; i++){
        for(j = 0; j < TAMANHO_MAX; j++){
            printf("%5c", matriz[i][j]);
        }
        printf("\n\n");
    }
}


void resetaMatriz(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    matriz[0][0] = 'O';    // 1 camada
    matriz[6][6] = 'O';    // 1 camada
    matriz[1][5] = 'O';    // 2 camada
    matriz[5][1] = 'O';    // 2 camada
    matriz[2][3] = 'O';    // 3 camada
    matriz[4][3] = 'O';    // 3 camada

    matriz[6][0] = 'X';    // 1 camada
    matriz[1][1] = 'X';    // 1 camada
    matriz[5][5] = 'X';    // 2 camada
    matriz[0][6] = 'X';    // 2 camada
    matriz[3][2] = 'X';    // 3 camada
    matriz[3][4] = 'X';    // 3 camada

    for (i = 0; i < TAMANHO_MAX; i++){
        for(j = 0; j < TAMANHO_MAX; j++){
            if (matriz[i][j] != 'O' && matriz[i][j] != 'X'){
                matriz[i][j] = '.';
            }
        }
    }
}


int qualCamada(char matriz[TAMANHO_MAX][TAMANHO_MAX]) {
    int camada = 0;

    do {
        printf("\n\nQual camada voce deseja mover? (digite '0' para parar o jogo)\n1 = camada mais externa no sentido anti-horario\n2 = camada do meiono sentido horario\n3 = camada interna circular ao eixo no sentido anti-horario:\n");
        scanf("%d", &camada);
    } while (camada > CAMADAS_MAX || camada < 0);

    switch (camada) {
        case 0:
            printf("\n\nADEUS :^( \n");
            return 0;
            break;

        case 1:
            sAntiHorario_1camada(matriz);
            break;

        case 2:
            sHoraio_2camada(matriz);
            break;

        case 3:
            sAntiHorario_3camada(matriz);
            break;
    }
    return 1;
}


int VerifMatrizX_A(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    char matrizXA[TAMANHO_MAX][TAMANHO_MAX] = {
        {'O', '.', '.', '.', '.', '.', 'X'},
        {'.', 'O', '.', '.', '.', 'X', '.'},
        {'.', '.', 'O', '.', 'X', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'X', '.', 'O', '.', '.'},
        {'.', 'X', '.', '.', '.', 'O', '.'},
        {'X', '.', '.', '.', '.', '.', 'O'}
        };

    for (i = 0; i < TAMANHO_MAX; i++) {
        for (j = 0; j < TAMANHO_MAX; j++) {
            if (matriz[i][j] != matrizXA[i][j]) {
                return 0;
            }
        }
    }
    printf("\n\nX DESENHADO NA TELA!!!!\n\n");
    limparTela(matriz);
    return 0;
}


int VerifMatrizX_B(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    char matrizXB[TAMANHO_MAX][TAMANHO_MAX] = {
        {'X', '.', '.', '.', '.', '.', 'O'},
        {'.', 'X', '.', '.', '.', 'O', '.'},
        {'.', '.', 'X', '.', 'O', '.', '.'},
        {'.', '.', '.', '.', '.', '.', '.'},
        {'.', '.', 'O', '.', 'X', '.', '.'},
        {'.', 'O', '.', '.', '.', 'X', '.'},
        {'O', '.', '.', '.', '.', '.', 'X'}
        };

    for (i = 0; i < TAMANHO_MAX; i++) {
        for (j = 0; j < TAMANHO_MAX; j++) {
            if (matriz[i][j] != matrizXB[i][j]) {
                return 0;
            }
        }
    }
    printf("\n\nX DESENHADO NA TELA!!!!\n\n");
    limparTela(matriz);
    return 0;
}


int VerifMatrizCruz_A(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    char matrizCruzA[TAMANHO_MAX][TAMANHO_MAX] = {
        {'.', '.', '.', 'O', '.', '.', '.'},
        {'.', '.', '.', 'O', '.', '.', '.'},
        {'.', '.', '.', 'O', '.', '.', '.'},
        {'X', 'X', 'X', '.', 'X', 'X', 'X'},
        {'.', '.', '.', 'O', '.', '.', '.'},
        {'.', '.', '.', 'O', '.', '.', '.'},
        {'.', '.', '.', 'O', '.', '.', '.'}
        };

    for (i = 0; i < TAMANHO_MAX; i++) {
        for (j = 0; j < TAMANHO_MAX; j++) {
            if (matriz[i][j] != matrizCruzA[i][j]) {
                return 0;
            }
        }
    }
    printf("\n\nCRUZ DESENHADA NA TELA!!!!\n\n");
    limparTela(matriz);
    return 0;
}


int VerifMatrizCruz_B(char matriz[TAMANHO_MAX][TAMANHO_MAX]){
    int i, j;

    char matrizCruzB[TAMANHO_MAX][TAMANHO_MAX] = {
        {'.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.'},
        {'O', 'O', 'O', '.', 'O', 'O', 'O'},
        {'.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.'},
        {'.', '.', '.', 'X', '.', '.', '.'}
        };

    for (i = 0; i < TAMANHO_MAX; i++) {
        for (j = 0; j < TAMANHO_MAX; j++) {
            if (matriz[i][j] != matrizCruzB[i][j]){
                return 0;
            }
        }
    }
    printf("\n\nCRUZ DESENHADA NA TELA!!!!\n\n");
    limparTela(matriz);
    return 0;
}


void limparTela(char matriz[TAMANHO_MAX]){
    system("pause");
    system("cls");
    imprimirMatriz(matriz);

}


int main(){
    int i, j;
    char matriz[TAMANHO_MAX][TAMANHO_MAX], resposta = 1;

    printf("\n\nBEM VINDO AO JOGO MOVA A MATRIZ :^) ");
    printf("\n\nSeu objetico eh conseguir formar uma cruz ou um 'X' utilizando linhas iguais de simbolos\n\n");

    resetaMatriz(matriz);
    imprimirMatriz(matriz);

    while (resposta != 0 ){
        resposta = qualCamada(matriz);
        if (resposta == 0){
            exit;
        }
        imprimirMatriz(matriz);

        VerifMatrizX_B(matriz);

        VerifMatrizX_A(matriz);

        VerifMatrizCruz_A(matriz);

        VerifMatrizCruz_B(matriz);
    }

    return 0;
}
