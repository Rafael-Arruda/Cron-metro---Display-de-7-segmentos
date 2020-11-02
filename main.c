#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

//Variaveis Globais
FILE* file;

int h1 = 0,h2 = 0,min1 =0,min2 = 0,seg1 = 0,seg2 = 0;
int horaAt, minAt, segAt;

void menu(){
    printf("=============================\n");
 	printf("---- DISPLAY 7 SEGMENTOS ----\n");
 	printf("=============================\n");
 	printf("1 - CRONÔMETRO PROGRESSIVO\n");
 	printf("2 - CRONÔMETRO REGRESSIVO\n");
 	printf("3 - FUNÇÃO RELÓGIO\n");
 	printf("4 - VISUALIZAR ÚLTIMO TEMPO REGISTRADO\n");
 	printf("5 - SAIR\n");
 	printf("SUA OPÇÃO: ");
}

void menu_relogio(){
    printf("\nDigite 'w' para voltar para o menu: \n");
}

void menu_cronometro(){
    printf("\n1 - Salvar a hora marcada no cronometro e continuar.\n");
    printf("2 - Zerar o cronometro.\n");
    printf("3 - Continuar a contagem.\n");
    printf("4 - Salvar e zerar o cronometro.\n");
    printf("5 - Retomar com os valores da última contagem\n");
    printf("6 - Voltar para o MENU PRINCIPAL.\n");
    printf("Sua opcao: ");
}

void menu_temporizador(){
    printf("\n1 - Retomar contagem\n");
    printf("2 - Inserir novos valores\n");
    printf("3 - Voltar para o MENU PRINCIPAL\n");
    printf("Sua opção: ");
}

void inicio_temporizador(){
    printf("Digite o inicio da contagem no formato (hh:mm:ss) -  ");
    scanf("%i:%i:%i", &horaAt, &minAt, &segAt);
    h1 = horaAt/10;
    h2 = horaAt%10;

    min1 = minAt/10;
    min2 = minAt%10;

    seg1 = segAt/10;
    seg2 = segAt%10;
}

void horarioSistema(){

  struct tm *data_hora_atual;
  time_t segundos;
  time(&segundos);
  data_hora_atual = localtime(&segundos);

  horaAt = data_hora_atual->tm_hour;
  minAt = data_hora_atual->tm_min;
  segAt = data_hora_atual->tm_sec;

  return;
}

void resetar_crescente(){
    h1 = 0;
    h2 = 0;
    min1 = 0;
    min2 = 0;
    seg1 = 0;
    seg2 = 0;
}

void resetar_decrescente(){
    h1 = 2;
    h2 = 3;
    min1 = 5;
    min2 = 9;
    seg1 = 6;
    seg2 = 0;
}

void desenha_inicio(int n){
    if(n==0 || n==2 || n==3 || n==5 || n==6 || n==7 || n==8 || n==9){
        printf(" _  ");
    }else{
        printf("    ");
    }
}

void desenha_meio(int n){
    if(n==0){
        printf("| | ");
    }else if(n==4 || n==8 || n==9){
        printf("|_| ");
    }else if(n==1 || n==7){
        printf("  | ");
    }else if(n==2 || n==3){
        printf(" _| ");
    }else if(n==5 || n==6){
        printf("|_  ");
    }
}

void desenha_fim(int n){
    if(n==0 || n==6 || n==8){
        printf("|_| ");
    }else if(n==1 || n==4 || n==7){
        printf("  | ");
    }else if(n==2){
        printf("|_  ");
    }else if(n==3 || n ==5 || n==9){
        printf(" _| ");
    }
}

void contagem_crescente(){
    if(seg2<10){
        seg2++;
        if(seg2 == 10){
            seg2 = 0;
            seg1++;
        }
    }if(seg1 == 6){
        seg1 = 0;
        min2++;
        if(min2 == 10){
            min2 = 0;
            min1++;
        }
    }if(min1==6){
        min1=0;
        h2++;
        printf("\a"); //A cada hora, um som do sistema é emitido.
        if(h2 == 10){
            h2=0;
            h1++;
        }
    }

    if(h1==2 && h2==4){
        resetar_crescente();
    }

}

void contagem_decrescente(){

    if(seg2>=0){
        seg2--;
        if(seg2 == -1){
            seg2 = 9;
            seg1--;
        }
    }if(seg1 == -1){
        seg1 = 5;
        min2--;
        if(min2 == -1){
            min2 = 9;
            min1--;
        }
    }if(min1==-1){
        min1=5;
        h2--;
        if(h2 == -1){
            h2=9;
            h1--;
        }
    }

}

