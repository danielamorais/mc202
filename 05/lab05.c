/**
 * Daniela Marques de Morais - 169562
 * */

#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

typedef struct ArvoreArquivo{
    char nome[20];
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
void exibirItens(ArvoreArquivo *no){
    if(no != NULL){
        exibirItens(no->esq);
        printf("OUTPUT %s \t", no->nome);
        exibirItens(no->dir);
    } 
}
 

/* * 
 * Cria novo arquivo na arvore e fazer rotacoes de acordo com o fator de balanceamento  
 * */
void criarItem(char *nomeArquivo, ArvoreArquivo **raiz){
    char arquivo[20];
    strcpy(arquivo, nomeArquivo);
    
    while(*raiz != NULL){
        int comparacaoString = strcmp(arquivo, (*raiz)->nome);
        printf("\nCOMPARACAO: %d\n", comparacaoString);
        if(comparacaoString > 0)
            raiz = &(*raiz)->dir;
        else if(comparacaoString < 0)
            raiz = &(*raiz)->esq;
        else
            (*raiz)->quantidade += 1;    
    }

    *raiz = malloc(sizeof(ArvoreArquivo));
    strcpy((*raiz)->nome, arquivo); 
    (*raiz)->esq = (*raiz)->dir = NULL;
    (*raiz)->quantidade = 0;
    //printf("ADICIONADO: %s\n\n", arquivo);
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
            exibirItens(arvore);
        else if(comando[0] == 't' && comando[4] == 'h')
            criarItem(arquivo, &arvore);
        else
            printf("Comando invalido!"); 
        printf("Comando %s \t Arquivo %s\n", comando, arquivo);
    }
    printf("Exibindo itens....");
    exibirItens(arvore);
}

int main(){
    iniciarArvore(&arvore);
    leituraItens();
    return 0;
}
