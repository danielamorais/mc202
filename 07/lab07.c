/** Daniela Marques de Morais - 169562
 *  Laboratorio de MC202 sobre Fila de Prioridade
 **/

#include <stdio.h>
#include <stdlib.h>

typedef struct ElementoCache{
    int elemento;
    unsigned short int quantidade;
} ElementoCache;

typedef struct InfoCache{
    ElementoCache *dadosSolicitacoes;
    int *elementos;
    int qtdSolicitacoes;
    unsigned int qtdElementos; 
} InfoCache;

unsigned int contadorElementos = 0; //FIXME refatorar
unsigned short int tamanhoCache;

/* Checa se o elemento existe no array, se nao existir eh adicionado */
void verificarElemento(ElementoCache array[], int tamanho, int elemento){
    for(int i = 0; i < tamanho; i++){
        if(array[i].elemento == elemento){
            array[i].quantidade += 1;
            return ;
        }
    }
    //Adiciona novo elemento no array
    array[contadorElementos].elemento = elemento;
    array[contadorElementos].quantidade = 1;
    contadorElementos++;
}

void inicializarVetor(ElementoCache array[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        array[i].elemento = 0;
        array[i].quantidade = 0;
    }
}

void exibirVetor(ElementoCache array[], int tamanho){
    for(int i = 0; i < tamanho; i++){
        printf("Elemento: %d \t Quantidade %d\n", array[i].elemento, array[i].quantidade);
    }
}

/* Realiza leitura de itens e guarda os elementos lidos num array */
InfoCache leituraItens(){
    unsigned int solicitacoes;
    int elemento;
    InfoCache informacoesCache;
    unsigned int qtdElementos; 

    scanf("%hu %d %d", &tamanhoCache, &qtdElementos, &solicitacoes);
    
    //FIXME usar malloc
    informacoesCache.dadosSolicitacoes = malloc(qtdElementos * sizeof(ElementoCache));
    inicializarVetor(informacoesCache.dadosSolicitacoes, qtdElementos);
    informacoesCache.elementos = malloc(solicitacoes * sizeof(int));
    informacoesCache.qtdSolicitacoes = solicitacoes; 
    informacoesCache.qtdElementos = qtdElementos;

    for(int i = 0; i < solicitacoes; i++){
        scanf("%d", &elemento);
        verificarElemento(informacoesCache.dadosSolicitacoes, qtdElementos, elemento);
        informacoesCache.elementos[i] = elemento;
    }
    exibirVetor(informacoesCache.dadosSolicitacoes, qtdElementos);
    return informacoesCache;
}

void adicionarElemento(ElementoCache heap[], ElementoCache item){
    printf("Quer inserir %d no heap", item.elemento);
}

void lerSolicitacoes(ElementoCache heap[], InfoCache *informacoes){
    for(int i = 0; i < informacoes->qtdSolicitacoes; i++){
        //printf("%d ", informacoes->elementos[i]);
        for(int j = 0; j < informacoes->qtdElementos; j++){
            if(informacoes->elementos[i] == informacoes->dadosSolicitacoes[j].elemento){
                adicionarElemento(heap, informacoes->dadosSolicitacoes[j]);
            }
        } 
    }
}

int main(){
    InfoCache informacoes = leituraItens();
    ElementoCache *heap = malloc(tamanhoCache * sizeof(ElementoCache));
    inicializarVetor(heap, tamanhoCache);
    lerSolicitacoes(heap, &informacoes);
    return 0;
}