void desenha_cronometro(){
        printf("\t");
        desenha_inicio(h1);
        desenha_inicio(h2);
        printf("    ");
        desenha_inicio(min1);
        desenha_inicio(min2);
        printf("    ");
        desenha_inicio(seg1);
        desenha_inicio(seg2);

        printf("\n");
        printf("\t");

        desenha_meio(h1);
        desenha_meio(h2);
        printf(" .  ");
        desenha_meio(min1);
        desenha_meio(min2);
        printf(" .  ");
        desenha_meio(seg1);
        desenha_meio(seg2);

        printf("\n");
        printf("\t");

        desenha_fim(h1);
        desenha_fim(h2);
        printf(" .  ");
        desenha_fim(min1);
        desenha_fim(min2);
        printf(" .  ");
        desenha_fim(seg1);
        desenha_fim(seg2);

        printf("\n");

        sleep(1);
}

int main(){
    setlocale(LC_ALL, "");

    int opc;
    int valor;  //Variavel para as funcoes menuCronometro e menuTemporizador

    do{
        menu();
        scanf("%i", &opc);
        system("cls");

        if(opc == 1){   //Opcao para contagem progessiva
            resetar_crescente();
            char tecla1;

            inicioP: //Referencia para retomar a contagem

            tecla1 = ' ';

            do{
                printf("\nDigite a tecla w para pausar: \n\n");
                desenha_cronometro();
                contagem_crescente();
                system("cls");

                if(kbhit()){  //Funcao para pegar ação do teclado
                    tecla1 = getch();
                }

            }while(tecla1 != 'w');

            desenha_cronometro();

            menu_cronometro();
            scanf("%i", &valor);

            if(valor == 1){     //Salvar hora marcada e continuar.
                file = fopen("Relogio.txt", "w");
                fprintf(file, "%i %i : %i %i : %i %i", h1, h2, min1, min2, seg1, seg2);
                fclose(file);
                system("cls");
                goto inicioP;  //Direciona a execução do programa para minha referencia.
            }else if(valor == 2){   //Zerar o cronometro.
                resetar_crescente();
                system("cls");
                goto inicioP;
            }else if(valor == 3){   //Continuar a contagem.
                system("cls");
                goto inicioP;
            }else if(valor == 4){   //Salvar e zerar o cronometro.
                file = fopen("Relogio.txt", "w");
                fprintf(file, "%i %i : %i %i : %i %i", h1, h2, min1, min2, seg1, seg2);
                fclose(file);
                resetar_crescente();
                system("cls");
                goto inicioP;
            }else if(valor == 5){   //Retomar com os valores salvos.
                file = fopen("Relogio.txt", "r");
                fscanf(file, "%i %i : %i %i : %i %i", &h1, &h2, &min1, &min2, &seg1, &seg2);
                fclose(file);
                system("cls");
                goto inicioP;
            }else if(valor == 6){   //Voltar para o menu principal.
                system("cls");
                continue;
            }

        }else if(opc == 2){     //Opcao para contagem regressiva(temporizador)
            inicioT:
            inicio_temporizador();
            char tecla2;

            inicioR:    //Referencia para continuar o temporizador.

            tecla2 = ' ';

            do{
                if(h1==0 && h2==0 && min1==0 && min2==0 && seg1==0 && seg2==0){
                    printf("\nInsira novos valores ou volte para o MENU PRINCIPAL\a\n");
                    break;
                }

                printf("\nDigite a tecla w para pausar: \n\n");
                desenha_cronometro();
                contagem_decrescente();
                system("cls");

                if(kbhit()){
                    tecla2 = getch();
                }

            }while(tecla2 != 'w');

            desenha_cronometro();

            menu_temporizador();

            scanf("%i", &valor);

            if(valor == 1){     //Retomar a contagem
                system("cls");
                goto inicioR;
            }else if(valor == 2){   //Inserir novos valores
                system("cls");
                goto inicioT;
            }else if(valor == 3){   //Voltar para o menu principal
                system("cls");
                continue;
            }
        }else if(opc == 3){     //Opcao para funcao de Relógio
            horarioSistema();

            h1 = horaAt/10;
            h2 = horaAt%10;

            min1 = minAt/10;
            min2 = minAt%10;

            seg1 = segAt/10;
            seg2 = segAt%10;

            char tecla3 = ' ';

            do{
                menu_relogio();
                desenha_cronometro();
                contagem_crescente();
                system("cls");

                if(kbhit()){
                    tecla3 = getch();
                }

            }while(tecla3 != 'w');

        }else if(opc == 4){     //Opcao para visualizar o ultimo tempo registrado
            file = fopen("Relogio.txt", "r");
            if(file == 0){
                printf("Banco de dados não encontrado!\n");
            }
            fscanf(file , "%i %i : %i %i : %i %i", &h1, &h2, &min1, &min2, &seg1, &seg2);
            fclose(file);
            printf("\nÚltima hora registrada\n\n");
            desenha_cronometro();
            printf("\n\n");
            system("pause");
            system("cls");
        }

    }while(opc != 5);  //Sair do loop

    return 0;
}
