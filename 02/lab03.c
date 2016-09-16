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

Requisicao *listaRequisicao; 
Lista *mtf; 
Lista *tr; 

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
	inicializarLista(&mtf);
	inicializarLista(&tr);
	inicializarListaRequisicao(&listaRequisicao);
	int n = 0; //tamanho
	int r = 0; //requisicoes 
	char requisicao;
	int numero;

	scanf(" %d %d", &n, &r);
	for(int i = 0; i < n; i++){
		scanf(" %d", &numero);
		if(i == 0){
			adicionarPrimeiroElemento(numero, &mtf);
			adicionarPrimeiroElemento(numero, &tr);
		}else{
			adicionarElemento(numero, &mtf);
			adicionarElemento(numero, &tr);
		}
	}
	for(int i = 0; i < r; i++){
		scanf(" %c %d", &requisicao, &numero);
		i == 0 ? adicionarPrimeiraRequisicao(requisicao, numero, &listaRequisicao) : adicionarRequisicao(requisicao, numero, &listaRequisicao);
	} 

}

void removerItem(Lista **lista, int item){
	Lista *aux = *lista;
	int find = 0;
	while(aux != NULL && find == 0){ 
		Lista *auxiliarProx = aux->prox;
		if(auxiliarProx->dado == item){
			aux->prox = auxiliarProx->prox;
			free(auxiliarProx);
			find = 1;
			break;
		}else if(aux->dado == item){
			*lista = aux->prox;
			free(aux);
			find = 1;
			break;  	
		}else{
			aux = aux->prox;
		}
	}
}

void moverParaFrente(Lista **lista, int item){
	Lista *aux = *lista;
	int find= 0;
	while(aux != NULL && find == 0){
		Lista *auxiliarProx = aux->prox;
		if(auxiliarProx->dado == item){
			//printf("First.. Este %d ira apontar para %d \n", aux->dado, auxiliarProx->prox->dado);
			aux->prox = auxiliarProx->prox;
			//printf("Este %d ira apontar para %d \n", auxiliarProx->dado, (*lista)->dado);
			auxiliarProx->prox = *lista;
			//printf("O inicio da lista sera %d\n", auxiliarProx->dado);
			*lista = auxiliarProx;
			find = 1;
			break;
		}else if(aux->dado == item){
			find = 1;
			break;
		}else{
			aux = aux->prox;
		}
	}
}

void imprimir(Lista **item){
	Lista *aux = *item;
	while(aux != NULL){
		printf(" %d", aux->dado);
		aux = aux->prox;
	}
}

void executarMtf(Lista *lista, Requisicao **requisicao){
	Requisicao *aux = *requisicao;
	Lista *auxLista = lista;
	int k = 0;
	while(aux != NULL){
		switch(aux->tipo){ 
		case 'a': //printf("Movendo para frente %d\n", aux->elemento);
			  moverParaFrente(&auxLista, aux->elemento);
			  imprimir(&auxLista);
			  printf("\n");
			  ++k;
			  break;
		case 'i': //printf("Inserindo no fim..");
			  adicionarElemento(aux->elemento, &auxLista);
			  imprimir(&auxLista);
			  printf("\n");
			  break;
		case 'r': removerItem(&auxLista, aux->elemento);
			  imprimir(&auxLista);
			  printf("\n");
			  break;
		}
		//printf("Saindo do switch..\n");
		aux = aux->prox;
	}
	//*lista = auxLista;
}

int main(){
	leituraItens();
	executarMtf(mtf, &listaRequisicao);
	return 0;
}
