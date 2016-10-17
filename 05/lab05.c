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
    int fator;
} ArvoreArquivo;

ArvoreArquivo *arvore;

void iniciarArvore(ArvoreArquivo **raiz){
    *raiz = NULL;
}

//TODO
void destruirArvore(ArvoreArquivo **raiz){

}

//girando a para a esquerda
void rotacaoEsquerda(ArvoreArquivo **raiz){
    ArvoreArquivo *a, *c;
    a = *raiz;
    c = a->dir;

    *raiz = c;
    a->dir = c->esq;
    c->esq = a;
}

//girando b para a direita 
void rotacaoDireita(ArvoreArquivo **raiz){
    ArvoreArquivo *b, *a;
    b = *raiz;
    a = b->esq;

    *raiz = a;
    if(b->esq == NULL){
        printf("Passou da 45rs");
        a->dir = NULL;
    }else
        b->esq = a->dir;
    a->dir = b;
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

int alturaArvore(ArvoreArquivo *no){
    if(no == NULL){
        return 0;
    }

    int alturaEsq = alturaArvore(no->esq);
    int alturaDir = alturaArvore(no->dir);
    if(alturaEsq > alturaDir)
        return alturaEsq + 1;
    else
        return alturaDir + 1;
}

/* *
 * Cria novo arquivo na arvore e fazer rotacoes de acordo com o fator de balanceamento
 * */
int criarItem(char *nomeArquivo, ArvoreArquivo **raiz){
    int aumentou = 0;
    char arquivo[20];
    strcpy(arquivo, nomeArquivo);

    if(*raiz == NULL){
        *raiz = malloc(sizeof(ArvoreArquivo));
        strcpy((*raiz)->nome, arquivo);
        (*raiz)->esq = (*raiz)->dir = NULL;
        (*raiz)->quantidade = 0;
        (*raiz)->fator = 0;
        return 1; //arvore aumentou
    }

    int comparacaoString = strcmp(arquivo, (*raiz)->nome);
    printf("\nCOMPARACAO: %d\n", comparacaoString);
    if(comparacaoString > 0){
        aumentou = criarItem(nomeArquivo, &(*raiz)->dir);
        if(aumentou){
            printf("Aumentou do lado direito %d!!\n\n", aumentou);
            (*raiz)->fator = alturaArvore((*raiz)->dir) - alturaArvore((*raiz)->esq);
            printf("Estou no %s e o fator eh %d \n\n", (*raiz)->nome, (*raiz)->fator);
            if((*raiz)->fator == 2){
                if((*raiz)->dir->fator == 1)
                    rotacaoEsquerda(raiz);
                if((*raiz)->dir->fator == -1){
                    rotacaoDireita(raiz);
                    rotacaoEsquerda(raiz);
                }
            }
        }else
            aumentou = 0;
    }
    else if(comparacaoString < 0){
        aumentou = criarItem(nomeArquivo, &(*raiz)->esq);
        if(aumentou){
            printf("Aumentou do lado esquerdo!!\n");
        }else
            aumentou = 0;
    }
    else{
        (*raiz)->quantidade += 1;
    }
     
   return aumentou; 
}


/**
 * Faz a leitura dos comandos com os respectivos nomes dos arquivos
 * */
void leituraItens(){
    char comando[5];
    char arquivo[20];

    //FIXME: Mudar para EOF e consertar ls
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
