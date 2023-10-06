#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <math.h>

#define MOUSE_CLICADO                   1
#define MOUSE_SOLTO                     0
#define DIMENSAO_QUADR_TAB              100
#define ESPACO_BASES                    33
#define yBases                          27
#define xBases                          393 
#define BONUS                           2
#define BONUS_COMBO                     10
#define FRAMES_SEGUNDO                  30 
#define DADOS_DIMENSAO                  2
#define DISTANCIA_AJUDA                 322
#define MINNUTO_HORA                    60 
                                        

float x;
float y; 
bool arrastarPecas = false;
int segundoClique = 0;
int contPecaBase = 0; 
int bombasUsadas = 0, girarUsados = 0; 

int gExibirRanking = 0, gExibirAjuda = 0, gExibirJogo = 0, gExibirMenu = 1, gExibirPause = 0;

enum BOMBA {
    LINHA_LINHA = 0,
    COLUNA_COLUNA,
    LINHA_COLUNA,
    N_OPCOES_BOMBA 
};

typedef enum Telas {
    tRANKING = 0,
    tAJUDA,
    tJOGO,
    tMENU,
    tPAUSE
}Telas;

typedef enum TIPO_PECA {
    INDIVIDUAL = 0,
    DUPLA_LATERAL,
    DUPLA_SUPERIOR,
    TRIO_INFERIOR_ESQUERDO,
    TRIO_INFERIOR_DIREITO,
    TRIO_SUPERIOR_ESQUERDO,
    TRIO_SUPERIOR_DIREITO, 
    N_TIPOS
}TIPO_PECA;

typedef struct COORDENADAS
{
    int x;
    int y;

}COORDENADAS;

typedef struct botoes
{
    COORDENADAS cord;
    int larg;
    int alt;
    int distBot;
    int raio;

};

struct botoes retang = { 448, 339, 382, 78, 116, 0 };
struct botoes circ = { 51, 49, 0, 0, 1177, 37 };

typedef struct TABULEIRO
{
    COORDENADAS cord;
    bool temPeca;

} TABULEIRO;

#define TAM_MAX_TAB 5
TABULEIRO tabuleiro_quadr[TAM_MAX_TAB][TAM_MAX_TAB];

typedef struct BASE_DADOS
{
    COORDENADAS cord;
    bool temPeca;

} BASE_DADOS;

#define MAX_BASE_DADOS                  3
BASE_DADOS baseDados[MAX_BASE_DADOS];

typedef struct DADO
{
    int valor; 
    bool usado; 
    int coluna; 
    int linha; 

}DADO;


typedef struct PECA
{
    DADO dados[DADOS_DIMENSAO][DADOS_DIMENSAO];
    COORDENADAS cord;
    TIPO_PECA tipo;
    bool movimento;
    bool desenhar; 
    bool base;
    bool tabuleiro; 

}PECA;
 
#define MAX_N_PECAS                     200
PECA pecas[MAX_N_PECAS]; 

void must_init(bool test, const char* description)
{
    if (test)
        return;

    printf("couldn't initialize %s\n", description);
    exit(1);
}

ALLEGRO_SAMPLE* menuClick;
ALLEGRO_SAMPLE* fundoMusica;
ALLEGRO_SAMPLE* esplosao;
ALLEGRO_SAMPLE* conquista;

void audio_init()
{
    al_install_audio();
    al_init_acodec_addon();
    al_reserve_samples(128);

    menuClick = al_load_sample("clickbarulho.wav");
    must_init(menuClick, "menuClick");

    esplosao = al_load_sample("esplosao.wav");
    must_init(esplosao, "esplosao");

    conquista = al_load_sample("conquista.wav");
    must_init(conquista, "conquista");
}

void audio_deinit()
{
    al_destroy_sample(esplosao);
    al_destroy_sample(menuClick);
    //al_destroy_sample(fundoMusica);
    al_destroy_sample(conquista);
}

int aleatorio(int max)
{
    return rand() % max;
}

#define LARGURA_TELA                    1280
#define ALTURA_TELA                     720
ALLEGRO_DISPLAY* display;

void display_init()
{
    al_set_new_display_option(ALLEGRO_SAMPLE_BUFFERS, 1, ALLEGRO_SUGGEST);
    al_set_new_display_option(ALLEGRO_SAMPLES, 8, ALLEGRO_SUGGEST);
    al_set_new_bitmap_flags(ALLEGRO_MIN_LINEAR | ALLEGRO_MAG_LINEAR);

    display = al_create_display(LARGURA_TELA, ALTURA_TELA);
    must_init(display, "display");
}

void display_deinit()
{
    al_destroy_display(display);
}

ALLEGRO_BITMAP* imagem_telaMenu;
ALLEGRO_BITMAP* imagem_jogo;
ALLEGRO_BITMAP* imagem_ajuda;
ALLEGRO_BITMAP* imagem_pause;
ALLEGRO_BITMAP* imagem_ranking;

ALLEGRO_BITMAP* dado0;
ALLEGRO_BITMAP* dado1;
ALLEGRO_BITMAP* dado2;
ALLEGRO_BITMAP* dado3;
ALLEGRO_BITMAP* dado4;
ALLEGRO_BITMAP* dado5;
ALLEGRO_BITMAP* dado6;

void imagens_init()
{
    imagem_telaMenu = al_load_bitmap("fundo.png");
    must_init(imagem_telaMenu, "imagem_menu");
    imagem_jogo = al_load_bitmap("telaJogo.png");
    must_init(imagem_jogo, "imagem_jogo");
    imagem_ajuda = al_load_bitmap("telaAjuda.png");
    must_init(imagem_ajuda, "imagem_ajuda");
    imagem_pause = al_load_bitmap("telaPause.png");
    must_init(imagem_pause, "imagem_pause");
    imagem_ranking = al_load_bitmap("telaRanking.png");
    must_init(imagem_ranking, "imagem_ranking");

    dado0 = al_load_bitmap("dado0.png");
    must_init(dado0, "dado0");
    dado1 = al_load_bitmap("dado1.png");
    must_init(dado1, "dado1");
    dado2 = al_load_bitmap("dado2.png");
    must_init(dado2, "dado2");
    dado3 = al_load_bitmap("dado3.png");
    must_init(dado3, "dado3");
    dado4 = al_load_bitmap("dado4.png");
    must_init(dado4, "dado4");
    dado5 = al_load_bitmap("dado5.png");
    must_init(dado5, "dado5");
    dado6 = al_load_bitmap("dado6.png");
    must_init(dado6, "dado6");
}

