#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int gPontosMax = 21;
int gJogadasMax = 3;

int rolarDados() {
    int branco, vermelho, pontosDados;

    branco = (rand() % 6) + 1;
    vermelho = (rand() % 6) + 1;

    if (vermelho == 6) {
        vermelho *= 2;
    }

    printf("\n\nVALOR DOS DADOS:\nBranco = %d\nVermelho = %d", branco, vermelho);

    pontosDados = vermelho + branco;

    return pontosDados;
}

int comecoJogo() {
    int opcaoJogo;

    printf("\nBem vindo ao jogo!!!!!\n\nINFORMACOES GERAIS:\n- Cada partida sera composta de 3 jogadas por player intercaladas\n- Quem chegar mais perto de 21 pontos será o grande vencedor!!!!\n- O player que passar de 21 pontos perde a partida e se os dois players passarem sera determinado empate");

    printf("\n\nDigite 1 para jogar Player vs PLayer e 0 para jogar Player vs Maquina: ");
    scanf("%d", &opcaoJogo);

    switch(opcaoJogo) {
        case 0:
            return opcaoJogo;
            break;
        case 1:
            return opcaoJogo;
            break;
        default:
            printf("\n\nOpcao inexistente, digite novamente:\n");
            return comecoJogo();
    }
}

int JogadaPlayer() {
    int jogaOuPassa, pontosDados;

    printf("\n\nDigite 1 para jogar os dados ou 0 para passar a vez: ");
    scanf("%d", &jogaOuPassa);

    switch (jogaOuPassa) {
        case 1:
            pontosDados = rolarDados();
            printf("\n\nPontuacao obtida nessa rodada pelo player: %d pontos", pontosDados);
            return pontosDados;
            break;
        case 0:
            printf("\n\nVoce pulou a vez e obteve 0 pontos na jogada");
            return 0;
            break;
        default:
            printf("\n\n##OPCAO INEXISTENTE##\n\n");
            return JogadaPlayer();
    }
}

int JogadaPlayer2() {
    int jogaOuPassa, pontosDados;

    printf("\n\nDigite 1 para jogar os dados ou 0 para passar a vez: ");
    scanf("%d", &jogaOuPassa);

    switch (jogaOuPassa) {
        case 1:
            pontosDados = rolarDados();
            printf("\n\nPontuacao obtida nessa rodada pelo player: %d pontos", pontosDados);
            return pontosDados;
            break;
        case 0:
            printf("\n\nVoce pulou a vez e obteve 0 pontos na jogada");
            return 0;
            break;
        default:
            printf("\n\n##OPCAO INEXISTENTE##\n\n");
            return JogadaPlayer2();
    }
}

