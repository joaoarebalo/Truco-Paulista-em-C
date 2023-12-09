#include <stdio.h>
#include <string.h>
#include <time.h>

struct JOGADOR {
    char nome_jogador[50];
    int  ordem;
    char cartas[2][50];
};

typedef struct Time {
    char nome_time[50];
    int pontos_time;
    struct JOGADOR Jogador_A;
    struct JOGADOR Jogador_B;
} Time;

int ordem_criacao = 1;

void DesserializarCartas(char cartas[39][50]);
void JogarTruco(char cartasOrdenadas[39][50]);
Time CriarTime();
void embaralharCartas(char cartas[39][50]);
void jogarRodada(Time *Time_1, Time *Time_2, char cartasOrdenadas[39][50]);
void separarCartas(Time *Time_1, Time *Time_2, char cartas[39][50]);
void separarManilha(char Cartas[39][50]);
int pegarCartaUsuario(Time *Time_1, Time *Time_2,char cartas[39][50]);
void removerElemento(char array[][50], int *tamanho, int indice);
int encontrarIndexNaRodada(char carta[50], char CartasRodada[39][50]);


int main() {
    char cartasOrdenadas[39][50];
    DesserializarCartas(cartasOrdenadas);
    JogarTruco(cartasOrdenadas);

    return 0;
}

void DesserializarCartas(char cartas[39][50]) {
    int i = 0;
    char str[] = "4 Ouro/4 Espada/4 Copas/4 Paus/5 Ouro/5 Espada/5 Copas/5 Paus/6 Ouro/6 Espada/6 Copas/6 Paus/7 Ouro/7 Espada/7 Copas/7 Paus/Q Ouro/Q Espada/Q Copas/Q Paus/J Ouro/J Espada/J Copas/J Paus/K Ouro/K Espada/K Copas/K Paus/A Ouro/A Espada/A Copas/A Paus/2 Ouro/2 Espada/2 Copas/2 Paus/3 Ouro/3 Espada/3 Copas/3 Paus";

    int init_size = strlen(str);
    char delim[] = "/";

    char *ptr = strtok(str, delim);

    while (ptr != NULL) {
        strcpy(cartas[i], ptr);
        ptr = strtok(NULL, delim);
        i++;
    }
}

void JogarTruco(char cartasOrdenadas[39][50]) {
    Time Time_1;
    Time Time_2;

    Time_1 = CriarTime();
    Time_2 = CriarTime();

    while (Time_1.pontos_time < 12 && Time_2.pontos_time < 12)
    {
        printf("\n________________________________________________\n");
        printf("\n             Placar Parcial                     \n");
        jogarRodada(&Time_1, &Time_2, cartasOrdenadas);
        printf("Time 1: %i \n", Time_1.pontos_time);
        printf("Time 2: %i \n", Time_2.pontos_time);
        printf("\n________________________________________________\n");


    }
    //jogarRodada(&Time_1, &Time_2, cartasOrdenadas);

 
    
}