void imagens_deinit()
{
    al_destroy_bitmap(imagem_telaMenu);
    al_destroy_bitmap(imagem_jogo);
    al_destroy_bitmap(imagem_ajuda);
    al_destroy_bitmap(imagem_pause);
    al_destroy_bitmap(imagem_ranking);

    al_destroy_bitmap(dado0);
    al_destroy_bitmap(dado1);
    al_destroy_bitmap(dado2);
    al_destroy_bitmap(dado3);
    al_destroy_bitmap(dado4);
    al_destroy_bitmap(dado5);
    al_destroy_bitmap(dado6);
}

void tabuleiroCoordenadas_init()
{
    int x_quadr_ini = 642, y_quadr_ini = 148;
    int x_quadr_fim = 742, y_quadr_fim = 248;
    int i = 0, j = 0;

    for (i = 0; i < TAM_MAX_TAB; i++)
    {
        for (j = 0; j < TAM_MAX_TAB; j++)
        {
            tabuleiro_quadr[i][j].cord.x = j * DIMENSAO_QUADR_TAB + 642;
            tabuleiro_quadr[i][j].cord.y = i * DIMENSAO_QUADR_TAB + 148;
            tabuleiro_quadr[i][j].temPeca = false;
        }
    }
}

void baseDados_init()
{
    int y = yBases;

    for (int i = 0; i < MAX_BASE_DADOS; i++)
    {
        baseDados[i].cord.x = xBases;
        baseDados[i].cord.y = y;
        y += ESPACO_BASES + DIMENSAO_QUADR_TAB + DIMENSAO_QUADR_TAB;
    }
}

void alteraTelas(int proximaTela)
{
    if (proximaTela == tRANKING) {
        gExibirRanking = 1;
        gExibirAjuda = 0;
        gExibirJogo = 0;
        gExibirMenu = 0;
        gExibirPause = 0;
    }

    if (proximaTela == tAJUDA) {
        gExibirRanking = 0;
        gExibirAjuda = 1;
        gExibirJogo = 0;
        gExibirMenu = 0;
        gExibirPause = 0;
    }

    if (proximaTela == tJOGO) {
        gExibirRanking = 0;
        gExibirAjuda = 0;
        gExibirJogo = 1;
        gExibirMenu = 0;
        gExibirPause = 0;
    }

    if (proximaTela == tMENU) {
        gExibirRanking = 0;
        gExibirAjuda = 0;
        gExibirJogo = 0;
        gExibirMenu = 1;
        gExibirPause = 0;
    }

    if (proximaTela == tPAUSE) {
        gExibirRanking = 0;
        gExibirAjuda = 0;
        gExibirJogo = 0;
        gExibirMenu = 0;
        gExibirPause = 1;
    }
}

void desenhaTela(int imagem_ajuda, int imagem_jogo, int imagem_menu, int imagem_pause, int imagem_ranking)
{
    if (gExibirMenu)
        al_draw_bitmap(imagem_menu, 0, 0, 0);

    if (gExibirJogo)
        al_draw_bitmap(imagem_jogo, 0, 0, 0);

    if (gExibirAjuda)
        al_draw_bitmap(imagem_ajuda, 0, 0, 0);

    if (gExibirPause)
        al_draw_bitmap(imagem_pause, 0, 0, 0);

    if (gExibirRanking)
        al_draw_bitmap(imagem_ranking, 0, 0, 0);
}

void botoes_telas(int x, int y, int *done)
{
    int dist = 0;

    if (gExibirAjuda)
    {
        dist = sqrt((circ.cord.x - x) * (circ.cord.x - x) + (circ.cord.y - y + DISTANCIA_AJUDA) * (circ.cord.y - y + DISTANCIA_AJUDA));
        if (dist <= circ.raio) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tMENU);
        }
    }

    if (gExibirJogo)
    {
        dist = sqrt(((circ.cord.x + circ.distBot) - x) * ((circ.cord.x + circ.distBot) - x) + (circ.cord.y - y) * (circ.cord.y - y));
        if (dist <= circ.raio) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tPAUSE);
        }
    }

    if (gExibirMenu)
    {
        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y && y <= retang.cord.y + retang.alt)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tJOGO);
        }

        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y + retang.distBot && y <= retang.cord.y + retang.alt + retang.distBot)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tJOGO);
        }

        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y + (retang.distBot * 2) && y <= retang.cord.y + retang.alt + (retang.distBot * 2))) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tRANKING);
        }

        dist = sqrt(((circ.cord.x + circ.distBot) - x) * ((circ.cord.x + circ.distBot) - x) + (circ.cord.y - y) * (circ.cord.y - y));
        if (dist <= circ.raio) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            *done = true; 
        }

        dist = sqrt((circ.cord.x - x) * (circ.cord.x - x) + (circ.cord.x - y) * (circ.cord.x - y));
        if (dist <= circ.raio) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tAJUDA);
        }
    }

    if (gExibirRanking)
    {
        dist = sqrt((circ.cord.x - x) * (circ.cord.x - x) + (circ.cord.x - y) * (circ.cord.x - y));
        if (dist <= circ.raio) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tMENU);
        }
    }

    if (gExibirPause)
    {
        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y && y <= retang.cord.y + retang.alt)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tJOGO);
        }

        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y + retang.distBot && y <= retang.cord.y + retang.alt + retang.distBot)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            *done = true;
        }

        if ((x >= retang.cord.x && x <= retang.cord.x + retang.larg) && (y >= retang.cord.y + (retang.distBot * 2) && y <= retang.cord.y + retang.alt + (retang.distBot * 2))) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            alteraTelas(tMENU);
        }
    }
}

