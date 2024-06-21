#include <stdio.h>
#include <stdlib.h>  
#include <windows.h> // Para fun??o SetConsoleCursorPosition()
#include <conio.h>   // Para fun??o getch() e kbhit()
#include <time.h>    // Para fun??o rand()

//Cordenadas onde a cobra nasce
#define cordenadax 58 
#define cordenaday 12

//Cores utilizadas
#define Vermelho      "\x1b[31m" 
#define CinzaEscuro  "\e[1;30m"
#define Verde "\e[0;32m"
#define Default   "\x1b[0m"
#define Branco "\033[1;37m"

// Vari?veis Globais(podem ser acessadas e alteradas em qualquer parte do c?digo)
int tamanhocobra[260][2]; // Linhas mostram qual o peda?o da cobra e colunas a cordenada x e y
int pontos = 1, cordx = 0, cordy = 0; // Variaveis que vao controlar o local onde a cabeca da cobra esta
int comida[2]; //Cordenadas da comida gerada
int velocidade = 200; //Quanto maior, mais devagar(tempo entre cada printf da cobra)

// Criando funcoes

void cursor(int x, int y) {
    // Funcao do windows para acessar o buffer da tela do prompt de comando e verificar onde o cursor esta
    SetConsoleCursorPosition(
            GetStdHandle(STD_OUTPUT_HANDLE),
            // Passa a nova posicao do cursor
            (COORD){x, y});
}

// Desenha a cobra
void desenha() {
    // De acordo o numero de ponto o tamanho da cobra cresce
    for (int i = 0; i < pontos; i++) {
        // chama a funcao cursor passando a cordenada, x recebe o valor 0 e y o valor 1 da matriz tamanhocobra
        //Os valores 56 e 10 servem para que a cobrinha inicie dentro do retangulo
        cursor(tamanhocobra[i][0] + cordenadax, tamanhocobra[i][1] + cordenaday);
        // O desenho e feito a partir de print da tecla 219 que e um retangulo cobrindo o a cordenada toda
        printf(Verde "%c", 219);
    }
}

// Conforme a cobra cresce e necessario passar a posicao do primeiro pedaco para os proximos, fazendo com que eles a 'sigam'
void atualizaposicao() {
    // chama a funcao cursor passando a cordenada, x que o valor 0 e y o valor 1 da matriz tamanhocobra
    cursor(tamanhocobra[pontos][0] + cordenadax, tamanhocobra[pontos][1] + cordenaday);
    // Conforme a cobra anda e necessario apagar o desenho onde ela nao existe mais
    // O que e feito com um printf vazio no local onde ela ja passou
    printf(" ");
    for (int i = pontos; i >= 0; i--) {
        //
        tamanhocobra[i + 1][0] = tamanhocobra[i][0];  
        tamanhocobra[i + 1][1] = tamanhocobra[i][1];
    }
}

// Gera um valor aleatorio de cordenadas dentro do retangulo que ira receber a "comida"
void desenhacomida() {
    srand(time(NULL));
    comida[0] = (rand() % 28) + 46;
    comida[1] = (rand() % 8) + 8;
	//Caso seja gerada logo na cabeça da cobra
	if(comida[0] == 58 && comida[1] == 12){
		comida[0] = 60;
	}
    cursor(comida[0], comida[1]);
    printf(Vermelho "*");

}

// Verifica se a cobrinha bateu no proprio corpo
int Verifica() {
    int i, bateu = 0;
    for (i = 1; i < pontos; i++) {
        //Verifica se a cordenada da "cabeca da cobra" (cordx e cordy) e igual a cordenada de alguma das outras partes(matriz tamanhocobra)
        if ((tamanhocobra[i][0] == cordx) && (tamanhocobra[i][1] == cordy)) {
            bateu = 1;
        }
    }
    return bateu;
}

void mostrapontos(int pontos) {
    cursor(85, 12);
    printf(Branco "Pontos: %d", pontos);
}

//Verifica se o jogador comeu uma comida
void comeucomida(int cordx, int cordy){
	if ((cordx == comida[0] - cordenadax) && (cordy == comida[1] - cordenaday)) {
            pontos++;
            //Mostrar pontuacao para o jogador
            mostrapontos(pontos);
            //Gera uma nova comida
            desenhacomida();
            if (velocidade > 60) {
                velocidade = velocidade - 10;
            }
        }
}