void jogarRodada(Time *Time_1, Time *Time_2, char cartasOrdenadas[39][50]) {
    int TotalTime1 = 0;
    int TotalTime2 = 0;
    char CartasRodada[39][50];
    char NomeTime1[50];
    char NomeTime2[50];
    strcpy(NomeTime1,Time_1->nome_time);
    strcpy(NomeTime2,Time_2->nome_time);


    for (int i = 0; i < 39; i++) {
        strcpy(CartasRodada[i], cartasOrdenadas[i]);
    }

    embaralharCartas(CartasRodada);
    separarCartas(Time_1, Time_2, CartasRodada);
    separarManilha(CartasRodada);
    
    
    
    for (int i = 0; i < 40; i++) {
          printf("\n %s \n",CartasRodada[i]);
        }
        
    printf("\n_______________Resumo____________________\n");

    printf("%s\n",NomeTime1);
    printf("ordem: %i \n",Time_1->Jogador_A.ordem);
    printf("%s\n",Time_1->Jogador_A.nome_jogador);
    printf("%s/", Time_1->Jogador_A.cartas[0]);
    printf("%s/", Time_1->Jogador_A.cartas[1]);
    printf("%s", Time_1->Jogador_A.cartas[2]);

    printf("\n________________________________________________\n");

    printf("%s\n",NomeTime1);
    printf("ordem: %i \n",Time_1->Jogador_B.ordem);
    printf("%s\n",Time_1->Jogador_B.nome_jogador);
    printf("%s/", Time_1->Jogador_B.cartas[0]);
    printf("%s/", Time_1->Jogador_B.cartas[1]);
    printf("%s", Time_1->Jogador_B.cartas[2]);
    
   printf("\n________________________________________________\n");
    
    printf("%s\n",NomeTime2);
    printf("ordem: %i \n",Time_2->Jogador_A.ordem);
    printf("%s\n",Time_2->Jogador_A.nome_jogador);
    printf("%s/", Time_2->Jogador_A.cartas[0]);
    printf("%s/", Time_2->Jogador_A.cartas[1]);
    printf("%s", Time_2->Jogador_A.cartas[2]);

    printf("\n________________________________________________\n");
    
    printf("%s\n",NomeTime2);    
    printf("ordem: %i \n",Time_2->Jogador_B.ordem);
    printf("%s\n",Time_2->Jogador_B.nome_jogador);
    printf("%s/", Time_2->Jogador_B.cartas[0]);
    printf("%s/", Time_2->Jogador_B.cartas[1]);
    printf("%s", Time_2->Jogador_B.cartas[2]);
    
    printf("\n________________________________________________\n");

    while (TotalTime1 != 2 && TotalTime2 != 2) {
        int TimeVencedor;
        //Caso retorne 1 Time 1 caso retorne 2 Time 2 
        TimeVencedor = pegarCartaUsuario(Time_1,Time_2,CartasRodada);
        if(TimeVencedor == 1){
            TotalTime1 ++;
        }
        else{
            TotalTime2++;
        }
        
        printf("\nParcial\n");
        printf("\n %s  - %i Rodadas\n",NomeTime1,TotalTime1);
        printf("\n %s  - %i Rodadas \n",NomeTime2,TotalTime2);
        
        printf("\n________________________________________________\n");


    }
    
    if(TotalTime1 == 2){
        Time_1->pontos_time = Time_1->pontos_time + 3;
    }
    else{
        Time_2->pontos_time = Time_2->pontos_time + 3;
    }


   // Time_1.pontos_time = 24;
    //Time_2.pontos_time = 24;
}

