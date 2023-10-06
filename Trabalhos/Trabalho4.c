#include <stdio.h>
#define max 100
#define min 0

int contarRepeticoes(int nNotas, float *vetNotas) {
    int i, repeticoes = 0, maxRepeticoes = 0;
    float valorMaisRepetido = 0;

    for (i = 0; i < nNotas - 1; i++) {
        repeticoes = 1;

        for (int j = i + 1; j < nNotas; j++) {
            if (vetNotas[i] == vetNotas[j]) {
                repeticoes++;
            } else {
                break;
            }
        }

        if (repeticoes > 1){
            printf("\nA nota %.2f possui %d ocorrencias", vetNotas[i], repeticoes);
        }

        if (repeticoes > maxRepeticoes || (repeticoes == maxRepeticoes && vetNotas[i] > valorMaisRepetido)) {
            maxRepeticoes = repeticoes;
            valorMaisRepetido = vetNotas[i];
        }

        i += repeticoes - 1;
    }

    printf("\n\nA nota %.2f possui no total %d repeticoes sendo a nota com maior ocorrencia", valorMaisRepetido, maxRepeticoes);

}

int notas(int nNotas, float *vetNotas) {
    printf("\n\nDigite o valor das notas no formato xxx.xx:\n");
    for (int i = 0; i < nNotas; i++) {
        scanf("%f", &vetNotas[i]);
    }

    for (int i = 0; i < nNotas; i++) {
        for (int j = i + 1; j < nNotas; j++) {
            if (vetNotas[i] > vetNotas[j]) {
                float temp = vetNotas[i];
                vetNotas[i] = vetNotas[j];
                vetNotas[j] = temp;
            }
        }
    }

    contarRepeticoes(nNotas, vetNotas);

    return 0;
}

int numeroNotas() {
    int nNotas;

    printf("Digite o numero de notas, sendo 100 o maximo e 0 o minimo, que voce deseja incluir no calculo:\n");
    scanf("%d", &nNotas);

    if (nNotas > min && nNotas <= max) {
        return nNotas;
    }

    else {
        printf("\n\nVALOR INVALIDO, TENTE NOVAMENTE\n");
        return -1;
    }
}

int main() {
    int nNotas;
    float vetNotas[max];

    nNotas = numeroNotas();

    if (nNotas == -1) {
        return 0;
    }

    notas(nNotas, vetNotas);

    return 0;
}