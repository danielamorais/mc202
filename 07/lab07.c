#include <stdio.h>
#include <stdlib.h>

typedef struct ElementoCache{
    int elemento; 
    unsigned short int quantidade; 
} ElementoCache; 

unsigned int contadorElementos = 0; 

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
void leituraItens(){
    unsigned short int tamanhoCache;
    unsigned int qtdElementos;
    unsigned int solicitacoes;
    int elemento; 
    scanf("%hu %d %d", &tamanhoCache, &qtdElementos, &solicitacoes);
    ElementoCache dadosSolicitacoes[qtdElementos];  
    inicializarVetor(dadosSolicitacoes, qtdElementos);
    for(int i = 0; i < solicitacoes; i++){
        scanf("%d", &elemento);
        verificarElemento(dadosSolicitacoes, qtdElementos, elemento);
    }
    exibirVetor(dadosSolicitacoes, qtdElementos);
}

int main(){
    leituraItens();
    return 0;
}