int pegarCartaUsuario(Time *Time_1, Time *Time_2,char cartas[39][50])
{
    char CartaTime1JogadorA[50];
    char CartaTime1JogadorB[50];
    char CartaTime2JogadorA[50];
    char CartaTime2JogadorB[50];
    
    int indexCartaTime1JogadorA;
    int indexCartaTime1JogadorB;
    int indexCartaTime2JogadorA;
    int indexCartaTime2JogadorB;

    for (int i = 1; i < 5; i++)
    {
        if (Time_1->Jogador_A.ordem == i)
        {
            int indexCarta;
            int qnt_Array_Cartas = sizeof(Time_1->Jogador_A.cartas) / sizeof(Time_1->Jogador_A.cartas[0]);
            printf("%s selecione uma carta: \n", Time_1->Jogador_A.nome_jogador);
            for (int i = 0; i < qnt_Array_Cartas + 1; i++)
            {
                
                if(strcmp(Time_1->Jogador_A.cartas[i] , "NULL") != 0) 
                {
                  printf("\n %i - %s \n", i, Time_1->Jogador_A.cartas[i]);
                }
            }
            scanf("%i", &indexCarta);
            strcpy(CartaTime1JogadorA, Time_1->Jogador_A.cartas[indexCarta]);
            removerElemento(Time_1->Jogador_A.cartas, &qnt_Array_Cartas, indexCarta);
            printf("\n________________________________________________\n");

        }
        if (Time_1->Jogador_B.ordem == i)
        {
            int indexCarta;
            int qnt_Array_Cartas = sizeof(Time_1->Jogador_B.cartas) / sizeof(Time_1->Jogador_B.cartas[0]);
            printf("%s selecione uma carta: \n", Time_1->Jogador_B.nome_jogador);
            for (int i = 0; i < qnt_Array_Cartas + 1; i++)
            {
                if(strcmp(Time_1->Jogador_B.cartas[i] ,"NULL") != 0) 
                {
                 printf("\n %i - %s \n", i, Time_1->Jogador_B.cartas[i]);
                }
            }
            scanf("%i", &indexCarta);
            strcpy(CartaTime1JogadorB, Time_1->Jogador_B.cartas[indexCarta]);
            removerElemento(Time_1->Jogador_B.cartas, &qnt_Array_Cartas, indexCarta);
            printf("\n________________________________________________\n");

        }
        if (Time_2->Jogador_A.ordem == i)
        {
            int indexCarta;
            int qnt_Array_Cartas = sizeof(Time_2->Jogador_A.cartas) / sizeof(Time_2->Jogador_A.cartas[0]);
            printf("%s selecione uma carta: \n", Time_2->Jogador_A.nome_jogador);
            for (int i = 0; i < qnt_Array_Cartas + 1; i++)
            {
                if(strcmp(Time_2->Jogador_A.cartas[i] , "NULL") != 0) 
                {
                 printf("\n %i - %s \n", i, Time_2->Jogador_A.cartas[i]);
                }
            }
            scanf("%i", &indexCarta);
            strcpy(CartaTime2JogadorA, Time_2->Jogador_A.cartas[indexCarta]);
            removerElemento(Time_2->Jogador_A.cartas, &qnt_Array_Cartas, indexCarta);
            printf("\n________________________________________________\n");

        }
        if (Time_2->Jogador_B.ordem == i)
        {
            int indexCarta;
            int qnt_Array_Cartas = sizeof(Time_2->Jogador_B.cartas) / sizeof(Time_2->Jogador_B.cartas[0]);
            printf("%s selecione uma carta: \n", Time_2->Jogador_B.nome_jogador);
            for (int i = 0; i < qnt_Array_Cartas + 1; i++)
            {
                if(strcmp(Time_2->Jogador_B.cartas[i] ,"NULL") != 0)
                {
                 printf("\n %i - %s \n", i, Time_2->Jogador_B.cartas[i]);
                }
            }
            scanf("%i", &indexCarta);
            strcpy(CartaTime2JogadorB, Time_2->Jogador_B.cartas[indexCarta]);
            removerElemento(Time_2->Jogador_B.cartas, &qnt_Array_Cartas, indexCarta);
            printf("\n________________________________________________\n");

        }
    }
    indexCartaTime1JogadorA = encontrarIndexNaRodada(CartaTime1JogadorA,cartas);
    indexCartaTime1JogadorB = encontrarIndexNaRodada(CartaTime1JogadorB,cartas);
    indexCartaTime2JogadorA = encontrarIndexNaRodada(CartaTime2JogadorA,cartas);
    indexCartaTime2JogadorB = encontrarIndexNaRodada(CartaTime2JogadorB,cartas);

   // printf("\n %i INDEX MONTE TIME 1 JOGADOR A\n", indexCartaTime1JogadorA);
    //printf("\n %i INDEX MONTE TIME 1 JOGADOR B\n", indexCartaTime1JogadorB);
   // printf("\n %i INDEX MONTE TIME 2 JOGADOR A\n", indexCartaTime2JogadorA);
   // printf("\n %i INDEX MONTE TIME 2 JOGADOR B\n", indexCartaTime2JogadorB);
    
    if (indexCartaTime1JogadorA < indexCartaTime2JogadorA && indexCartaTime1JogadorA < indexCartaTime2JogadorB && indexCartaTime1JogadorA < indexCartaTime1JogadorB) {
        printf("\nTime 1 Ganhou Jogador A tem a carta mais forte\n");
        return 1;
    } else if (indexCartaTime1JogadorB < indexCartaTime2JogadorA && indexCartaTime1JogadorB < indexCartaTime2JogadorB && indexCartaTime1JogadorB < indexCartaTime1JogadorA){
        printf("\nTime 1 Ganhou Jogador B tem a carta mais forte\n");
        return 1;
    }
    else if (indexCartaTime2JogadorA < indexCartaTime1JogadorA && indexCartaTime2JogadorA < indexCartaTime1JogadorB && indexCartaTime2JogadorA < indexCartaTime2JogadorB){
        printf("\nTime 2 Ganhou Jogador A tem a carta mais forte\n");
        return 2;
    }
    else{
        printf("\nTime 2 Ganhou Jogador B tem a carta mais forte\n");
        return 2;

    }
    printf("\n________________________________________________\n");

}