void define_PecasTipos()
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        pecas[i].tipo = aleatorio(N_TIPOS); 

        switch (pecas[i].tipo)
        {
        case INDIVIDUAL:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = false;
            pecas[i].dados[1][0].usado = false;
            pecas[i].dados[1][1].usado = false;
            break;
                
        case DUPLA_LATERAL:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = false;
            pecas[i].dados[1][0].usado = true;
            pecas[i].dados[1][1].usado = false;
            break;

        case DUPLA_SUPERIOR:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = true;
            pecas[i].dados[1][0].usado = false;
            pecas[i].dados[1][1].usado = false;
            break;

        case TRIO_INFERIOR_ESQUERDO:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = true;
            pecas[i].dados[1][0].usado = false;
            pecas[i].dados[1][1].usado = true;
            break;

        case TRIO_INFERIOR_DIREITO:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = true;
            pecas[i].dados[1][0].usado = true;
            pecas[i].dados[1][1].usado = false;
            break;

        case TRIO_SUPERIOR_ESQUERDO:
            pecas[i].dados[0][0].usado = false;
            pecas[i].dados[0][1].usado = true;
            pecas[i].dados[1][0].usado = true;
            pecas[i].dados[1][1].usado = true;
            break;

        case TRIO_SUPERIOR_DIREITO:
            pecas[i].dados[0][0].usado = true;
            pecas[i].dados[0][1].usado = false;
            pecas[i].dados[1][0].usado = true;
            pecas[i].dados[1][1].usado = true;
            break;
        }
    }
}

void define_ValoresDados()
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        for (int j = 0; j < DADOS_DIMENSAO; j++)
        {
            for (int k = 0; k < DADOS_DIMENSAO; k++)
            {
                if (pecas[i].dados[j][k].usado)
                {
                    pecas[i].dados[j][k].valor = aleatorio(6);
                }
            }
        }
    }
}

void define_CoordenadasPecas()
{
    int cont = 0;

    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        pecas[i].cord.x = baseDados[cont].cord.x;
        pecas[i].cord.y = baseDados[cont].cord.y;
        pecas[i].desenhar = false;
        pecas[i].base = false;
        pecas[i].tabuleiro = false;

        cont++;
        if (cont >= MAX_BASE_DADOS)
            cont = 0;
    }
}

void zera_colunasLinhas()
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        for (int j = 0; j < DADOS_DIMENSAO; j++)
        {
            for (int k = 0; k < DADOS_DIMENSAO; k++)
            {
                pecas[i].dados[j][k].coluna = -1; 
                pecas[i].dados[j][k].linha = -1; 
            }
        }
    }
}

int montaBanca()
{
    int pecasColocadas = 0;

    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if (!pecas[i].tabuleiro)
        {
            for (int j = i; j < i + 3; j++)
            {
                pecas[j].desenhar = true;
                pecas[j].base = true;
                pecasColocadas++;
            }
        }

        if (pecasColocadas == 3)
            break;
    }
    return 0;
}

void desenha_valor_dados(int valorDado, int x, int y)
{
    if (gExibirJogo){
        switch (valorDado)
        {
        case 0:
            al_draw_bitmap(dado0, x, y, 0);
            break;

        case 1:
            al_draw_bitmap(dado1, x, y, 0);
            break;

        case 2:
            al_draw_bitmap(dado2, x, y, 0);
            break;

        case 3:
            al_draw_bitmap(dado3, x, y, 0);
            break;

        case 4:
            al_draw_bitmap(dado4, x, y, 0);
            break;

        case 5:
            al_draw_bitmap(dado5, x, y, 0);
            break;

        case 6:
            al_draw_bitmap(dado6, x, y, 0);
            break;
        }
    }
}

void desenha_pecas()
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if (pecas[i].desenhar)
        {
            if (pecas[i].dados[0][0].usado)
            {
                desenha_valor_dados(pecas[i].dados[0][0].valor, pecas[i].cord.x, pecas[i].cord.y);
            }

            if (pecas[i].dados[0][1].usado)
            {
                desenha_valor_dados(pecas[i].dados[0][1].valor, pecas[i].cord.x + 100, pecas[i].cord.y);
            }

            if (pecas[i].dados[1][0].usado)
            {
                desenha_valor_dados(pecas[i].dados[1][0].valor, pecas[i].cord.x, pecas[i].cord.y + 100);
            }

            if (pecas[i].dados[1][1].usado)
            {
                desenha_valor_dados(pecas[i].dados[1][1].valor, pecas[i].cord.x + 100, pecas[i].cord.y + 100);
            }
        }
    }
}

void dados_init()
{
    define_PecasTipos();
    define_ValoresDados();
    define_CoordenadasPecas();
    zera_colunasLinhas(); 
    montaBanca();
    desenha_pecas();
}

#define TAM_TOTAL_BASE              200

void botoes_dados(int x, int y)
{
    if (gExibirJogo)
    { 
        if ((x >= baseDados[0].cord.x && x <= baseDados[0].cord.x + TAM_TOTAL_BASE) && (y >= baseDados[0].cord.y && y <= baseDados[0].cord.y + TAM_TOTAL_BASE))
        {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            arrasta_pecas(baseDados[0].cord.y, baseDados[0].cord.y + TAM_TOTAL_BASE);
            arrastarPecas = true;
            baseDados[0].temPeca = false; 

        }

        if ((x >= baseDados[1].cord.x && x <= baseDados[1].cord.x + TAM_TOTAL_BASE) && (y >= baseDados[1].cord.y && y <= baseDados[1].cord.y + TAM_TOTAL_BASE))
        {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            arrasta_pecas(baseDados[1].cord.y, baseDados[1].cord.y + TAM_TOTAL_BASE);
            arrastarPecas = true;
            baseDados[1].temPeca = false;
        }

        if ((x >= baseDados[2].cord.x && x <= baseDados[2].cord.x + TAM_TOTAL_BASE) && (y >= baseDados[2].cord.y && y <= baseDados[2].cord.y + TAM_TOTAL_BASE))
        {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            arrasta_pecas(baseDados[2].cord.y, baseDados[2].cord.y + TAM_TOTAL_BASE);
            arrastarPecas = true; 
            baseDados[2].temPeca = false;
        }
    }
}

int arrasta_pecas(int yMin, int yMax)
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if ((pecas[i].cord.y <= yMax && pecas[i].cord.y >= yMin) && (pecas[i].base && !pecas[i].movimento))
        {
            pecas[i].movimento = true;
            return; 
        }
    }
}

