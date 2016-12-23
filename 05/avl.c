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
//FIXME: Nas rotacoes os ponteiros se perdem
void rotacaoEsquerda(ArvoreAvl **raiz){
    printf("\n ESQUERDA \n");
    ArvoreAvl *antigaRaiz, *novaRaiz;
    antigaRaiz = *raiz;
    novaRaiz = antigaRaiz->dir;
    printf("Nova: %d Antiga: %d \n", novaRaiz->dado, antigaRaiz->dado);
    *raiz = novaRaiz;
    antigaRaiz->dir = novaRaiz->esq;
    novaRaiz->esq = antigaRaiz;
}

void rotacaoDireita(ArvoreAvl **raiz){
    printf("\n DIREITA \n");
    ArvoreAvl *antigaRaiz, *novaRaiz;
    antigaRaiz = *raiz;
    novaRaiz = antigaRaiz->esq;
    
    printf("Nova: %d Antiga: %d \n", novaRaiz->dado, antigaRaiz->dado);
    *raiz = novaRaiz;
    antigaRaiz->esq = novaRaiz->dir;
    novaRaiz->dir = antigaRaiz;
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

int alturaArvore(ArvoreAvl **no){
    if(*no == NULL){
        return 0;
    }

    int alturaEsq = alturaArvore(&((*no)->esq));
    int alturaDir = alturaArvore(&((*no)->dir));
    if(alturaEsq > alturaDir)
        return alturaEsq + 1;
    else
        return alturaDir + 1;
}

/* *
 * Verificar se arvore esta balanceada
 * */
void verificarFator(ArvoreAvl **raiz){
    ArvoreAvl *tmp = *raiz;
    (*raiz)->fator = alturaArvore(&((*raiz)->dir)) - alturaArvore(&((*raiz)->esq)); 
    printf("\nO fator eh %d\n", (*raiz)->fator);
    if((*raiz)->fator == 2){
        ArvoreAvl *filho = (*raiz)->dir;
        int fatorFilho = 0;
        if((*raiz)->dir != NULL)
            fatorFilho = alturaArvore(&(filho->dir)) - alturaArvore(&(filho->esq));
        if(fatorFilho >= 0){
            rotacaoEsquerda(raiz);
        }else{
            rotacaoDireita(&(*raiz)->dir);
            rotacaoEsquerda(raiz);
        }
    }else if((*raiz)->fator == -2){
        ArvoreAvl *filho = (*raiz)->esq;
        int fatorFilho = 0;
        if((*raiz)->esq != NULL)
            fatorFilho = alturaArvore(&(filho->dir)) - alturaArvore(&(filho->esq));
        if(fatorFilho < 0){
            rotacaoDireita(&(*raiz));
        }else{
            exibirArvore(&tmp);
            rotacaoEsquerda(&(*raiz)->esq);
            exibirArvore(&tmp);
            rotacaoDireita(raiz);
        }
    }
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

/**
 * Remover caso em que os dois filhos sao NAO vazios
 * */
void removerSegundoCaso(ArvoreAvl **no, ArvoreAvl **arvore){
    ArvoreAvl *raiz = *arvore;
    ArvoreAvl **sucessor = &((*no)->dir);
    while((*sucessor)->esq != NULL){
        sucessor = &((*sucessor)->esq);
    }
    ArvoreAvl *elementoRemover = *sucessor;
    int dado = (*sucessor)->dado;
    removerPrimeiroCaso(&elementoRemover, &raiz);

    (*no)->dado = dado;
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
        removerSegundoCaso(&(*arv), &raiz);
    }else{
        removerPrimeiroCaso(&(*arv), &raiz);
    }
}

void inserirArvore(ArvoreAvl **arv, int dado){
    ArvoreAvl *raiz = *arv;
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
    if(raiz != NULL)
        verificarFator(&raiz);
}

void liberarMemoria(ArvoreAvl **arv){
    if(*arv != NULL){
        liberarMemoria(&((*arv)->dir));
        liberarMemoria(&((*arv)->esq));
        free(*arv);
    }
}

int main(){
    ArvoreAvl *arvore;
    inicializarArvore(&arvore);
    //Teste remocao 2
    /*
       printf("Mandando inserir...\n");
       inserirArvore(&arvore, 8);
       inserirArvore(&arvore, 3);
       inserirArvore(&arvore, 13);
       inserirArvore(&arvore, 1);
       inserirArvore(&arvore, 11);
       inserirArvore(&arvore, 7);
       inserirArvore(&arvore, 14);
       inserirArvore(&arvore, 4);
       inserirArvore(&arvore, 12);
       inserirArvore(&arvore, 9);
       inserirArvore(&arvore, 10);
       printf("Mandando exibir...\n");
       exibirArvore(&arvore);
       printf("\nMandando remover..\n");
       removerElemento(&arvore, 8);
       printf("\nExibir apos remocao..\n");
       exibirArvore(&arvore);
       */
    int entrada = 0;
    while(scanf("%d", &entrada) == 1){
        inserirArvore(&arvore, entrada);
        exibirArvore(&arvore);
    }
    //exibirArvore(&arvore);
    liberarMemoria(&arvore);
    return 0;
}
