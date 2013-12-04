#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <Windows.h>

void gotoxy (int x, int y); // função para posicionar o cursor na tela, na posição desejada.
void start (void); // função que controla a tela de inicialização do jogo.
int menu (void); // função para inicializar o menu principal do jogo.
void newgame (void); // função para iniciar um novo jogo.
void level1 (void); // função para iniciar a primeira fase do jogo.
void print_borders (void); // função para imprimir as bordas do mapa atual.
int verify_score (void); // função que verifica se o score do jogador está entre os 5 primeiros.
void show_scores (void); // função que mostra na tela os 5 maiores placares do jogo.
void add_score (void); // função que adiciona o score do jogador ao arquivo highscores.bin.
int get_higher_score (void); // função que retorna o score mais alto do arquivo highscores.bin.

// funções de movimento.
void movearcher_up (void);
void movearcher_down (void);

void shoot (void); // função de disparo de flecha.
void destroy_balloon (int arrow_x, int arrow_y); // função que trata a colisão entre a flecha e o balão.

typedef struct tipo_jogador {
    char nome[30];
    int score;
} TIPO_JOGADOR;

// variáveis globais.
int Garcher_x, Garcher_y, score, arrows, balloons, shoot_flag, endgame;
char map[24][80], firstline[80];

int main () {
    start();
}