bool collide(int ax1, int ay1, int ax2, int ay2, int bx1, int by1, int bx2, int by2)
{
    if (ax1 >= bx2) return false;
    if (ax2 <= bx1) return false;
    if (ay1 >= by2) return false;
    if (ay2 <= by1) return false;

    return true;
}

void novasCoord_collisoes(int i, int j, int k)
{
    switch (pecas[i].tipo)
    {
    case INDIVIDUAL:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j; 
        pecas[i].dados[0][0].coluna = k; 
        break;

    case DUPLA_LATERAL:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j;
        pecas[i].dados[0][0].coluna = k;

        tabuleiro_quadr[j + 1][k].temPeca = true;
        pecas[i].dados[1][0].linha = j + 1;
        pecas[i].dados[1][0].coluna = k;
        break;

    case DUPLA_SUPERIOR:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j;
        pecas[i].dados[0][0].coluna = k;

        tabuleiro_quadr[j][k + 1].temPeca = true;
        pecas[i].dados[0][1].linha = j;
        pecas[i].dados[0][1].coluna = k + 1;
        break;

    case TRIO_INFERIOR_ESQUERDO:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j;
        pecas[i].dados[0][0].coluna = k;

        tabuleiro_quadr[j][k + 1].temPeca = true;
        pecas[i].dados[0][1].linha = j;
        pecas[i].dados[0][1].coluna = k + 1;

        tabuleiro_quadr[j + 1][k + 1].temPeca = true;
        pecas[i].dados[1][1].linha = j + 1;
        pecas[i].dados[1][1].coluna = k + 1;
        break;

    case TRIO_INFERIOR_DIREITO:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j;
        pecas[i].dados[0][0].coluna = k;

        tabuleiro_quadr[j][k + 1].temPeca = true;
        pecas[i].dados[0][1].linha = j;
        pecas[i].dados[0][1].coluna = k + 1;

        tabuleiro_quadr[j + 1][k].temPeca = true;
        pecas[i].dados[1][0].linha = j + 1;
        pecas[i].dados[1][0].coluna = k;
        break;

    case TRIO_SUPERIOR_ESQUERDO:
        tabuleiro_quadr[j + 1][k].temPeca = true;
        pecas[i].dados[1][0].linha = j + 1;
        pecas[i].dados[1][0].coluna = k;

        tabuleiro_quadr[j][k + 1].temPeca = true;
        pecas[i].dados[0][1].linha = j;
        pecas[i].dados[0][1].coluna = k + 1;

        tabuleiro_quadr[j + 1][k + 1].temPeca = true;
        pecas[i].dados[1][1].linha = j + 1;
        pecas[i].dados[1][1].coluna = k + 1;
        break;

    case TRIO_SUPERIOR_DIREITO:
        tabuleiro_quadr[j][k].temPeca = true;
        pecas[i].dados[0][0].linha = j;
        pecas[i].dados[0][0].coluna = k;

        tabuleiro_quadr[j + 1][k].temPeca = true;
        pecas[i].dados[1][0].linha = j + 1;
        pecas[i].dados[1][0].coluna = k;

        tabuleiro_quadr[j + 1][k + 1].temPeca = true;
        pecas[i].dados[1][1].linha = j + 1;
        pecas[i].dados[1][1].coluna = k + 1;
        break;
    }

    pecas[i].cord.x = tabuleiro_quadr[j][k].cord.x;
    pecas[i].cord.y = tabuleiro_quadr[j][k].cord.y;
    pecas[i].movimento = false;
    pecas[i].tabuleiro = true;
    pecas[i].base = false;
    contPecaBase--;
}