int encontrarIndexNaRodada(char carta[50], char CartasRodada[39][50]) {
    for (int i = 0; i < 39; i++) {
        if (strcmp(carta, CartasRodada[i]) == 0) {
            return i;
        }
    }
    return 1000; // Retorna -1 se a carta não for encontrada
}

void removerElemento(char array[][50], int *tamanho, int indice) {
    if (indice < 0 || indice >= *tamanho) {
        return;
    }
    
    strcpy(array[indice], "NULL");

    (*tamanho)--;
}

void separarManilha(char CartasEmbaralhadas[39][50])
{
    char InicialAnteriorManilha;
    char InicialManilha = '4';
    char OrdemManilha[10] = {'3','2','A','K','J','Q','7','6','5','4'};
    char OrdemNipe[4][25] = {"Paus","Copas","Espada","Ouro"};
    char Retorno[40][50];
    

    //Inicial da 13 Carta do baralho
    InicialAnteriorManilha = CartasEmbaralhadas[12][0];
    
    
    
    //Pego a manilha do jogo na proxima posicao do Vira
    for (int i = 0; i < 9; i++) {
        if (OrdemManilha[i] == InicialAnteriorManilha && InicialAnteriorManilha != '4') {
            i = i + 1;
            InicialManilha = OrdemManilha[i];
            break;  
        }
    }
    
    printf("\n________________________________________________\n");

    printf("\nA Manilha do jogo é: %c \n",InicialManilha);
    
    printf("\n________________________________________________\n");

    //Coloca no inicio do Array as manilhas
 
    for (int i = 0; i < 4; i++) {
        char tempString[50];
        tempString[0] = InicialManilha;
        tempString[1] = ' ';
        strcpy(&tempString[2], OrdemNipe[i]);
        strcpy(Retorno[i], tempString);
    }


    int InicioArrayReordenado = 4;

    // Completa o Array com o restante das cartas
    for (int i = 0; i < 11; i++) {
        for (int j = 0; j < 4; j++) {
            if(OrdemManilha[i] != InicialManilha){
                
                char tempString[50];
                tempString[0] = OrdemManilha[i];
                tempString[1] = ' ';
                strcpy(&tempString[2], OrdemNipe[j]); 
                
                
                strcpy(Retorno[InicioArrayReordenado], tempString);
                InicioArrayReordenado ++;
            }
        }
    }
    

     //Valoriza variavel do parametro
     for (int i = 0; i < 40; i++) {
        strcpy(CartasEmbaralhadas[i], Retorno[i]);
    }
    
}


void embaralharCartas(char cartas[39][50]) {
    srand((unsigned int)time(NULL));

    for (int i = 39; i > 0; i--) {
        int j = rand() % (i + 1);

        // Troca as cartas nas posições i e j
        char temp[39];
        strcpy(temp, cartas[i]);
        strcpy(cartas[i], cartas[j]);
        strcpy(cartas[j], temp);
    }
}

Time CriarTime() {
    Time time;
    char nomeTime[50];
    char nomeJogadorA[50];
    char nomeJogadorB[50];
    char cartasNull[2][50];

    printf("**********************************************\n");
    printf("Insira o nome do Time: ");
    scanf("%s", &nomeTime);

    printf("Insira o nome do Jogador 1 do %s:", nomeTime);
    scanf("%s", &nomeJogadorA);

    printf("Insira o nome do Jogador 2 do %s:", nomeTime);
    scanf("%s", &nomeJogadorB);

    struct JOGADOR jogadorA;
    strcpy(jogadorA.nome_jogador,nomeJogadorA);
    jogadorA.ordem = ordem_criacao;
    strcpy(jogadorA.cartas, cartasNull);
    ordem_criacao++;

    struct JOGADOR jogadorB;
    strcpy(jogadorB.nome_jogador,nomeJogadorB);
    jogadorB.ordem = ordem_criacao;
    strcpy(jogadorB.cartas, cartasNull);
    ordem_criacao++;

    strcpy(time.nome_time,nomeTime);
    time.pontos_time = 0;
    time.Jogador_A = jogadorA;
    time.Jogador_B = jogadorB;

    return time;
}

