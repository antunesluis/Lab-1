#include <stdio.H>
#include <stdlib.h>
#include <time.h>

int tabela(int d1, int d2){
    int pontos;

    if (d1 != d2){
        if (d1 == d2 - 1 || d1 == d2 + 1){
            pontos = 20;
        }
        else {
            pontos = d1 + d2;
        }
    }
    if (d1 == d2){
        if (d1 == 6){
            pontos = 50;
        }
        else {
            pontos = 30;
        }
    }

    return pontos;
}

int tabela3opcoes(int d1, int d2, int d3){
     int pontos;

     if (d1 != d2 && d3 != d2 && d3 != d2 ){
        if (d1 == d2 - 1 || d1 == d2 + 1 || d1 == d3 + 1 || d1 == d3 - 1 || d2 == d3 - 1 || d2 == d3 + 1 ){
            pontos = 20;
        }
        else {
            pontos = d1 + d2 + d3;
        }
    }
    if (d1 == d2 || d3 == d1 || d2 == d3) {
        if (d1 == 6 || d3 == 6){
            pontos = 50;
        }
        else {
            pontos = 30;
        }
    }

    return pontos;
}

int primeiraRodadaPlayer (){
    int dado1, dado2, dadoEspecial, dado3, dado4, opcaoSegundaJogada, pontuacaoPlayer;
    srand(time(NULL));

    dado1 = (rand() % 6) + 1;
    printf("\no valor do primeiro dado eh = %d\n", dado1);

    dado2 = (rand() % 6) + 1;
    printf("\nO valor do segundo dado eh = %d\n\n", dado2);

    printf("\nNa segunda jogada existem tres opcoes: \n1 = Marcar uma posicao na tabela ja no primeiro lancamento;\n2 = separar um dos dados e jogar o outro - em busca da combinacao desejada;\n3 = jogar novamente os 2 dados.\n\nDIGITE A OPCAO DESEJADA: \n");
    scanf("%d", &opcaoSegundaJogada);

    switch (opcaoSegundaJogada)
    {
        case 1:
            pontuacaoPlayer = tabela(dado1, dado2);
            break;

        case 2:
            dadoEspecial = (rand() % 6) + 1;
            printf("\n\nO valor do terceiro dado e de = %d", dadoEspecial);
            pontuacaoPlayer = tabela3opcoes(dado1, dado2, dadoEspecial);
            break;

        case 3:
            dado3 = (rand() % 6) + 1;
            printf("\n\nO valor do quarto dado é de = %d", dado3);
            dado4 = (rand() % 6) + 1;
            printf("\n\nO valor do quarto dado é de = %d", dado4);
            pontuacaoPlayer = tabela(dado3, dado4);

    }

    return pontuacaoPlayer;
}

int primeiraRodadaComp(){
    int dado1, dado2, dadoEspecial, dado3, dado4, opcaoSegundaJogada, pontuacaoComp;
    srand(time(NULL));

    dado1 = (rand() % 6) + 1;
    printf("\no valor do primeiro dado do computador eh = %d\n", dado1);

    dado2 = (rand() % 6) + 1;
    printf("\nO valor do segundo dado do computador eh = %d\n\n", dado2);

    opcaoSegundaJogada = (rand() % 2) + 1;

    switch (opcaoSegundaJogada)
    {
        case 1:
            pontuacaoComp = tabela(dado1, dado2);
            break;

        case 2:
            dadoEspecial = (rand() % 6) + 1;
            printf("\n\nO valor do terceiro dado e de = %d", dadoEspecial);
            pontuacaoComp = tabela3opcoes(dado1, dado2, dadoEspecial);
            break;

        case 3:
            dado3 = (rand() % 6) + 1;
            printf("\n\nO valor do quarto dado é de = %d", dado3);
            dado4 = (rand() % 6) + 1;
            printf("\n\nO valor do quarto dado é de = %d", dado4);
            pontuacaoComp = tabela(dado3, dado4);

    }

    return pontuacaoComp;
}

int main (){
    int rodada1player, rodada1comp;

    printf("Bem vindo ao jogo Maior Soma de 3, onde apos 3 partidas de 4 rodadas (cada uma com 4 jogadas por participante) o vencedor sera decidido!!!! \n\n");
    printf("Cada rodada possui duas jogadas por participante, sendo a primeira o lancamento obrigatorio de dois dados e a segunda decidida pelo participante \n\n");
    printf("Apos cada jogada os pontos serao calculados e exibidos com base na tabela a seguir:\na = FREE: 2 dados diferentes sem formar sequencia - marcar a soma dos dados;\nb = RANK: 2 dados diferentes em sequencia - 20 pontos;\nc = DOUBLE: 2 dados iguais, porém diferentes de 6 - 30 pontos;\nd = MAX: 2 dados iguais a 6 - 50 pontos\n\n ");
    printf("-----------------------------------------------------------------------------------------------------------------------");

    rodada1player = primeiraRodadaPlayer();
    printf("\nSeus pontos no final da primeira jogado foram de = %d", rodada1player);
    printf("-----------------------------------------------------------------------------------------------------------------------");printf("-----------------------------------------------------------------------------------------------------------------------");


    rodada1comp = primeiraRodadaComp();
    printf("\nOs pontos no final da rodada da maquina foram de = %d", rodada1comp);

    return 0;
}
