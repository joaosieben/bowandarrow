#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Bibliotecas para Windows (comentar caso o sistema seja Linux).
#include <conio.h>
#include <Windows.h>

/* ADAPTAÇÃO PARA LINUX
=====================================================
#include <termios.h> // função 'getch' para linux

// Adaptação da função 'getch' para linux.
static struct termios old, new;

// Initialize new terminal i/o settings
void initTermios(int echo)
{
  tcgetattr(0, &old); // grab old terminal i/o settings
  new = old; // make new settings same as old settings
  new.c_lflag &= ~ICANON; // disable buffered i/o
  new.c_lflag &= echo ? ECHO : ~ECHO; // set echo mode
  tcsetattr(0, TCSANOW, &new); // use these new terminal i/o settings now
}

// Restore old terminal i/o settings
void resetTermios(void)
{
  tcsetattr(0, TCSANOW, &old);
}

// Read 1 character - echo defines echo mode
char getch_(int echo)
{
  char ch;
  initTermios(echo);
  ch = getchar();
  resetTermios();
  return ch;
}

// Read 1 character without echo
char getch(void)
{
  return getch_(0);
}

// Read 1 character with echo
char getche(void)
{
  return getch_(1);
}
============================================ */

void gotoxy (int x, int y); // função para posicionar o cursor na tela, na posição desejada.
int menu (void); // função para inicializar o menu principal do jogo.
void newgame (void); // função para iniciar um novo jogo.
void level1 (void); // função para iniciar a primeira fase do jogo.
void print_borders (void); // função para imprimir as bordas do mapa atual.

// funções de movimento.
void movearcher_up (void);
void movearcher_down (void);

void shoot (void); // função de disparo de flecha.

// variáveis globais.
int Garcher_x, Garcher_y, arrows=15;

int main () {
    switch(menu()) {
    case 1:
        newgame();
    }
}

void gotoxy (int x, int y) {
	COORD coord = {0, 0};
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
//    printf("%c[%d;%df",0x1B,y,x); // Função gotoxy para Linux.
}

int menu (void) {
	char map[14][80];
	int opt;
	int cont1, cont2;
	for (cont1=0; cont1<14; cont1++) { // laço que inicializa o array do mapa de caracteres, preenchendo-o com espaços em branco.
        for (cont2=0; cont2<80; cont2++) {
            map[cont1][cont2]=' ';
        }
	}
    for (cont1=1; cont1<79; cont1++) { // laço para preencher o array do mapa de caracteres com os hífens que constituem o mapa.
        map[0][cont1] = '-';
        map[13][cont1] = '-';
        map[4][cont1] = '-';
    }
    for (cont1=1; cont1<13; cont1++) { // laço para preencher o array do mapa de caracteres com os pipes que constituem o mapa.
        map[cont1][0] = '|';
        map[cont1][79] = '|';
        //map[cont1][79]='\0';
    }
    for (cont1=0; cont1<14; cont1++) {
        for (cont2=0; cont2<80; cont2++) {
            printf("%c", map[cont1][cont2]);
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
    int score=0, balloons=15, cont1, cont2, archer_x, archer_y;
    char map[24][80], archer[4][8], arrow[] = "-->", balloon[3][3], key;
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
    printf("HIGH SCORE: 9999");
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
    strcpy(balloon[1], "\ /");
    strcpy(balloon[2], " $ ");


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
    key = getch();
    do {
        switch (key) {
        case 119: // tecla 'w', que move o arqueiro para cima.
            movearcher_up();
            break;
        case 115: // tecla 's', que move o arqueiro para baixo.
            movearcher_down();
            break;
        case 32: // barra de espaço, que aciona a função de disparo da flecha.
            shoot();
            break;
        }
        key = getch();
        //printf("%i", key);
    } while (key != 27);
}

void print_borders (void) {
    char map[24][80];
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
    int arrow_y, arrow_x=11;
    char key;
    arrow_y = Garcher_y+1;
    arrows--;
    while (arrow_x < 77 && arrows >= 0) {
        gotoxy(arrow_x, arrow_y);
        printf("-->");
        gotoxy(arrow_x-1, arrow_y);
        printf(" ");
        arrow_x++;
        if (arrow_x == 77) {
            gotoxy(arrow_x-1, arrow_y);
            printf("   ");
        }
        if (kbhit()) {
            key = getch();
            switch (key) {
                 case 119: // tecla 'w', que move o arqueiro para cima.
                    movearcher_up();
                    break;
                case 115: // tecla 's', que move o arqueiro para baixo.
                    movearcher_down();
                    break;
            }
        }
        if (arrows < 10) {
            gotoxy(77, 2);
            printf("  ");
        }
        gotoxy(77, 2);
        printf("%i", arrows);
        Sleep(10);
    }
}