int main() {
    system("color F");
    
	int i, perdeu = 0;
    int direcao, temp;

    cursor(100, 27);
    printf("By Andre Carvalho");

    //Desenha o titulo e faz piscar
    for (i = 0; i < 3; i++) {
        //Printa vazio e depois o titulo dando a impressao de piscar
        cursor(49, 2);
        printf("                         "); 
        Sleep(500);
        cursor(49, 2);
        printf("|||||| SNAKE GAME ||||||");
        Sleep(500);
    }

    //Desenha o retangulo que define as paredes dos jogo
    //Parede de cima
    for (i = 45; i < 75; i++) {
        cursor(i, 7);
        printf(CinzaEscuro "%c", 219);
        Sleep(05);
    }


    //Parede da direita
    for (i = 7; i < 17; i++) {
        cursor(75, i);
        printf("%c", 219);
        Sleep(05);
    }

    //Parede de baixo
    for (i = 75; i > 45; i--) {
        cursor(i, 17);
        printf("%c", 219);
        Sleep(05);
    }

    //Parede da esquerda
    for (i = 17; i > 7; i--) {
        cursor(45, i);
        printf("%c", 219);
        Sleep(05);
    }
    //Paredes feitas

    //tutorial
    cursor(2, 11);
    printf(Branco "Bem vindo ao jogo da cobrinha! Para se\n");
    cursor(2, 12);
    printf("mover use W,A,S,D. Tente antingir o\n");
    cursor(2, 13);
    printf("maximo de pontos sem bater nas\n");
    cursor(2, 14);
    printf("paredes ou em seu proprio corpo");
    //fim do tutorial

    //Pede qualquer tecla para iniciar
    cursor(38, 5);
    printf("Pressione qualquer tecla para iniciar o jogo!");
    getch();
    cursor(37, 5);
    printf("                                              ");
    //Gerar comida
    desenha();
    desenhacomida();
    //Passa a direcao inicial que a cobra vai andar
    direcao = 'd';

    mostrapontos(pontos);

    //Enquanto o jogador nao perder o programa continua a rodar
    while (perdeu == 0) {

        //Matriz tamanhocobra recebe o novo valor da cordenada da cabeca
        tamanhocobra[0][0] = cordx;
        tamanhocobra[0][1] = cordy;

        //Funcao kbhit verifica quando uma tecla e pressionada
        if (kbhit()) {
            //Funcao getch recebe o a tecla pressionada sem mostrar na tela
            temp = getch();

            if ((temp == 77) || (temp == 'd') || (temp == 'D')) {
                temp = 'd';
            } else if ((temp == 'a') || (temp == 'A')) {
                temp = 'a';
            } else if ((temp == 'w') || (temp == 'W')) {
                temp = 'w';
            } else if ((temp == 's') || (temp == 'S')) {
                temp = 's';
            }

            //Verifica se a tecla pressionada e valida
            if ((temp == 'd') || (temp == 'a') || (temp == 'w') || (temp == 's')) {
                //verifica se para player esta tentando andar para o lado contrario	
                if (
                        ((direcao == 'd') && (temp != 'a')) ||
                        ((direcao == 'a') && (temp != 'd')) ||
                        ((direcao == 'w') && (temp != 's')) ||
                        ((direcao == 's') && (temp != 'w'))){
                    direcao = temp;
                }
            }
        }

        //Caso o jogador aperta alguma das teclas a seguir a cobrinha ira 
        //Para a direita, caso sua cordenada seja igual a da parede o loop
        //E encerrado e o jogador perde

        if (direcao == 'd') {
            cordx++;
        }
        if (direcao == 'a') {
            cordx--;
        }
        if (direcao == 'w') {
            cordy--;
            Sleep(15);
        }
        if (direcao == 's') {
            cordy++;
			Sleep(15);
        }
        
		if(cordx == 18 || cordx == -14 || cordy == 6 ||cordy == -6){
			break;
		}
		
        comeucomida(cordx,cordy);

        perdeu = Verifica();
        atualizaposicao();
        desenha();
        Sleep(velocidade);
    }
    //Mostra mensagem para o usuario
    
    if (perdeu == 1){
        cursor(35,20);
		printf(Branco "Voce bateu no proprio rabo! Fez o total de %d pontos", pontos);
	}
    else{
    	cursor(38, 20);
		printf(Branco"Voce bateu na parede! Fez o total de %d pontos" Default, pontos);
	}
	
    cursor(0, 25);
}