void testa_colissoes(int* linhasPontos, int* colunasPontos, int *verificaTabLimpo)
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if (pecas[i].movimento)
        {
            for (int j = 0; j < TAM_MAX_TAB; j++)
            {
                for (int k = 0; k < TAM_MAX_TAB; k++)
                {
                    if (collide(pecas[i].cord.x, pecas[i].cord.y, pecas[i].cord.x + 100, pecas[i].cord.y + 100, tabuleiro_quadr[j][k].cord.x, 
                        tabuleiro_quadr[j][k].cord.y, tabuleiro_quadr[j][k].cord.x + 100, tabuleiro_quadr[j][k].cord.y + 100))
                    {
                        switch (pecas[i].tipo)
                        {
                        case INDIVIDUAL:
                        
                            if (!tabuleiro_quadr[j][k].temPeca)
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case DUPLA_LATERAL:
                            if ((!tabuleiro_quadr[j][k].temPeca && !tabuleiro_quadr[j + 1][k].temPeca) && (j != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case DUPLA_SUPERIOR:
                            if ((!tabuleiro_quadr[j][k].temPeca && !tabuleiro_quadr[j][k + 1].temPeca) && (k != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case TRIO_INFERIOR_ESQUERDO:
                            if ((!tabuleiro_quadr[j][k].temPeca && !tabuleiro_quadr[j][k + 1].temPeca && !tabuleiro_quadr[j + 1][k + 1].temPeca) && (k != 4) && (j != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case TRIO_INFERIOR_DIREITO:
                            if ((!tabuleiro_quadr[j][k].temPeca && !tabuleiro_quadr[j][k + 1].temPeca && !tabuleiro_quadr[j + 1][k].temPeca) && (k != 4) && (j != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case TRIO_SUPERIOR_ESQUERDO:
                            if ((!tabuleiro_quadr[j + 1][k].temPeca && !tabuleiro_quadr[j][k + 1].temPeca && !tabuleiro_quadr[j + 1][k + 1].temPeca) && (k != 4) && (j != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;

                        case TRIO_SUPERIOR_DIREITO:
                            if ((!tabuleiro_quadr[j][k].temPeca && !tabuleiro_quadr[j + 1][k].temPeca && !tabuleiro_quadr[j + 1][k + 1].temPeca) && (k != 4) && (j != 4))
                            {
                                novasCoord_collisoes(i, j, k);
                            }
                            break;
                        }
                        (*verificaTabLimpo) = true;
                        pontos_update(i, linhasPontos, colunasPontos);

                        return; 
                    }
                }
            }
        }
    }
}

int pontos_update(int i, int *linhasPontos, int *colunasPontos)
{
    for (int j = 0; j < DADOS_DIMENSAO; j++)
    {
        for (int k = 0; k < DADOS_DIMENSAO; k++)
        {
            if (pecas[i].dados[j][k].usado) 
            {
                linhasPontos[pecas[i].dados[j][k].linha] += pecas[i].dados[j][k].valor;
                colunasPontos[pecas[i].dados[j][k].coluna] += pecas[i].dados[j][k].valor;
            }
        }
    }
}

ALLEGRO_FONT* font;
void hud_init()
{
    font = al_load_font("fontejogo.ttf", 18, 0); 
    must_init(font, "font"); 

}

void hud_deinit()
{
    al_destroy_font(font);
}

int exclui_colunas(int colunasExcesso, int *linhasPontos, int*colunaPontos)
{
    int cont = 0;

    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        for (int j = 0; j < DADOS_DIMENSAO; j++)
        {
            for (int k = 0; k < DADOS_DIMENSAO; k++)
            {       
                if (pecas[i].dados[j][k].coluna == colunasExcesso)
                {
                    pecas[i].dados[j][k].usado = false;
                    tabuleiro_quadr[pecas[i].dados[j][k].linha][pecas[i].dados[j][k].coluna].temPeca = false;
                    cont++; 

                    linhasPontos[pecas[i].dados[j][k].linha] -= pecas[i].dados[j][k].valor;
                    pecas[i].dados[j][k].valor = 0; 
                }
            }
        }
    }       
    return cont; 
}

int exclui_linhas(int linhasExcesso, int *linhasPontos, int *colunasPontos)
{
    int cont = 0; 

    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        for (int j = 0; j < DADOS_DIMENSAO; j++)
        {
            for (int k = 0; k < DADOS_DIMENSAO; k++)
            {  
                if (pecas[i].dados[j][k].linha == linhasExcesso)
                {
                    pecas[i].dados[j][k].usado = false;
                    tabuleiro_quadr[pecas[i].dados[j][k].linha][pecas[i].dados[j][k].coluna].temPeca = false; 
                    cont++; 

                    colunasPontos[pecas[i].dados[j][k].coluna] -= pecas[i].dados[j][k].valor;
                    pecas[i].dados[j][k].valor = 0;
                }
            }
        }
    }
    return cont; 
}

#define MAX_COL_LINH                10

int excessos_pontos(int *linhasPontos, int *colunasPontos, int *pontuacaoTotal, int *multilinha, int *combo)
{
    bool linhaLimpa = false; 
    bool colunaLimpa = false; 
    int pontosColunas = 0, pontosLinhas = 0; 

    for (int i = 0; i < TAM_MAX_TAB; i++)
    {
        if (colunasPontos[i] == MAX_COL_LINH)
        {
            if (colunasPontos[i + 1] == MAX_COL_LINH)
            {
                *pontuacaoTotal += exclui_colunas(i, linhasPontos, colunasPontos) * BONUS;
                colunasPontos[i] = 0;
                (*multilinha)++; 
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; 
            }

            else
            {
                *pontuacaoTotal += exclui_colunas(i, linhasPontos, colunasPontos);
                colunasPontos[i] = 0;
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; 
            }

            colunaLimpa = true; 

            if (colunaLimpa && linhaLimpa)
            {
                (*combo)++;
                colunaLimpa = false;
                linhaLimpa = false;
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                return; 
            }
        }

        if (linhasPontos[i] == MAX_COL_LINH)
        {
            if (linhasPontos[i + 1] == MAX_COL_LINH)
            {
                *pontuacaoTotal += exclui_linhas(i, linhasPontos, colunasPontos) * BONUS;
                linhasPontos[i] = 0;
                (*multilinha)++;
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; 
            }

            else
            { 
                *pontuacaoTotal += exclui_linhas(i, linhasPontos, colunasPontos);
                linhasPontos[i] = 0;
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                break; 
            }
            linhaLimpa = true; 

            if (colunaLimpa && linhaLimpa)
            {
                (*combo)++;
                colunaLimpa = false;
                linhaLimpa = false;
                *pontuacaoTotal += BONUS_COMBO; 
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
                return; 
            }
        }
    }
}

void acao_bomba(int* linhasPontos, int* colunasPontos)
{
    int valor1 = aleatorio(TAM_MAX_TAB);
    int valor2 = 0; 

    do {
        valor2 = aleatorio(TAM_MAX_TAB);

    } while (valor2 == valor1); 

    int opcao = aleatorio(N_OPCOES_BOMBA);

    switch (opcao)
    {
    case LINHA_LINHA: 
        exclui_linhas(valor1, linhasPontos, colunasPontos);
        exclui_linhas(valor2, linhasPontos, colunasPontos); 

        linhasPontos[valor1] = 0;
        linhasPontos[valor2] = 0;
        break;
    
    case COLUNA_COLUNA:
        exclui_colunas(valor1, linhasPontos, colunasPontos);
        exclui_colunas(valor2, linhasPontos, colunasPontos);

        colunasPontos[valor1] = 0;
        colunasPontos[valor2] = 0;
        break; 

    case LINHA_COLUNA:
        exclui_linhas(valor1, linhasPontos, colunasPontos);
        exclui_colunas(valor2, linhasPontos, colunasPontos);

        linhasPontos[valor1] = 0;
        colunasPontos[valor2] = 0;
        break; 
    }
}

#define MIN_BOMBA                       1
#define MIN_GIRAR                       50
#define MIN_UNDO                        5

#define RAIO_BOT_JOGO                   51
#define RAIO_VOLTAR                     25
#define xBOTOES_JOGO                    159
#define yUNDO                           450
#define yBOMBA                          584 
#define xVOLTAR                         334
#define yVOLTAR_1                       139
#define yVOLTAR_2                       360
#define yVOLTAR_3                       593 

void botoes_jogo(int x, int y, int* linhasPontos, int* colunasPontos, int *bombasDisp, int *girarDisp, int *undoDisp)
{
    int dist = 0; 

    if (gExibirJogo)
    {
        dist = sqrt((xBOTOES_JOGO - x) * (xBOTOES_JOGO - x) + (yUNDO - y) * (yUNDO - y));
        if (dist <= RAIO_BOT_JOGO && undoDisp){
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            acao_undo(linhasPontos, colunasPontos);
            (*undoDisp) = 0; 
        }
    }

    if (gExibirJogo)
    {
        dist = sqrt((xBOTOES_JOGO - x) * (xBOTOES_JOGO - x) + (yBOMBA - y) * (yBOMBA - y));
        if (dist <= RAIO_BOT_JOGO && (*bombasDisp > 0)) {
            al_play_sample(esplosao, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            acao_bomba(linhasPontos, colunasPontos);
            bombasUsadas++; 
        }
    }

    if (gExibirJogo)
    {
        dist = sqrt((xVOLTAR - x) * (xVOLTAR - x) + (yVOLTAR_1 - y) * (yVOLTAR_1 - y));
        if ((dist <= RAIO_VOLTAR) && (*girarDisp > 0)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            girar_peca(baseDados[0].cord.x, baseDados[0].cord.y);
            girarUsados++; 
        }
    }

    if (gExibirJogo)
    {
        dist = sqrt((xVOLTAR - x) * (xVOLTAR - x) + (yVOLTAR_2 - y) * (yVOLTAR_2 - y));
        if ((dist <= RAIO_VOLTAR) && (*girarDisp > 0)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            girar_peca(baseDados[1].cord.x, baseDados[1].cord.y);
            girarUsados++; 
        }
    }

    if (gExibirJogo)
    {
        dist = sqrt((xVOLTAR - x) * (xVOLTAR - x) + (yVOLTAR_3 - y) * (yVOLTAR_3 - y));
        if ((dist <= RAIO_VOLTAR) && (*girarDisp > 0)) {
            al_play_sample(menuClick, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL);
            girar_peca(baseDados[2].cord.x, baseDados[2].cord.y);
            girarUsados++; 
        }
    }
}

void altera_tipo(int i, int tipoNovo)
{
    switch (tipoNovo)
    {

    case DUPLA_LATERAL:
        pecas[i].tipo = DUPLA_LATERAL; 

        pecas[i].dados[0][0].usado = true;
        pecas[i].dados[0][1].usado = false;
        pecas[i].dados[1][0].usado = true;
        pecas[i].dados[1][1].usado = false;
        break;

    case DUPLA_SUPERIOR:
        pecas[i].tipo = DUPLA_SUPERIOR; 

        pecas[i].dados[0][0].usado = true;
        pecas[i].dados[0][1].usado = true;
        pecas[i].dados[1][0].usado = false;
        pecas[i].dados[1][1].usado = false; 
        break;

    case TRIO_INFERIOR_ESQUERDO:
        pecas[i].tipo = TRIO_INFERIOR_ESQUERDO; 

        pecas[i].dados[0][0].usado = true;
        pecas[i].dados[0][1].usado = true;
        pecas[i].dados[1][0].usado = false;
        pecas[i].dados[1][1].usado = true;
        break;

    case TRIO_INFERIOR_DIREITO:
        pecas[i].tipo = TRIO_INFERIOR_DIREITO; 

        pecas[i].dados[0][0].usado = true;
        pecas[i].dados[0][1].usado = true;
        pecas[i].dados[1][0].usado = true;
        pecas[i].dados[1][1].usado = false;
        break;

    case TRIO_SUPERIOR_ESQUERDO:
        pecas[i].tipo = TRIO_SUPERIOR_ESQUERDO; 

        pecas[i].dados[0][0].usado = false;
        pecas[i].dados[0][1].usado = true;
        pecas[i].dados[1][0].usado = true;
        pecas[i].dados[1][1].usado = true;
        break;

    case TRIO_SUPERIOR_DIREITO:
        pecas[i].tipo = TRIO_SUPERIOR_DIREITO; 

        pecas[i].dados[0][0].usado = true;
        pecas[i].dados[0][1].usado = false;
        pecas[i].dados[1][0].usado = true;
        pecas[i].dados[1][1].usado = true;
        break;
    }
}

int girar_peca(int x, int y)
{
    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if (pecas[i].cord.x == x && pecas[i].cord.y == y)
        {
            int valor_00 = pecas[i].dados[0][0].valor; 
            int valor_01 = pecas[i].dados[0][1].valor;
            int valor_10 = pecas[i].dados[1][0].valor;
            int valor_11 = pecas[i].dados[1][1].valor;

            switch (pecas[i].tipo)
            {

            case DUPLA_LATERAL:
                altera_tipo(i, DUPLA_SUPERIOR);

                pecas[i].dados[0][1].valor = valor_00; 
                pecas[i].dados[0][0].valor = valor_10; 

                break;

            case DUPLA_SUPERIOR:
                altera_tipo(i, DUPLA_LATERAL);
                pecas[i].dados[1][0].valor = valor_01; 

                break;

            case TRIO_INFERIOR_ESQUERDO:
                altera_tipo(i, TRIO_SUPERIOR_ESQUERDO);

                pecas[i].dados[0][1].valor = valor_00;
                pecas[i].dados[1][0].valor = valor_11;
                pecas[i].dados[1][1].valor = valor_01;

                break;

            case TRIO_INFERIOR_DIREITO:
                altera_tipo(i, TRIO_INFERIOR_ESQUERDO);

                pecas[i].dados[0][0].valor = valor_10;
                pecas[i].dados[0][1].valor = valor_00;
                pecas[i].dados[1][1].valor = valor_01;

                break;

            case TRIO_SUPERIOR_ESQUERDO:
                altera_tipo(i, TRIO_SUPERIOR_DIREITO);

                pecas[i].dados[0][0].valor = valor_10;
                pecas[i].dados[1][0].valor = valor_11;
                pecas[i].dados[1][1].valor = valor_01;

                break;

            case TRIO_SUPERIOR_DIREITO:
                altera_tipo(i, TRIO_INFERIOR_DIREITO);

                pecas[i].dados[0][0].valor = valor_10;
                pecas[i].dados[0][1].valor = valor_00;
                pecas[i].dados[1][0].valor = valor_11;

                break;
            }
            return;
        }
    }
}

void tempo_jogo(int* segundos, int* minutos, int* horas)
{
    (*segundos)++; 

    if (*segundos == MINNUTO_HORA)
    {
        (*minutos)++; 
        (*segundos) = 0; 
    }

    if (*minutos == MINNUTO_HORA)
    {
        (*horas)++; 
        (*minutos) = 0; 
    }
}

bool verifica_tabuleiroCompleto()
{
    for (int i = 0; i < TAM_MAX_TAB; i++)
    {
        for (int j = 0; j < TAM_MAX_TAB; j++)
        {
            if (tabuleiro_quadr[i][j].temPeca)
            {
                return false; 
            }
        }
    }
    return true; 
}

void atualiza_bonus(int multilinha, int combo, int tabuleiroCompleto, int *bombasDisp, int *girarDisp, int *undoDisp, int pontuacaoTotal)
{
    *bombasDisp = (multilinha + combo) / MIN_BOMBA;
    *bombasDisp -= bombasUsadas; 

    *girarDisp = pontuacaoTotal / MIN_GIRAR; 
    *girarDisp -= girarUsados; 

    if (tabuleiroCompleto == TAM_MAX_TAB)
    {
        (*undoDisp)++; 
    }
}

#define xPONTUACOES                 130
#define yPONTUACOES                 150
#define yTIMER                      35
#define yDIST                       30
#define yDIST_BOMB                  40
#define xDIST                       10
#define xLINHAS                     125
#define yLINHAS                     40
#define xCOLUNAS                    40
#define yCOLUNAS                    40

void hud_desenha(int* linhasPontos, int* colunasPontos, int* pontuacaoTotal, int segundos, int minutos, int horas, int ExtrasTotais, int bombasDisp, int girarDisp, int undoDisp)
{
    if (gExibirJogo)
    {
        for (int i = 0; i < TAM_MAX_TAB; i++)
        {
            al_draw_textf(font, al_map_rgb_f(1, 1, 1), tabuleiro_quadr[0][i].cord.x + xCOLUNAS, tabuleiro_quadr[0][0].cord.y - yCOLUNAS, 0, "%d", colunasPontos[i]);
            al_draw_textf(font, al_map_rgb_f(1, 1, 1), tabuleiro_quadr[0][4].cord.x + xLINHAS, tabuleiro_quadr[i][4].cord.y + 40, 0, "%d", linhasPontos[i]);
        }

        al_draw_textf(font, al_map_rgb_f(1, 1, 1), xPONTUACOES, yPONTUACOES, 0, "%04d", *pontuacaoTotal);
        al_draw_textf(font, al_map_rgb_f(1, 1, 1), xPONTUACOES, yPONTUACOES + yPONTUACOES, 0, "%04d", ExtrasTotais);

        al_draw_textf(font, al_map_rgb_f(0, 0, 0), 870, yTIMER, 0, "%02d", horas);
        al_draw_textf(font, al_map_rgb_f(0, 0, 0), 905, yTIMER, 0, "%02d", minutos);
        al_draw_textf(font, al_map_rgb_f(0, 0, 0), 940, yTIMER, 0, "%02d", segundos);

        al_draw_textf(font, al_map_rgb_f(0, 0, 0), xVOLTAR - xDIST, yVOLTAR_1 + yDIST, 0, "%02d", girarDisp);
        al_draw_textf(font, al_map_rgb_f(0, 0, 0), xVOLTAR - xDIST, yVOLTAR_2 + yDIST, 0, "%02d", girarDisp);
        al_draw_textf(font, al_map_rgb_f(0, 0, 0), xVOLTAR - xDIST, yVOLTAR_3 + yDIST, 0, "%02d", girarDisp);

        al_draw_textf(font, al_map_rgb_f(0, 0, 0), xBOTOES_JOGO - yDIST_BOMB, yBOMBA - yDIST_BOMB, 0, "%02d", bombasDisp);
    }
}

pecasBase()
{
    baseDados[0].temPeca = true; 
    baseDados[1].temPeca = true;
    baseDados[2].temPeca = true;
}

bool teste_encaixe(int i)
{
    for (int j = 0; j < TAM_MAX_TAB; j++)
    {
        printf("j = %d\n", j);
        for (int k = 0; k < TAM_MAX_TAB; k++)
        {
            printf("k = %d\n", k);
            if (!tabuleiro_quadr[j][k].temPeca)
            {
                switch (pecas[i].tipo)
                {
                case INDIVIDUAL:

                    return true;

                case DUPLA_LATERAL:
                    if (!tabuleiro_quadr[j + 1][k].temPeca)
                    {
                        return true;
                    }

                    break;

                case DUPLA_SUPERIOR:
                    if (!tabuleiro_quadr[j][k + 1].temPeca)
                    {
                        return true;
                    }

                    break;

                case TRIO_INFERIOR_ESQUERDO:
                    if (!tabuleiro_quadr[j][k + 1].temPeca)
                    {
                        if (!tabuleiro_quadr[j + 1][k + 1].temPeca)
                        {
                            return true;
                        }
                    }
                    break;

                case TRIO_INFERIOR_DIREITO:
                    if (!tabuleiro_quadr[j][k + 1].temPeca)
                    {
                        if (!tabuleiro_quadr[j + 1][k].temPeca)
                        {
                            return true;
                        }
                    }
                    break;

                case TRIO_SUPERIOR_ESQUERDO:
                    if (!tabuleiro_quadr[j][k + 1].temPeca)
                    {
                        if (!tabuleiro_quadr[j + 1][k].temPeca)
                        {
                            if (!tabuleiro_quadr[j + 1][k + 1].temPeca)
                            {
                                return true;
                            }
                        }
                    }
                    break;

                case TRIO_SUPERIOR_DIREITO:
                    if (!tabuleiro_quadr[j + 1][k].temPeca)
                    {
                        if (!tabuleiro_quadr[j + 1][k + 1].temPeca)
                        {
                            return true;
                        }
                    }
                    break;
                }
            }
        }
    }
    return false; 
}

void gameOver_teste(bool *gameOver)
{
    bool temp = true; 
    int cont = 0; 

    for (int i = 0; i < MAX_N_PECAS; i++)
    {
        if (pecas[i].base)
        {
            temp = teste_encaixe(i, &gameOver);
            printf("\n%d\n", temp); 

            if (temp)
            {
                return; 
            }

            else 
            {
                *gameOver = true;
            }
        }
    }
}

void removePeca_tabuleiro(int i, int* linhasPontos, int* colunasPontos)
{
    int coluna = 0, linha = 0;

    for (int l = 0; l < DADOS_DIMENSAO; l++)
    {
        for (int m = 0; m < DADOS_DIMENSAO; m++)
        {
            if (pecas[i].dados[l][m].usado && pecas[i].dados[l][m].linha != -1 && pecas[i].dados[l][m].coluna != -1)
            {
                linha = pecas[i].dados[l][m].linha;
                coluna = pecas[i].dados[l][m].coluna;

                linhasPontos[pecas[i].dados[l][m].linha] -= pecas[i].dados[l][m].valor;
                colunasPontos[pecas[i].dados[l][m].coluna] -= pecas[i].dados[l][m].valor;

                tabuleiro_quadr[linha][coluna].temPeca = false;

                pecas[i].dados[l][m].linha = -1;
                pecas[i].dados[l][m].coluna = -1;
            }
        }
    }
}

int acao_undo(int* linhasPontos, int* colunasPontos)
{
    int i = 0, j = 0;

    for (i = 0; i < MAX_BASE_DADOS; i++)
    {
        if (!baseDados[i].temPeca)
        {
            for (j = MAX_N_PECAS - 1; j > 0; j--)
            {
                if (pecas[j].desenhar && pecas[j].tabuleiro)
                {
                    removePeca_tabuleiro(j, linhasPontos, colunasPontos);

                    pecas[j].base = true;
                    pecas[j].tabuleiro = false;
                    baseDados[i].temPeca = true;
                    contPecaBase++;

                    pecas[j].cord.x = baseDados[i].cord.x;
                    pecas[j].cord.y = baseDados[i].cord.y;

                    return;
                }

            }

        }
    }
}

int main(void)
{
    must_init(al_init(), "allegro");
    must_init(al_install_mouse(), "mouse");
    srand(time(NULL));

    must_init(al_init_font_addon(), "fonte");
    must_init(al_init_ttf_addon(), "ttf");

    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    must_init(timer, "timer"); 

    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    must_init(queue, "queue");

    display_init();
    audio_init();

    must_init(al_init_primitives_addon(), "primitives");

    must_init(al_install_audio(), "audio");
    must_init(al_init_acodec_addon(), "audio codecs");
    must_init(al_reserve_samples(16), "reserve samples");

    al_register_event_source(queue, al_get_display_event_source(display));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    al_register_event_source(queue, al_get_mouse_event_source());

    al_init_image_addon();
    imagens_init();

    int pecasColocadas = 3;

    tabuleiroCoordenadas_init();
    baseDados_init();
    dados_init();

    bool done = false;
    bool redraw = true;
    bool verificaTabLimpo = false;
    bool gameOver = false; 

    int pontuacaoTotal = 0, ExtrasTotais = 0; 
    int multilinha = 0, combo = 0, tabuleiroCompleto = 0; 
    int bombasDisp = 0, girarDisp = 0, undoDisp = 0; 

    int segundos = 0, minutos = 0, horas = 0, frames = 0; 

    int linhasPontos[TAM_MAX_TAB] = { 0 }; 
    int colunasPontos[TAM_MAX_TAB] = { 0 }; 

    hud_init();

    ALLEGRO_EVENT event;

    al_start_timer(timer);

    while (1)
    {
        al_wait_for_event(queue, &event);

        switch (event.type)
        {
        case ALLEGRO_EVENT_TIMER:
            frames++; 
            gameOver_teste(&gameOver); 
            excessos_pontos(linhasPontos, colunasPontos, &pontuacaoTotal, &multilinha, &combo);
            atualiza_bonus(multilinha, combo, tabuleiroCompleto, &bombasDisp, &girarDisp, &undoDisp, pontuacaoTotal);


            if (verifica_tabuleiroCompleto() && verificaTabLimpo)
            {
                pontuacaoTotal += BONUS_COMBO;
                tabuleiroCompleto++; 
                verificaTabLimpo = false; 
                al_play_sample(conquista, 0.5, 0.0, 1.0, ALLEGRO_PLAYMODE_ONCE, NULL); 
            }

            if (contPecaBase == 0)
            {
                montaBanca();
                pecasBase(); 
                contPecaBase = MAX_BASE_DADOS; 
            }

            if (frames == FRAMES_SEGUNDO )
            {
                tempo_jogo(&segundos, &minutos, &horas);
                frames = 0; 
            }

            ExtrasTotais = tabuleiroCompleto + combo + multilinha; 

            if (gameOver && bombasDisp == 0 && girarDisp == 0 && undoDisp == 0)
            {
                al_rest(5); 
                done = true; 
            }

            redraw = true;
            break;

        case ALLEGRO_EVENT_MOUSE_AXES:
            x = event.mouse.x;
            y = event.mouse.y;

            if (arrastarPecas)
            {
                for (int i = 0; i < MAX_N_PECAS; i++)
                {
                    if (pecas[i].movimento)
                    {
                        pecas[i].cord.x = x - 50;
                        pecas[i].cord.y = y - 50;

                        redraw = true; 
                        segundoClique = 1; 
                    }
                }
            }

            break;

        case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
            botoes_telas(x, y, &done); 
            botoes_dados(x, y); 
            botoes_jogo(x, y, linhasPontos, colunasPontos, &bombasDisp, &girarDisp, &undoDisp);

            if (segundoClique && arrastarPecas)
            {
                testa_colissoes(linhasPontos, colunasPontos, &verificaTabLimpo);
                segundoClique = 0; 

            }

            redraw = true;
            break;

        case ALLEGRO_EVENT_DISPLAY_CLOSE:
            done = true;
            break;
        }

        if (done)
            break;

        if (redraw && al_is_event_queue_empty(queue))
        {
            desenhaTela(imagem_ajuda, imagem_jogo, imagem_telaMenu, imagem_pause, imagem_ranking);
            desenha_pecas();
            hud_desenha(linhasPontos, colunasPontos, &pontuacaoTotal, segundos, minutos, horas, ExtrasTotais, bombasDisp, girarDisp, undoDisp);

            al_flip_display(); 
            redraw = false;
        }
    }

    audio_deinit();
    imagens_deinit();
    hud_deinit(); 

    al_destroy_timer(timer);
    al_destroy_event_queue(queue);

    return 0;
} 