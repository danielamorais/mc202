/* *
 * Daniela Marques de Morais - 169562
 * Programa para receber lista e gerar novas listas a partir de valores m, n e p
 * */

#include <stdio.h>
#include <stdlib.h> 

typedef struct No { 
	int dado;
	struct No *prox; 
} No;

int m, n, p;

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

void terceiraLista(No **inicio, No **fim, No **listaOriginal){
	No *auxInicio = *fim;
	No *auxFim = *listaOriginal;
	while(auxFim->prox != NULL){
		auxFim = auxFim->prox;
	}
	if(auxInicio->dado != p){
		auxInicio = *inicio;
	}
	printf("\nterceira ");
	imprimirLista(&auxInicio, &auxFim);
}

void segundaLista(No **inicio, No **fim, No **listaOriginal){
	No *auxInicio = *inicio; 
	No *auxFim = *inicio;
	No *auxOriginal = *listaOriginal;

	//buscar n
	if((*fim)->dado == n){
		auxInicio = *fim;
	}else{
		//comecar da mesma posicao de inicio da primeira sublista
		auxInicio = *inicio;
	}
	int encontrouP = 0;
	//buscar p a apartir do inicio da sublista 
	while(auxFim->dado != p && auxFim->prox != NULL){
		auxFim = auxFim->prox;
		if(auxFim->dado == p){
			encontrouP = 1;
			break; 
		}
	}		

	if (encontrouP == 0){
		auxFim = *listaOriginal;
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
	terceiraLista(&auxInicio, &auxFim, &auxOriginal);
}

void primeiraLista(No **lista){
	No *aux = *lista;
	No *inicio = *lista; 
	No *fim = NULL; 

	//buscar m	
	while(aux->dado != m && aux->prox != NULL){
		aux = aux->prox;
		if(aux->dado == m){
			inicio = aux;
			break;
		}  
	}
	aux = inicio;
	//buscar n em sublista
	while(aux->dado != n && aux->prox != NULL){
		aux = aux->prox;
		if(aux->dado == n){
			fim = aux;
			break;
		} 
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
	int k = 0; //Verificar se eh o primeiro elemento 
	inicializarLista(&lista);

	//Ler elemento
	char proxChar;
	int numero;
	while (scanf("%d%c", &numero, &proxChar) == 2) {
		++k;
		(k == 1) ? addPrimeiroElemento(&lista, numero) : adicionarElemento(&lista, numero);
		//Leitura de m, n e p
		if (proxChar == '\n' || proxChar == '\r'){
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
	liberarMemoria(&lista);
	return 0; 
}
