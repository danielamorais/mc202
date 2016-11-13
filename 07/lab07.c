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
    ElementoCache *elementos;
    int qtdSolicitacoes;
    unsigned int qtdElementos;
} InfoCache;

int contador = 0;
unsigned int contadorElementos = 0; //FIXME refatorar
unsigned short int tamanhoCache;
InfoCache informacoesCache;

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
    for(int i = 0; i < tamanho; i++){
        printf("Elemento: %d \t ", array[i].elemento);
    }
    printf("\n");
}

/* Realiza leitura de itens e guarda os elementos lidos num array */
InfoCache leituraItens(){
    unsigned int solicitacoes;
    int elemento;
    unsigned int qtdElementos;

    scanf("%hu %d %d", &tamanhoCache, &qtdElementos, &solicitacoes);

    informacoesCache.elementos = malloc(solicitacoes * sizeof(ElementoCache));
    informacoesCache.qtdSolicitacoes = solicitacoes;
    informacoesCache.qtdElementos = qtdElementos;

    for(int i = 0; i < solicitacoes; i++){
        scanf("%d", &elemento);
        informacoesCache.elementos[i].elemento = elemento;
        informacoesCache.elementos[i].quantidade = 0;
    }
    //printf("Exibir vetor...\n");
    //exibirVetor(informacoesCache.elementos, solicitacoes);
    return informacoesCache;
}

/* Ajusta arvore para que continue sendo heap apos a remocao da raiz */
void ajustarRemocaoMinimo(ElementoCache **pointerHeap){
    ElementoCache *heap = *pointerHeap;
    int pos = 1;
    if(pos*2 < tamanhoCache && ((2*pos)+1) < tamanhoCache){
        if(((2*pos)+1) >= tamanhoCache){
            if(heap[pos].quantidade < heap[pos*2].quantidade){
                ElementoCache *maiorFilho = &heap[2*pos];
                ElementoCache paiTemp = heap[pos];
                heap[pos] = *maiorFilho;
                *maiorFilho = paiTemp;
            }
            return ;
        }

        while(heap[pos].quantidade < heap[pos*2].quantidade || heap[pos].quantidade < heap[(2*pos)+1].quantidade){
            //if(heap[2*pos].elemento == -1)
            //    break;
            ElementoCache *maiorFilho;
            int posFilho = 0;
            if(heap[2*pos].quantidade > heap[(2*pos)+1].quantidade){
                maiorFilho = &heap[2*pos];
                posFilho = 2*pos;
            }
            else{
                maiorFilho = &heap[(2*pos)+1];
                posFilho = (2*pos)+1;
            }
            ElementoCache paiTemp = heap[pos];
            heap[pos] = *maiorFilho;
            *maiorFilho = paiTemp;
            pos = posFilho;
            if(pos >= (tamanhoCache-1) || (pos*2) >= (tamanhoCache-1)) break;
        }
    }
}

/* Verificar se determinado elemento esta no heap */
int contemElemento(ElementoCache elemento, ElementoCache **pointerHeap){
    ElementoCache *heap = *pointerHeap;
    for(int i = 1; i < tamanhoCache; i++){
        if(heap[i].elemento == elemento.elemento){
            heap[i] = elemento;
            return 1;
        }
    }
    return 0;
}

void alterarPrioridade(ElementoCache **pointElementos, int tamanho){
    ElementoCache *elementos = *pointElementos;
    //printf("Os proximos elementos sao: \t");
    for(int i = 0; i < tamanho; i++){
        for(int j = i+1; j < tamanho; j++){
            //printf("Comparando %d com %d ", elementos[i].elemento, elementos[j].elemento);
            if(elementos[i].elemento == elementos[j].elemento){
                elementos[i].quantidade = j;
                break;
            }
            elementos[i].quantidade = 10001;
        }
        // printf(" %d-%d ", elementos[i].elemento, elementos[i].quantidade);
    }
    // printf("\n\n");
}

/* Ira inserir o elemento na ultima posicao do array e ajustar de acordo com a prioridade. O heap possuir -1 como elemento significa que eh uma posicao vazia */
void adicionarElemento(ElementoCache heap[], ElementoCache item){
    //Buscar primeira posicao vazia
    int i = 1;
    int contemPosicaoVazia = 0;
    if(heap[i].elemento == -1){
        heap[1] = item;
        contador++;
    }else{

        //Verificar se o elemento ja esta no heap
        if(contemElemento(item, &heap) == 1){
            ajustarRemocaoMinimo(&heap);
            return ;
        }
        int posicaoVazia = 0;
        for(int i = 2; i < tamanhoCache; i++){
            if(heap[i].elemento == -1){
                contemPosicaoVazia = 1;
                posicaoVazia = i;
                break;
            }
        }
        //Tornar o maximo sempre a raiz da arvore
        if(contemPosicaoVazia == 1){
            heap[posicaoVazia] = item;
            contador++;
            if((posicaoVazia/2) != 0){ //FIXME: Posicao vazia nunca sera 0
                //Verifica se o filho eh maior que o pai
                while((heap[posicaoVazia].quantidade > heap[posicaoVazia/2].quantidade)){
                    ElementoCache temporario = heap[posicaoVazia/2];
                    heap[posicaoVazia/2] = heap[posicaoVazia];
                    heap[posicaoVazia] = temporario;
                    posicaoVazia = posicaoVazia/2;
                    if(posicaoVazia == 1) break;
                }
            }
        }else{
            //Remover a raiz da arvore. A nova raiz deve ser o ultimo elemento do heap
            heap[1] = heap[tamanhoCache-1];
            heap[tamanhoCache-1].elemento = -1;
            heap[tamanhoCache-1].quantidade = 0;
            ajustarRemocaoMinimo(&heap);
            adicionarElemento(heap, item);
        }
    }
}

void lerSolicitacoes(ElementoCache heap[], InfoCache *informacoes){
    for(int i = 0; i < informacoes->qtdSolicitacoes; i++){
        adicionarElemento(heap, informacoes->elementos[i]);
    }
}

int main(){
    InfoCache informacoes = leituraItens();
    tamanhoCache++;
    ElementoCache *heap = malloc(tamanhoCache * sizeof(ElementoCache));
    inicializarVetor(heap, tamanhoCache, 1);
    alterarPrioridade(&(informacoes.elementos), informacoes.qtdSolicitacoes);
    lerSolicitacoes(heap, &informacoes);
    printf("%d", contador);
    free(heap);
    free(informacoesCache.elementos);
    return 0;
}
