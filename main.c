#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//Thiago Leandro Liporace 42128481
//Lucas Goulart de Farias Meres 42127459

//Fontes para o projeto foram GeeksforGeeks.org, Stackoverflow.com e tutorialkart.com

// Funcao para imprimir o tabuleiro, com identacao adequada para numeros decimais
void print_tabuleiro(int tamanho,int *tabuleiro){
  printf("---------------------------------------\n");
  for (int i = 0;i < tamanho;i++){
    for (int j = 0;j < tamanho;j++){
      if (tabuleiro[i*tamanho + j] >= 10) printf("%d  ",tabuleiro[i*tamanho + j]);
      else printf("%d   ",tabuleiro[i*tamanho + j]);
    }
    printf("\n");
  }
}

// Funcao para abrir o arquivo, scanear a quantidade de elementos colocada, alocar memoria para a matriz e armazenar os numeros do arquivo dentro da matriz
int *cria_tabuleiro(){
  int tamanho,num;
  FILE *textfile = fopen("ladrilho.txt", "r");
  fscanf(textfile, "%d",&tamanho);
  int *tabuleiro = (int*)malloc((tamanho*tamanho)*sizeof(int));
  for (int i = 0;i < tamanho*tamanho;i++){
    fscanf(textfile,"%d",&num);
    tabuleiro[i] = num;
  }
  fclose(textfile);
  return tabuleiro;
}

// Funcao que checa se a ordem do tabuleiro esta de acordo ou nao
void checa_ordem(int *tabuleiro,int tamanho){
  int count = 0;
  for (int i = 0;i < tamanho*tamanho;i++){
    if ((i == tamanho*tamanho-1) && (tabuleiro[i] == 0)){
      count++;
    }
    else if (tabuleiro[i] < tabuleiro[i+1]){
      count++;
    }
  }
  if (count != (tamanho*tamanho)-1){
    printf("O tabuleiro ainda nao esta ordenado!\n");
  }
  else printf("O tabuleiro esta ordenado! HIHI HAHAHA!\n");
}

// Funcao que checa e gera o movimento desejado pelo usuario dentro do arquivo .txt
void movimento(int *tabuleiro,int tamanho){
  int x,passos,num,aux;
  FILE *textfile = fopen("ladrilho.txt", "r");
  char ch;
  
  // Loop que apenas leva o .txt para o lugar adequado para o inicio da funcao de movimento.
  for (int i = 0;i < tamanho*tamanho+1;i++) fscanf(textfile,"%d",&x); 
  fscanf(textfile,"%d",&passos);
  for (int i=0;i<passos;i++){
    fscanf(textfile,"%d",&num);
    ch = fgetc(textfile);
    
    // Loop com funcao de pular os espacos ate que ch seja uma letra.
    while (ch == ' '){
      ch = fgetc(textfile);
    }

    // Loop que permite faz de fato os movimentos e as checagens de cada ordem do usuario.
    for (int j = 0;j < tamanho*tamanho;j++){
      if (tabuleiro[j] == num){
        if (ch == 'c'){
          if (tabuleiro[j-tamanho] == 0){
            aux = tabuleiro[j];
            tabuleiro[j] = tabuleiro[j-tamanho];
            tabuleiro[j-tamanho] = aux;
            break;
          }
          else {
            printf("Movimento invalido, fechando o programa...");
            return;
          }
        }
        else if (ch == 'b'){
          if (tabuleiro[j+tamanho] == 0){
            aux = tabuleiro[j];
            tabuleiro[j] = tabuleiro[j+tamanho];
            tabuleiro[j+tamanho] = aux;
            break;
          }
          else {
            printf("Movimento invalido, fechando o programa...");
            return;
          }
        }
        else if(ch == 'e'){
          if (tabuleiro[j-1] == 0){
            aux = tabuleiro[j];
            tabuleiro[j] = tabuleiro[j-1];
            tabuleiro[j-1] = aux;
            break;
          }
          else {
            printf("Movimento invalido, fechando o programa...");
            return;
          }
        }
        else if (ch == 'd'){
            if (tabuleiro[j+1] == 0){
            aux = tabuleiro[j];
            tabuleiro[j] = tabuleiro[j+1];
            tabuleiro[j+1] = aux;
            break;
          }
          else {
            printf("Movimento invalido, fechando o programa...");
            return;
          }
        }
      }
    }
    printf("---------------------------------------\n");
    checa_ordem(tabuleiro,tamanho);
    print_tabuleiro(tamanho,tabuleiro);
    sleep(2);
  }
  fclose(textfile);
}

int main() {
  int tamanho,x,passos;
  FILE *textfile = fopen("ladrilho.txt", "r");
  fscanf(textfile, "%d",&tamanho);
  int *tabuleiro = cria_tabuleiro();
  movimento(tabuleiro,tamanho);
  free(tabuleiro);
  return 0;
}