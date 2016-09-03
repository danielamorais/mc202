/* *
 * Daniela Marques de Morais - 169562
 * */

#include <stdio.h>
#include <stdlib.h> 

typedef struct No { 
	int dado;
	struct No *prox; 
} No; 

void inicializarLista(No **lista){
	*lista = NULL; 
}

/* *
 * Adicionar novo elemento no fim da lista 
 * */
void adicionarElemento(No **lista, int dado){
	No *novoElemento;
	novoElemento = malloc(sizeof(No));
	if (novoElemento == NULL){
		printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
		exit(1);
	}
	novoElemento->dado = dado; 
	novoElemento->prox = *lista; //Ira apontar para null 
	*lista = novoElemento; //Ira apontar para novo elemento
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


int main(){
	No *lista, *atual;
	int dado;  
	inicializarLista(&lista);
	do{
		scanf("%d ", &dado);
		if(dado != -1){
			adicionarElemento(&lista, dado);
			//exibir valores
			while(atual != NULL){
				printf("%d ", atual->dado);
				atual = atual->prox;
			}
		}
	} while (dado != -1);
	while(atual != NULL){
		printf("%d ", atual->dado);
		atual = atual->prox;
	}
	return 0; 
}
