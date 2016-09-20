#include <stdio.h>
#include <stdlib.h>

typedef struct Brinquedo{
	int valor;
	struct Brinquedo *prox;
} Brinquedo; 

void inicializarLista(Brinquedo **pilha){
	*pilha = NULL;
}

void adicionarElemento(Brinquedo **pilha, int valor){
	Brinquedo *novoElemento = malloc(sizeof(Brinquedo));
	if(novoElemento == NULL){
		printf("Erro ao inserir novo elemento!");
		exit(1);
	}
	novoElemento->valor = valor;
	novoElemento->prox = *pilha;
	*pilha = novoElemento; 
}

void imprimirPilha(Brinquedo **pilha){
	Brinquedo *aux = *pilha; 
	while(aux != NULL){
		printf("%d ", aux->valor);
		aux = aux->prox;
	}
}

void lerEntrada(Brinquedo **pilha){
	int numero; 
	char proxChar;

	while(scanf("%d%c", &numero, &proxChar) == 2){
		adicionarElemento(pilha, numero);
		if(proxChar == '\n' || proxChar == '\r')
			break;
	}
}

int main(){
	Brinquedo *pilha;
	inicializarLista(&pilha);
	lerEntrada(&pilha);
	imprimirPilha(&pilha);
	return 0;
}