void separarCartas(Time *Time_1, Time *Time_2, char cartas[39][50]) {
  

   
   if(Time_1->Jogador_A.ordem == 1)
   {
     int index = 0;
     for (int i = 0; i <= 2; i++) {
        strcpy(Time_1->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 4 a 6 da pilha para o segundo jogador
   if(Time_1->Jogador_A.ordem == 2)
   {
      int index = 0;
      for (int i = 3; i <= 5; i++) {
        strcpy(Time_1->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 7 a 9 da pilha para o terceiro jogador
   if(Time_1->Jogador_A.ordem == 3)
   {
      int index = 0;
      for (int i = 6; i <= 8; i++) {
        strcpy(Time_1->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 10 a 12 da pilha para o terceiro jogador
   if(Time_1->Jogador_A.ordem == 4)
   {
        int index = 0;
        for (int i = 9; i <= 11; i++) {
        strcpy(Time_1->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }


   //Carta 1 a 3 para o primeiro jogador
   if(Time_1->Jogador_B.ordem == 1)
   {
     int index = 0;
     for (int i = 0; i <= 2; i++) {
        strcpy(Time_1->Jogador_B.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 4 a 6 da pilha para o segundo jogador
   if(Time_1->Jogador_B.ordem == 2)
   {
        int index = 0;
        for (int i = 3; i <= 5; i++) {
        strcpy(Time_1->Jogador_B.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 7 a 9 da pilha para o terceiro jogador
   if(Time_1->Jogador_B.ordem == 3)
   {
      int index = 0;
      for (int i = 6; i <= 8; i++) {
        strcpy(Time_1->Jogador_B.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 10 a 12 da pilha para o terceiro jogador
   if(Time_1->Jogador_B.ordem == 4)
   {

        int index = 0; 
        for (int i = 9; i <= 11; i++) {
        strcpy(Time_1->Jogador_B.cartas[index],cartas[i]);
        index ++;
     }
   }
  
  //********************* TIME 2  *************************
  
   //Carta 1 a 3 para o primeiro jogador
   if(Time_2->Jogador_A.ordem == 1)
   {
     int index = 0;
     for (int i = 0; i <= 2; i++) {
        strcpy(Time_2->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 4 a 6 da pilha para o segundo jogador
   if(Time_2->Jogador_A.ordem == 2)
   {
        int index = 0;
        for (int i = 3; i <= 5; i++) {
        strcpy(Time_2->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 7 a 9 da pilha para o terceiro jogador
   if(Time_2->Jogador_A.ordem == 3)
   {
      int index = 0;
      for (int i = 6; i <= 8; i++) {
        strcpy(Time_2->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }
   //Carta 10 a 12 da pilha para o terceiro jogador
   if(Time_2->Jogador_A.ordem == 4)
   {
        int index = 0;
        for (int i = 9; i <= 11; i++) {
        strcpy(Time_2->Jogador_A.cartas[index],cartas[i]);
        index ++;
     }
   }


   //Carta 1 a 3 para o primeiro jogador
   if (Time_2->Jogador_B.ordem == 1) {
        int index = 0;
        for (int i = 0; i <= 2; i++) {
            strcpy(Time_2->Jogador_B.cartas[index], cartas[i]);
            index++;
        }
    }
   //Carta 4 a 6 da pilha para o segundo jogador
    if (Time_2->Jogador_B.ordem == 2) {
        int index = 0;
        for (int i = 3; i <= 5; i++) {
            strcpy(Time_2->Jogador_B.cartas[index], cartas[i]);
            index++;
        }
    }
   //Carta 7 a 9 da pilha para o terceiro jogador
    if (Time_2->Jogador_B.ordem == 3) {
        int index = 0;
        for (int i = 6; i <= 8; i++) {
            strcpy(Time_2->Jogador_B.cartas[index], cartas[i]);
            index++;
        }
    }
   //Carta 10 a 12 da pilha para o terceiro jogador
    if (Time_2->Jogador_B.ordem == 4) {
        int index = 0;
        for (int i = 9; i <= 11; i++) {
            strcpy(Time_2->Jogador_B.cartas[index], cartas[i]);
            index++;
       }
    }
}