/**
 * Daniela Marques de Morais - 169562
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct ArvoreArquivo{
    char *nome;
    int quantidade;
    struct ArvoreArquivo *esq, *dir;
    enum { MENOS, ZERO, MAIS } fator;
} ArvoreArquivo;

ArvoreArquivo *arvore;

void iniciarArvore(ArvoreArquivo **raiz){
    *raiz = NULL;
}

//TODO
void destruirArvore(ArvoreArquivo **raiz){

}

/**
 * Excluir determinado arquivo da arvore, o nome do arquivo eh passado por referencia 
 * */
void excluirItem(char *arquivo){
    
}

/** 
 * Percorre a arvore inordem e exibe itens em ordem alfabetica 
 * */
void exibirItens(){
    
}

/* * 
 * Cria novo arquivo na arvore e fazer rotacoes de acordo com o fator de balanceamento  
 * */
void criarItem(char *arquivo, ArvoreArquivo **raiz){
    ArvoreArquivo *auxRaiz = *raiz;
    while(auxRaiz != NULL){
        int comparacaoString = strcmp(auxRaiz->nome, arquivo);
        if(comparacaoString > 0)
            auxRaiz = auxRaiz->dir;
        if(comparacaoString < 0)
            auxRaiz = auxRaiz->esq;
        else
            auxRaiz->quantidade += 1;    
    }

    auxRaiz = malloc(sizeof(ArvoreArquivo));
    auxRaiz->nome = arquivo; 
    auxRaiz->esq = auxRaiz->dir = NULL;
    auxRaiz->quantidade = 0;
    printf("ADICIONADO: %s\n", arquivo);
}


/**
 * Faz a leitura dos comandos com os respectivos nomes dos arquivos
 * */
void leituraItens(){
    char comando[5];
    char arquivo[20];

    //FIXME: Mudar para EOF
    //while(scanf("$s %s", comando, arquivo) != EOF){

    while(scanf("%s %s", comando, arquivo) == 2 && comando[0]!= 'p'){
        if(comando[0] == 'r' && comando[1] == 'm')
               excluirItem(arquivo);
        else if(comando[0] == 'l' && comando[1] == 's')
               exibirItens();
        else if(comando[0] == 't' && comando[4] == 'h')
                criarItem(arquivo, &arvore);
        else
            printf("Comando invalido!"); 
        printf("Comando %s \t Arquivo %s\n", comando, arquivo);
    }
}

int main(){
    iniciarArvore(&arvore);
    leituraItens();
    return 0;
}
