/**
 * Daniela Marques de Morais - 169562
 * */

#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreArquivo{
    char nome[20];
    int quantidade;
    struct ArvoreArquivo *esq, *dir;
    enum { MENOS, ZERO, MAIS } fator;
} *ArvoreArquivo;

void iniciarArvore(ArvoreArquivo **raiz){
    *raiz = NULL;
}

//TODO
void destruirArvore(ArvoreArquivo **raiz){

}

/**
 * Faz a leitura dos comandos com os respectivos nomes dos arquivos
 * */ 
void leituraItens(){
    char comando[2];
    int numero;
    char arquivo[20];
    char fimDaLinha = ' ';

    while(scanf("%s %s", comando, arquivo) == 2){
       printf("Comando %s \t Arquivo %s\n", comando, arquivo);
       /* if(fimDaLinha == '\n' || fimDaLinha == '\r'){ */
       /*      printf("Thats all folks"); */
       /*      break; */
       /* } */
    
    }
}

int main(){
    leituraItens();
    return 0;
}
