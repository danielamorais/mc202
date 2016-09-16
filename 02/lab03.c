#include <stdio.h>
#include <stdlib.h>

typedef struct Lista{
	int dado;
	struct Lista *prox;
} Lista;

typedef struct Requisicao{
	char tipo;
	int elemento;
	struct Requisicao *prox; 
} Requisicao;

Lista *lista; 
Requisicao *listaRequisicao; 

void inicializarLista(Lista **lista){
	*lista = NULL;	
}

void inicializarListaRequisicao(Requisicao **lista){
	*lista = NULL;
}

void adicionarElemento(int numero, Lista **lista){
	if((*lista)->prox == NULL){
		Lista *novo = malloc(sizeof(Lista));
		if(novo == NULL){
			printf("Erro ao alocar memoria!");
			exit(1);
		}
		novo->dado = numero;
		novo->prox = NULL;
		(*lista)->prox = novo; 
	}else{
		Lista *aux = (*lista)->prox;
		adicionarElemento(numero, &aux);
	}	
}

void adicionarPrimeiroElemento(int numero, Lista **lista){
	Lista *novo = malloc(sizeof(Lista));
	if(novo == NULL){
		printf("Erro ao alocar memoria!");
		exit(1);
	}
	novo->dado = numero;
	novo->prox = NULL;
	*lista = novo;  
}

void adicionarRequisicao(char requisicao, int numero, Requisicao **listaRequisicao){
	if((*listaRequisicao)->prox == NULL){
		Requisicao *novo = malloc(sizeof(Requisicao));
		if(novo == NULL){
			printf("Erro ao alocar memoria!");
			exit(1);
		}
		novo->elemento = numero;
		novo->tipo = requisicao;
		novo->prox = NULL;
		(*listaRequisicao)->prox = novo; 
	}else{
		Requisicao *aux = (*listaRequisicao)->prox;
		adicionarRequisicao(requisicao, numero, &aux);
	}	

}

void adicionarPrimeiraRequisicao(char requisicao, int numero, Requisicao **listaRequisicao){
	Requisicao *novo = malloc(sizeof(Requisicao));
	if(novo == NULL){
		printf("Erro ao alocar memoria!");
		exit(1);
	}
	novo->elemento = numero;
	novo->tipo = requisicao;
	novo->prox = NULL;
	*listaRequisicao = novo; 
}

void leituraItens(){
	inicializarLista(&lista);
	inicializarListaRequisicao(&listaRequisicao);
	int n = 0; //tamanho
	int r = 0; //requisicoes 
	char requisicao;
	int numero;

	scanf(" %d %d", &n, &r);
	for(int i = 0; i < n; i++){
		scanf(" %d", &numero);
		printf("Lendo .. %d \n", numero);
		i == 0 ? adicionarPrimeiroElemento(numero, &lista) : adicionarElemento(numero, &lista);
	}
	for(int i = 0; i < r; i++){
		scanf(" %c %d", &requisicao, &numero);
		printf("Lendo2 .. %d \n", numero);
		i == 0 ? adicionarPrimeiraRequisicao(requisicao, numero, &listaRequisicao) : adicionarRequisicao(requisicao, numero, &listaRequisicao);
	} 

}

int main(){
	leituraItens();
	//Exibir itens 
	Lista *atual = lista;
	printf("Printando \n");
	while(atual != NULL){
		printf("%d ", atual->dado);
		atual = atual->prox;
	}

	printf("\n Printando char\n");
	Requisicao *atualReq = listaRequisicao;
	while(atualReq != NULL){
		printf(" %c %d\n", atualReq->tipo, atualReq->elemento);
		atualReq = atualReq->prox;
	}
	return 0;
}
