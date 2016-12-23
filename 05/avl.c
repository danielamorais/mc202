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

ArvoreAvl** buscarAntecessor(ArvoreAvl **avl, int dado){
    ArvoreAvl **pai = NULL;
    while((*avl) != NULL){
        if((*avl)->dir != NULL){
            pai = &((*avl)->dir);
            if((*pai)->dado == dado){
                return &((*avl));
            } 
        }
        if((*avl)->esq != NULL){
            pai = &((*avl)->esq);
            if((*pai)->dado == dado){
                return &((*avl));
            } 
        }
        if((*avl)->dado > dado){
            avl = &((*avl)->esq);
        }else if((*avl)->dado < dado){
            avl = &((*avl)->dir);
        }    
    }
    return NULL;

}

/**
 * Remover caso em que pelo menos um filho eh vazio
 * */
void removerPrimeiroCaso(ArvoreAvl **no, ArvoreAvl **arvore){
    ArvoreAvl *raiz = *arvore;
    ArvoreAvl **pai = buscarAntecessor(&(raiz), (*no)->dado);
    int direita = 1;
    if(((*pai)->esq)->dado == (*no)->dado){
        direita = 0;
    }
    ArvoreAvl *temp = *no; 
    if((*no)->dir == NULL){
        //Pai apontar para esquerda
        if(direita == 1){
            (*pai)->dir = (*no)->esq; 
        }else{
            (*pai)->esq = (*no)->esq;
        }
    }else{
        if(direita == 1){
            (*pai)->dir = (*no)->dir;
        }else{
            (*pai)->esq = (*no)->dir;
        }
    }
    free(temp);
}

void removerElemento(ArvoreAvl **arv, int dado){
    ArvoreAvl *raiz = *arv;
    //Procurar elemento
    while((*arv)->dado != dado){
        if((*arv)->dado > dado){
            arv = &((*arv)->esq);
        }else{
            arv = &((*arv)->dir); 
        }
    }
    if((*arv)->dir != NULL && (*arv)->esq != NULL){
        printf("Remover segundo caso nao pronto.. \n");
    }else{
        removerPrimeiroCaso(&(*arv), &raiz);
    }
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

void liberarMemoria(ArvoreAvl **arv){
    if(*arv != NULL){
        liberarMemoria(&((*arv)->dir));
        liberarMemoria(&((*arv)->esq));
        free(*arv);
    }
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
    inserirArvore(&arvore, 8);
    inserirArvore(&arvore, 3);
    inserirArvore(&arvore, 13);
    inserirArvore(&arvore, 1);
    inserirArvore(&arvore, 10);
    inserirArvore(&arvore, 7);
    inserirArvore(&arvore, 14);
    inserirArvore(&arvore, 4);
    inserirArvore(&arvore, 12);
    inserirArvore(&arvore, 5);
    inserirArvore(&arvore, 11);
    printf("Mandando exibir...\n");
    exibirArvore(&arvore);
    printf("\nMandando remover..\n");
    removerElemento(&arvore, 10);
    printf("\nExibir apos remocao..\n");
    exibirArvore(&arvore);
    liberarMemoria(&arvore);
    return 0;
}
