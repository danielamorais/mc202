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
int m, n, p;
No *listaUm;
No *listaDois;
No *listaTres; 

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

void imprimirLista(No **inicio, No **fim){
	No *auxInicio = *inicio;
	No *auxFim = *fim;
	while(auxInicio != NULL){
		printf("%d ", auxInicio->dado);
		if(auxInicio->dado == auxFim->dado) break;
		auxInicio = auxInicio->prox;
	}
}

void segundaLista(No **inicio, No **fim, No **listaOriginal){
	No *auxInicio = *inicio; 
	No *auxFim = *fim;
	No *auxOriginal = *listaOriginal;

	//buscar n
	if(auxFim->dado == n){
		auxInicio = *fim;
	}else{
		//comecar da mesma posicao de inicio da primeira sublista
		auxInicio = *inicio;
	}
	if((*inicio)->dado == p){
		auxFim = *inicio;	
	}else{
		//terminar no fim da lista original
		while(auxFim != NULL){
			if(auxFim->prox == NULL){
				break;
			}
			auxFim = auxFim->prox;
		}	
	}
	printf("\nsegunda ");
	imprimirLista(&auxInicio, &auxFim);

}

void primeiraLista(No **lista){
	No *aux = *lista;
	No *inicio = *lista; 
	No *fim = NULL; 

	//buscar m	
	while(aux->dado != m && aux->prox != NULL){
		aux = aux->prox;
		if(aux->dado == m) inicio = aux; 
	}

	//buscar n em sublista 
	while(aux->dado != n && aux->prox != NULL){
		aux = aux->prox;
		if(aux->dado == n) fim = aux; 
	}	
	if(fim == NULL){
		aux = *lista;
		while(aux -> dado != p && aux->prox != NULL){
			aux = aux->prox;
			if(aux -> dado == p) fim = aux; 
		}
		if(fim == NULL){
			fim = *lista;
			//percorrer ate o fim o lista
			while(fim != NULL){
				if(fim->prox == NULL) break; 
				fim = fim->prox;  
			}
		}
	}
	printf("primeira ");
	imprimirLista(&inicio, &fim);
	segundaLista(&inicio, &fim, &(*lista));
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
		//Leitura de m, n e p
		if (next_char == '\n'){
			scanf("%d %d %d", &m, &n, &p);
			break; 
		}
	}

	atual = lista; 
	//Exibir valores
	printf("original "); 
	while(atual != NULL){
		printf("%d ", atual->dado);
		atual = atual->prox;
	}
	printf("\nm=%d, n=%d, p=%d\n", m, n, p);
	 primeiraLista(&lista);
	return 0; 
}