void gotoxy (int x, int y) {
	COORD coord = {0, 0};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void start (void) {
    switch(menu()) {
    case 1:
        newgame();
        break;
    case 2:
        show_scores();
        break;
    }
}

int menu (void) {
	char mapmenu[14][80];
	int opt;
	int cont1, cont2;
	system("cls");
	for (cont1=0; cont1<14; cont1++) { // laço que inicializa o array do mapa de caracteres, preenchendo-o com espaços em branco.
        for (cont2=0; cont2<80; cont2++) {
            mapmenu[cont1][cont2]=' ';
        }
	}
    for (cont1=1; cont1<79; cont1++) { // laço para preencher o array do mapa de caracteres com os hífens que constituem o mapa.
        mapmenu[0][cont1] = '-';
        mapmenu[13][cont1] = '-';
        mapmenu[4][cont1] = '-';
    }
    for (cont1=1; cont1<13; cont1++) { // laço para preencher o array do mapa de caracteres com os pipes que constituem o mapa.
        mapmenu[cont1][0] = '|';
        mapmenu[cont1][79] = '|';
    }
    for (cont1=0; cont1<14; cont1++) {
        for (cont2=0; cont2<80; cont2++) {
            printf("%c", mapmenu[cont1][cont2]);
        }
    }
    gotoxy(31, 2);
    printf("BOW AND ARROW");

    gotoxy(31, 6);
    printf("1. NOVO JOGO");
    gotoxy(31, 7);
    printf("2. MAIORES PLACARES");
    gotoxy(31, 8);
    printf("3. SAIR");
    do {
        gotoxy(28, 10);
        printf("DIGITE A OPCAO DESEJADA: ");
        scanf("%i", &opt);
        if (opt < 1 || opt > 3) {
            gotoxy(28, 11);
            printf("Opcao invalida!");
            gotoxy(53, 10);
            printf(" ");
        }
    } while (opt < 1 || opt > 3);
    return opt;
}

void newgame (void) {
    system("cls");
    level1();
}

void level1 (void) {
    int cont1, cont2, cont3, archer_x, archer_y, x, y, arrow_x, arrow_y, flag_final_balao = 0;
    char archer[4][8], arrow[] = "-->", balloon[3][3], key;
    score = 0;
    arrows = 15;
    balloons = 15;
    shoot_flag = 0;
    endgame = 0;
    fflush(stdin);
    // informações do nível atual.
    print_borders();
    gotoxy(29, 0);
    printf(">  BOW AND ARROW  <");
    gotoxy(35, 1);
    printf("LEVEL 1");
    gotoxy(34, 2);
    printf("BALLOONS");
    gotoxy(2, 1);
    printf("SCORE: %i", score);
    gotoxy(2, 2);
    printf("HIGH SCORE: %i", get_higher_score());
    gotoxy(68, 2);
    printf("Flechas: %i", arrows);
    // construindo o arqueiro.
    for (cont1=0; cont1<3; cont1++) {
        for (cont2=0; cont2<8; cont2++) {
            archer[cont1][cont2] = ' ';
        }
    }
    strcpy(archer[0], "~O |\\   ");
    strcpy(archer[1], " |<| >->");
    strcpy(archer[2], " | |/   ");
    strcpy(archer[3], "/ \\     ");

    // construindo o balão.
    strcpy(balloon[0], "/~\\");
    strcpy(balloon[1], "\\ /");
    strcpy(balloon[2], " $ ");

    // escrevendo os balões na matriz principal.
    x=20;
    y=15;
    for (cont1=1; cont1<=15; cont1++) {
        for (cont2=0; cont2<3; cont2++) {
            for (cont3=0; cont3<3; cont3++) {
                map[x][y]=balloon[cont2][cont3];
                y++;
            }
            x++;
            y-=3;
        }
        y+=4;
        x-=3;
    }

    // escrevendo o arqueiro na tela.
    Garcher_x = 2;
    Garcher_y = 10;
    archer_x = Garcher_x;
    archer_y = Garcher_y;
    for (cont1=0; cont1<4; cont1++) {
        gotoxy(archer_x, archer_y);
        for (cont2=0; cont2<8; cont2++) {
            printf("%c", archer[cont1][cont2]);
        }
        archer_y++;
    }

    // escrevendo o mapa da fase atual.
    x = 10;
    y = 4;
    gotoxy(x, y);
    for (cont1=4; cont1<23; cont1++) {
        for (cont2=10; cont2<78; cont2++) {
            printf("%c", map[cont1][cont2]);
        }
        y++;
        gotoxy(x, y);
    }

    // salvando a primeira linha jogável da matriz (necessário para o efeito de movimento dos balões)
    for (cont1 = 10; cont1 < 78; cont1++)
        firstline[cont1] = map[4][cont1];

    do {
        gotoxy(9, 1);
        printf("%i", score);
        if (kbhit()) {
            key = getch();
            switch (key) {
            case 119: // tecla 'w', que move o arqueiro para cima.
                movearcher_up();
                movearcher_up();
                break;
            case 115: // tecla 's', que move o arqueiro para baixo.
                movearcher_down();
                movearcher_down();
                break;
            case 32: // barra de espaço, que aciona a função de disparo da flecha.
                shoot();
                break;
            }
        }

       for (cont1 = 4; cont1 < 23; cont1++) {
            for (cont2 = 10; cont2 < 78; cont2++) {
                if (cont1 == 22)
                    map[cont1][cont2] = firstline[cont2];
                else
                    map[cont1][cont2] = map[cont1+1][cont2];
            }
       }

        // salvando a primeira linha da matriz principal no vetor 'firstline'.
       for (cont1 = 10; cont1 < 78; cont1++)
            firstline[cont1] = map[4][cont1];

        x = 10;
        y = 4;
        gotoxy(x, y);
        for (cont1=4; cont1<23; cont1++) {
            for (cont2=10; cont2<78; cont2++) {
                if (map[cont1][cont2] == '>') {
                    arrow_x = cont2;
                    arrow_y = cont1;
                }
                printf("%c", map[cont1][cont2]);
            }
            y++;
            gotoxy(x, y);
        }
        if (shoot_flag) {
            if (map[arrow_y+1][arrow_x+4] == '/' || map[arrow_y+1][arrow_x+4] == '\\') {
                destroy_balloon(arrow_x+4, arrow_y);
            }
            for (cont1 = 1; cont1 <= 4; cont1++) {
                if (map[arrow_y+1][arrow_x+cont1] == '$')
                    flag_final_balao = cont1;
            }
            map[arrow_y][arrow_x] = ' ';
            map[arrow_y][arrow_x-1] = ' ';
            map[arrow_y][arrow_x-2] = ' ';
            map[arrow_y+1][arrow_x+2] = '-';
            map[arrow_y+1][arrow_x+3] = '-';
            map[arrow_y+1][arrow_x+4] = '>';
            if (flag_final_balao) {
                map[arrow_y+1][arrow_x+flag_final_balao] = '$';

                flag_final_balao = 0;
                map[arrow_y+1][arrow_x+2] = ' ';
                map[arrow_y+1][arrow_x+4] = '-';
                map[arrow_y+1][arrow_x+5] = '-';
                map[arrow_y+1][arrow_x+6] = '>';
            }
            if (arrow_x+1 > 75) {
                map[arrow_y][arrow_x] = ' ';
                map[arrow_y][arrow_x-1] = ' ';
                map[arrow_y][arrow_x-2] = ' ';
                shoot_flag = 0;

                for (cont1 = 4; cont1 < 23; cont1++) {
                    if (map[cont1][77] == '-')
                        map[cont1][77] = ' ';
                }
                if (arrows == 0)
                    endgame = 1;
            }
        }
        Sleep(100);
    } while (!endgame);
    if (arrows > 0) {
        for (cont1 = 0; cont1 < arrows; cont1++)
            score+=50;
    }
    system("cls");
    gotoxy(25, 7);
    printf("FIM DE JOGO!");
    gotoxy(25, 8);
    printf("Seu score foi de %i pontos.", score);
    gotoxy(25, 10);
    printf("Pressione qualquer tecla para continuar.");
    getch();
    if (verify_score())
        add_score();
    start();
}

void print_borders (void) {
    int cont1, cont2;
    for (cont1=0; cont1<24; cont1++) { // laço que inicializa o array do mapa de caracteres, preenchendo-o com espaços em branco.
        for (cont2=0; cont2<80; cont2++) {
            map[cont1][cont2]=' ';
        }
	}
    for (cont1=1; cont1<79; cont1++) { // laço para preencher o array do mapa de caracteres com os hífens que constituem o mapa.
        map[0][cont1] = '-';
        map[23][cont1] = '-';
        map[3][cont1] = '-';
    }
    for (cont1=1; cont1<23; cont1++) { // laço para preencher o array do mapa de caracteres com os pipes que constituem o mapa.
        map[cont1][0] = '|';
        map[cont1][79] = '|';
    }
    for (cont1=0; cont1<24; cont1++) {
        for (cont2=0; cont2<80; cont2++) {
            printf("%c", map[cont1][cont2]);
        }
    }
}

void movearcher_up (void) {
    int cont1, cont2, archer_x, archer_y;
    char archer[4][8];
    if (Garcher_y-1 > 3) {
        strcpy(archer[0], "~O |\\   ");
        strcpy(archer[1], " |<| >->");
        strcpy(archer[2], " | |/   ");
        strcpy(archer[3], "/ \\     ");
        for (cont1=0; cont1<8; cont1++) {
            gotoxy((Garcher_x+cont1), (Garcher_y+3));
            printf(" ");
        }
        Garcher_y--;
        archer_x = Garcher_x;
        archer_y = Garcher_y;
        for (cont1=0; cont1<4; cont1++) {
            gotoxy(archer_x, archer_y);
            for (cont2=0; cont2<8; cont2++) {
                printf("%c", archer[cont1][cont2]);
            }
            archer_y++;
        }
    }
}

void movearcher_down (void) {
    int cont1, cont2, archer_x, archer_y;
    char archer[4][8];
    if (Garcher_y+1 < 20) {
        strcpy(archer[0], "~O |\\   ");
        strcpy(archer[1], " |<| >->");
        strcpy(archer[2], " | |/   ");
        strcpy(archer[3], "/ \\     ");
        for (cont1=0; cont1<8; cont1++) {
            gotoxy((Garcher_x+cont1), Garcher_y);
            printf(" ");
        }
        Garcher_y++;
        archer_x = Garcher_x;
        archer_y = Garcher_y;
        for (cont1=0; cont1<4; cont1++) {
            gotoxy(archer_x, archer_y);
            for (cont2=0; cont2<8; cont2++) {
                printf("%c", archer[cont1][cont2]);
            }
            archer_y++;
        }
    }
}

void shoot (void) {
    int arrow_y, arrow_x=11, cont1, cont2;
    char key;
    if (!shoot_flag && arrows > 0) {
        arrow_y = Garcher_y+2;
        arrows--;
        shoot_flag = 1;
        map[arrow_y][arrow_x] = '-';
        map[arrow_y][arrow_x+1] = '-';
        map[arrow_y][arrow_x+2] = '>';
        if (arrows < 10) {
            gotoxy(77, 2);
            printf("  ");
        }
        gotoxy(77, 2);
        printf("%i", arrows);
    }
}

void destroy_balloon (int arrow_x, int arrow_y) {
    int cont1, cont2;
    if (map[arrow_y][arrow_x] == '\\')
        arrow_y--;
    map[arrow_y+1][arrow_x-2] = ' ';
    map[arrow_y+1][arrow_x-1] = ' ';
    map[arrow_y+1][arrow_x] = ' ';
    map[arrow_y+2][arrow_x-2] = ' ';
    map[arrow_y+2][arrow_x-1] = ' ';
    map[arrow_y+2][arrow_x] = ' ';
    map[arrow_y+3][arrow_x-2] = ' ';
    map[arrow_y+3][arrow_x-1] = ' ';
    map[arrow_y+3][arrow_x] = ' ';
    if (arrow_y+3 > 22)
        firstline[arrow_x-1] = ' ';
    balloons--;
    score+=100;
    if (balloons == 0)
        endgame = 1;
}

void show_scores (void) {
    FILE *arq;
    TIPO_JOGADOR jogador;
    int x = 28, y = 4;
    if (!(arq = fopen("highscores.bin", "rb"))) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        system("cls");
        gotoxy(35, y);
        printf("HIGH SCORES");
        y+=2;
        gotoxy(x, y);
        printf("Nome\t\tScore");
        while (!feof(arq)) {
            if (fread(&jogador, sizeof(TIPO_JOGADOR), 1, arq) == 1) {
                y++;
                gotoxy(x, y);
                printf("%s\t\t%i\n", jogador.nome, jogador.score);
            }
        }
        fclose(arq);
        y+=3;
        gotoxy(21, y);
        printf("Pressione qualquer tecla para continuar.");
        getch();
        start();
    }
}

