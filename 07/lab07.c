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

void inicializarVetor(ElementoCache array[], int tamanho, int vetorHeap){
    for(int i = 0; i < tamanho; i++){
        array[i].quantidade = 0;
        if(vetorHeap == 0)
            array[i].elemento = 0;
        else
            array[i].elemento = -1;
    }
}

void exibirVetor(ElementoCache array[], int tamanho){
    tamanho++;
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
    inicializarVetor(informacoesCache.dadosSolicitacoes, qtdElementos, 0);
    informacoesCache.elementos = malloc(solicitacoes * sizeof(int));
    informacoesCache.qtdSolicitacoes = solicitacoes;
    informacoesCache.qtdElementos = qtdElementos;

    for(int i = 0; i < solicitacoes; i++){
        scanf("%d", &elemento);
        verificarElemento(informacoesCache.dadosSolicitacoes, qtdElementos, elemento);
        informacoesCache.elementos[i] = elemento;
    }
    //exibirVetor(informacoesCache.dadosSolicitacoes, qtdElementos);
    return informacoesCache;
}

/* Ira inserir o elemento na ultima posicao do array e ajustar de acordo com a prioridade. O heap possuir -1 como elemento significa que eh uma posicao vazia */
void adicionarElemento(ElementoCache heap[], ElementoCache item){
    int contador = 0;
    //Buscar primeira posicao vazia
    int i = 1;
    int contemPosicaoVazia = 0;
    if(heap[i].elemento == -1){
        heap[1] = item;
    }else{
        int posicaoVazia = 0;
        for(int i = 2; i < tamanhoCache; i++){
            if(heap[i].elemento == -1){
                contemPosicaoVazia = 1;
                posicaoVazia = i;
                break;
            }
        }
        //Ajustar para satisfazer prioridade
        if(contemPosicaoVazia == 1){
            heap[posicaoVazia] = item;
            if((posicaoVazia/2) != 0){ //FIXME: Posicao vazia nunca sera 0 
                while(posicaoVazia != 1 && (heap[posicaoVazia].quantidade > heap[posicaoVazia/2].quantidade)){
                    ElementoCache temporario = heap[posicaoVazia/2];
                    heap[posicaoVazia/2] = heap[posicaoVazia];
                    heap[posicaoVazia] = temporario;
                    posicaoVazia = posicaoVazia/2;
                    if(posicaoVazia == 1) break; 
                }
            }
        }else{
            //Remover minimo
            heap[1] = heap[tamanhoCache];
            heap[tamanhoCache].elemento = -1;
            heap[tamanhoCache].quantidade = 0;
            int pos = 1;
            while(heap[pos].quantidade > heap[(2*pos)+1].quantidade || heap[pos].quantidade > heap[(2*pos)].quantidade){
                ElementoCache pai = heap[pos];
                ElementoCache menorFilho;
                //FIXME ambos serao iguais ou nao
                if(heap[(2*pos)+1].quantidade<heap[(2*pos)].quantidade){
                    menorFilho = heap[(2*pos)+1];
                    heap[pos] = menorFilho;
                    heap[(2*pos)+1] = pai; 
                    pos = (2*pos)+1;
                }else{
                    menorFilho = heap[2*pos];
                    heap[pos] = menorFilho;
                    heap[(2*pos)+1] = pai; 
                    pos = 2*pos;
                }

            }

            adicionarElemento(heap, item); 
        }
    }
    exibirVetor(heap, 2);
    printf("\n\n");
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
    tamanhoCache++;
    ElementoCache *heap = malloc(tamanhoCache * sizeof(ElementoCache));
    inicializarVetor(heap, tamanhoCache, 1);
    lerSolicitacoes(heap, &informacoes);
    return 0;
}
