#include <stdio.h>
#include <stdlib.h>

typedef struct Elementos{
    int item;
    int quantidade;
} Elementos; 

int contem(Elementos v[], int n, int t){
    int i = 0;
    for(i = 0; i < t; i++){
        if(v[i].item == n){
            v[i].quantidade += 1;
            return 1;
        }
    }
    return 0; 
} 

void inicializarVetor(Elementos v[], int t){
    int i = 0;
    for(i = 0; i < t; i++){
        v[i].item = -1;
        v[i].quantidade = 0;
    }
}

int main(){
    int tamanho, numeros, solicitacoes = 0;
    scanf("%d %d %d", &tamanho, &numeros, &solicitacoes);
    tamanho += 1;
    Elementos vetor[numeros];
    inicializarVetor(vetor, tamanho);
    int i = 0;
    int leitura = 0;
    int j = 0;
    for(i = 0; i < solicitacoes; i++){
        scanf("%d", &leitura);
        if(contem(vetor, leitura, numeros) == 0){
            vetor[j].item = leitura;
            vetor[j].quantidade = 1;
            j += 1;
        }
    } 
    printf("\n\n");
    for(i = 0; i < numeros; i++){
        printf("%d - %d\n", vetor[i].item, vetor[i].quantidade);
    }
    return 0;
}