int verify_score (void) {
    FILE *arq;
    TIPO_JOGADOR jogador;
    if (!(arq = fopen("highscores.bin", "rb"))) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        while (!feof(arq)) {
            if (fread(&jogador, sizeof(TIPO_JOGADOR), 1, arq) == 1) {
                if (score > jogador.score) {
                    fclose(arq);
                    return 1;
                }
            }
            else {
                printf("Erro na leitura do arquivo.");
            }
        }
    }
    return 0;
}

void add_score (void) {
    FILE *arq;
    TIPO_JOGADOR jogador[5];
    int cont1, cont2, flag = 0;
    char nome[30];
    system("cls");
    fflush(stdin);
    gotoxy(21, 6);
    printf("Parabens! Sua pontuacao esta entre as 5 melhores.");
    gotoxy(21, 7);
    printf("Informe seu nome: ");
    gets(nome);
    if (!(arq = fopen("highscores.bin", "rb"))) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        if (fread(&jogador, sizeof(TIPO_JOGADOR), 5, arq) != 5) {
            printf("Erro na leitura do arquivo.");
        }
        for (cont1 = 0; cont1 < 5; cont1++) {
            if (score > jogador[cont1].score && flag == 0) {
                for (cont2 = 4; cont2 < cont1; cont2--)
                    jogador[cont2] = jogador[cont2-1];
                jogador[cont1].score = score;
                strcpy(jogador[cont1].nome, nome);
                flag = 1;
            }
        }
        fclose(arq);
    }

    if (!(arq = fopen("highscores.bin", "wb"))) {
        printf("Erro na abertura do arquivo.");
    }
    else {
        fflush(stdin);
        if (fwrite(&jogador, sizeof(TIPO_JOGADOR), 5, arq) != 5) {
            printf("Erro na gravacao dos dados.");
        }
        fclose(arq);
    }
}

int get_higher_score (void) {
    FILE *arq;
    TIPO_JOGADOR jogador;
    if (!(arq = fopen("highscores.bin", "rb"))) {
        printf("Erro na leitura do arquivo.");
    }
    else {
        if (fread(&jogador, sizeof(TIPO_JOGADOR), 1, arq) != 1)
            printf("Erro na leitura do arquivo.");
        fclose(arq);
    }
    return jogador.score;
}
