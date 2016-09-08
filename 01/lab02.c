/* *
 * Daniela Marques de Morais - 169562
 * */

#include <stdio.h>
#include <stdlib.h> 

typedef struct No { 
	int dado;
	struct No *prox; 
} No;

int k = 0; 

void inicializarLista(No **lista){
	*lista = NULL; 
}

/* *
 * Adicionar novo elemento no fim da lista 
 * */
void adicionarElemento(No **lista, int dado){
	if((*(*lista)).prox == NULL){
		No *novoElemento;
		novoElemento = malloc(sizeof(No));
		if (novoElemento == NULL){
			printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
			exit(1);
		}
		novoElemento->dado = dado; 
		novoElemento-> prox = NULL; 
		(*(*lista)).prox = novoElemento; //Ira apontar para o primeiro elemento
	}else{
		No *aux = (*(*lista)).prox;
		adicionarElemento(&aux, dado);
	}
}

/* *
 * Destruir toda a lista e liberar memoria 
 * */
void liberarMemoria(No **lista){
	No *atual, *proximoElemento; 
	proximoElemento = *lista; //Irá apontar para o primeiro elemento
	while(proximoElemento != NULL){
		atual = proximoElemento;
		proximoElemento = atual->prox;
		free(atual);
	}
}

/*
 * Adicionar primeiro elemento da lista e fazer o nó (cabeça da lista) deixar de apontar para NULL e apontar para primeiro elemento
 */
void addPrimeiroElemento(No **lista, int dado){
	No *novoElemento;
	novoElemento = malloc(sizeof(No));
	if (novoElemento == NULL){
		printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
		exit(1);
	}
	novoElemento->dado = dado;
	novoElemento-> prox = *lista;
	*lista = novoElemento;
}

int main(){
	No *lista, *atual;
	inicializarLista(&lista);
	//Ler elemento
	char next_char;
	int number;

	while (scanf("%d%c", &number, &next_char) == 2) {
		/*  some stuff */
		++k;
		if(k == 1){
			addPrimeiroElemento(&lista, number);
		}else{
			adicionarElemento(&lista, number);
		}
		if (next_char == '\n') break;
	} 

	atual = lista; 
	//Exibir valores 
	while(atual != NULL){
		printf("%d ", atual->dado);
		atual = atual->prox;
	}

	return 0; 
}
