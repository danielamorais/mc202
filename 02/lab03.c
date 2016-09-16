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

}

void adicionarRequisicao(int requisicao, int numero, Requisicao **listaRequisicao){

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
		adicionarElemento(numero, &lista);
	}
	for(int i = 0; i < r; i++){
		scanf(" %c %d", &requisicao, &numero);
		adicionarRequisicao(requisicao, numero, &listaRequisicao);
	} 

}

int main(){
	leituraItens();
	return 0;
}