int jogadaComp(int pontosCompTotais, int pontosPlayerTotais, int nJogadasComp) {
    int pontosDados;
    int pontosCriticos = 20;

    /* se o computador estiver com a partida ganha na ultima rodada ou com uma pontuação critica, visto que em cada
    partida ele ganha no minimo dois pontos, ele pula a vez*/
    if (pontosCompTotais > pontosPlayerTotais && nJogadasComp == gJogadasMax || pontosCompTotais >= pontosCriticos) {
        printf("\n\nO computador pulou a vez e obteve 0 pontos na rodada");
        return 0;
    }

    pontosDados = rolarDados();
    printf("\n\nPontuacao obtida nessa rodada pelo computador: %d pontos", pontosDados);
    return pontosDados;
}
int main( ){
    int opcaoJogo, pontosPlayerTotais = 0, pontosPlayerTemp = 0, pontosCompTotais = 0, nJogadasComp = 0, nJogadasPlayer = 0 , pontosCompTemp = 0, vezPlayer = 1, pontosPlayerTemp2 = 0, pontosPlayerTotais2 = 0, nJogadasPlayer2 = 0, jogadorAtual  = 1;
    srand(time(NULL));
    opcaoJogo = comecoJogo();

    if (opcaoJogo == 0){
        while (nJogadasPlayer < gJogadasMax && nJogadasComp < gJogadasMax){

            if (vezPlayer == 1 ){
                printf("\n\n-------------------------------------------------- JOGADA DO PLAYER ---------------------------------------------------");
                printf("\nPONTUACOES:\nPlayer = %d pontos\nComputador = %d pontos ", pontosPlayerTotais, pontosCompTotais);

                pontosPlayerTemp = JogadaPlayer();
                pontosPlayerTotais += pontosPlayerTemp;
                nJogadasPlayer++;
                vezPlayer = 0;
            }
            if (vezPlayer == 0){
                printf("\n\n----------------------------------------------- JOGADA DO COMPUTADOR ------------------------------------------------");
                printf("\nPONTUACOES:\nPlayer = %d pontos\nComputador = %d pontos ", pontosPlayerTotais, pontosCompTotais);

                pontosCompTemp = jogadaComp(pontosCompTotais, pontosPlayerTotais, nJogadasComp);
                pontosCompTotais += pontosCompTemp;
                nJogadasComp++;
                vezPlayer = 1;
            }
        }
            printf("\n\n-------------------------------------------------FIM DA PARTIDA ----------------------------------------------------");
            printf("\n\nPontuacoes Finais:\nPlayer: %d pontos\nComputador: %d pontos", pontosPlayerTotais, pontosCompTotais);

            if (pontosPlayerTotais > gPontosMax && pontosCompTotais > gPontosMax){
                printf("\n\nEMPATE!!!!!\nOs dois ultrapassaram a pontuacao maxima\n\n");
            }
            else if (pontosPlayerTotais > pontosCompTotais && pontosPlayerTotais <= gPontosMax){
                printf("\n\nVOCE VENCEU!!!!");
            }
            else if(pontosCompTotais > pontosPlayerTotais && pontosCompTotais <= gPontosMax){
                printf("\n\nVOCE PERDEU PARA O COMPUTADOR :( ");
            }
            else if(pontosCompTotais == pontosPlayerTotais && pontosCompTotais <= gPontosMax && pontosPlayerTotais <= gPontosMax){
                printf("\n\nEMPATE!!!");
            }
            else if(pontosCompTotais < pontosPlayerTotais && pontosPlayerTotais > gPontosMax && pontosCompTotais <= gPontosMax ){
                printf("\n\nVOCE PERDEU PARA O COMPUTADOR :( ");
            }
            else if(pontosPlayerTotais < pontosCompTotais && pontosCompTotais > gPontosMax && pontosPlayerTotais <= gPontosMax){
                printf("\n\nVOCE VENCEU!!!!");
            }
        }

    else if (opcaoJogo == 1){
        while (nJogadasPlayer < gJogadasMax && nJogadasPlayer2 < gJogadasMax){
            if (jogadorAtual  == 1 ){
                printf("\n\n-------------------------------------------------- JOGADA DO PLAYER ---------------------------------------------------");
                printf("\nPONTUACOES:\nPlayer = %d pontos\nComputador = %d pontos ", pontosPlayerTotais, pontosPlayerTotais2);

                pontosPlayerTemp = JogadaPlayer();
                pontosPlayerTotais += pontosPlayerTemp;
                nJogadasPlayer++;
                jogadorAtual  = 2;
            }
            if (jogadorAtual  == 2){
                printf("\n\n-------------------------------------------------- JOGADA DO PLAYER 2---------------------------------------------------");
                printf("\nPONTUACOES:\nPlayer = %d pontos\nPlayer 2 = %d pontos ", pontosPlayerTotais, pontosPlayerTotais2);

                pontosPlayerTemp2 = JogadaPlayer2();
                pontosPlayerTotais2 += pontosPlayerTemp2;
                nJogadasPlayer2++;
                jogadorAtual  = 1;
            }
        }
            printf("\n\n-------------------------------------------------- FIM DA PARTIDA =----------------------------------------------------");
            printf("\n\nPontuacoes Finais:\nPlayer: %d pontos\nPlayer 2: %d pontos", pontosPlayerTotais, pontosPlayerTotais2);

            if (pontosPlayerTotais > gPontosMax && pontosPlayerTotais2 > gPontosMax){
                printf("\n\nEMPATE!!!!!\nOs dois ultrapassaram a pontuacao maxima\n\n");
            }

            else if (pontosPlayerTotais > pontosPlayerTotais2 && pontosPlayerTotais <= gPontosMax){
                printf("\n\nO JOGADOR 1 VENCEU");
            }

            else if(pontosPlayerTotais2 > pontosPlayerTotais && pontosPlayerTotais2 <= gPontosMax){
                printf("\n\nO JOGADOR 2 VENCEU");
            }

            else if(pontosPlayerTotais2 == pontosPlayerTotais && pontosPlayerTotais2 <= gPontosMax && pontosPlayerTotais <= gPontosMax){
                printf("\n\nEMPATE!!!");
            }
            else if(pontosPlayerTotais2 < pontosPlayerTotais && pontosPlayerTotais > gPontosMax && pontosPlayerTotais2 <= gPontosMax){
                printf("\n\nO JOGADOR 2 VENCEU!!!!");
            }
            else if(pontosPlayerTotais < pontosPlayerTotais2 && pontosPlayerTotais2 > gPontosMax && pontosPlayerTotais <= gPontosMax){
                printf("\n\nO JOGADOR 1 VENCEU");
            }
        }

    return 0;
}
