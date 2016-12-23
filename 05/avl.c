/* *
 * Daniela Marques de Morais - 169562
 * */

#include <stdlib.h>
#include <stdio.h>

typedef struct ArvoreAvl{
    int dado;
    struct ArvoreAvl *dir, *esq;
    int fator; 
} ArvoreAvl; 

void inicializarArvore(ArvoreAvl **arvore){
    *arvore = NULL; 
}

void inserirArvore(ArvoreAvl **arv, int dado){
    while(*arv != NULL){
        if(dado > (*arv)->dado){
            arv = &((*arv)->dir);
        }else{
            arv = &((*arv)->esq);
        }
    }

    *arv = (ArvoreAvl *)  malloc(sizeof(ArvoreAvl));
    (*arv)->esq = (*arv)->dir = NULL;
    (*arv)->dado = dado;
}

/**
 * Percorrer arvore inordem
 * */
void exibirArvore(ArvoreAvl **arv){
    if(*arv != NULL){
        exibirArvore(&((*arv)->esq));
        printf("OUTPUT %d \t", (*arv)->dado);
        exibirArvore(&((*arv)->dir));
    }
}

int main(){
    ArvoreAvl *arvore;
    inicializarArvore(&arvore);
    printf("Mandando inserir...\n");
    inserirArvore(&arvore, 20);
    inserirArvore(&arvore, 35);
    inserirArvore(&arvore, 5);
    inserirArvore(&arvore, 17);
    inserirArvore(&arvore, 50);
    inserirArvore(&arvore, 68);
    inserirArvore(&arvore, 3);
    printf("Mandando exibir...\n");
    exibirArvore(&arvore);

    return 0;
}
