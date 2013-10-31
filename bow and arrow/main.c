#include <stdio.h>
#include <conio.h>
#include <Windows.h>
#include <string.h>

void gotoxy (int x, int y); // função para posicionar o cursor na tela, na posição desejada.
int menu (void); // função para inicializar o menu principal do jogo.
void newgame (void); // função para iniciar um novo jogo.
void level1 (void); // função para iniciar a primeira fase do jogo.
void print_borders (void); // função para imprimir as bordas do mapa atual.

// funções de movimento.
void movearcher_up (void);
void movearcher_down (void);
void movearcher_right (void);
void movearcher_left (void);

// variáveis globais.
int Garcher_x, Garcher_y;

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
    int score, arrows, balloons=15, cont1, cont2, archer_x, archer_y;
    char map[24][80], archer[4][8], arrow[] = "-->", balloon[2][2], key;
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

    system("cls");

    print_borders();

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
        case 72: // seta para cima.
            movearcher_up();
            break;
        case 80: // seta para baixo.
            movearcher_down();
            break;
        case 77: // seta para a direita.
            movearcher_right();
            break;
        case 75: // seta para a esquerda.
            movearcher_left();
            break;
        }
        key = getch();
        printf("%i", key);
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
        system("cls");
        print_borders();
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

}
void movearcher_right (void){

}
void movearcher_left (void) {

}
