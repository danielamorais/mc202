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
int custoMtf = 0;
int custoTr = 0;
int tamanhoMtf = 0; 

void inicializarLista(Lista **lista){
	*lista = NULL;	
}

void inicializarListaRequisicao(Requisicao **lista){
	*lista = NULL;
}

void adicionarElemento(int numero, Lista **lista, int isMtf){
	if((*lista)->prox == NULL){
		Lista *novo = malloc(sizeof(Lista));
		if(novo == NULL){
			printf("Erro ao alocar memoria!");
			exit(1);
		}
		novo->dado = numero;
		novo->prox = NULL;
		(*lista)->prox = novo; 
		if(isMtf == 1){
			custoMtf += tamanhoMtf + 1;
		}
	}else{
		Lista *aux = (*lista)->prox;
		adicionarElemento(numero, &aux, isMtf);
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
	tamanhoMtf = n;
	for(int i = 0; i < n; i++){
		scanf(" %d", &numero);
		if(i == 0){
			adicionarPrimeiroElemento(numero, &mtf);
			adicionarPrimeiroElemento(numero, &tr);
		}else{
			adicionarElemento(numero, &mtf, 0);
			adicionarElemento(numero, &tr, 0);
		}
	}
	for(int i = 0; i < r; i++){
		scanf(" %c %d", &requisicao, &numero);
		i == 0 ? adicionarPrimeiraRequisicao(requisicao, numero, &listaRequisicao) : adicionarRequisicao(requisicao, numero, &listaRequisicao);
	} 

}

void removerItem(Lista **lista, int item, int isMtf){
	Lista *aux = *lista;
	int controle = 1; 
	while(aux != NULL){ 
		Lista *auxiliarProx = aux->prox;
		if(auxiliarProx->dado == item){
			aux->prox = auxiliarProx->prox;
			free(auxiliarProx);
			if(isMtf == 1){
				if(controle == 1){
					custoMtf += 2;
				}else{
					custoMtf += controle + 1; 
				}
			}
			break;
		}else if(aux->dado == item){
			*lista = aux->prox;
			free(aux);
			custoMtf += controle; 
			break;  	
		}else{
			aux = aux->prox;
			++controle;
		}
	}
}

void moverParaFrente(Lista **lista, int item, int isMtf){
	Lista *aux = *lista;
	int controle = 1;
	while(aux != NULL){
		Lista *auxiliarProx = aux->prox;
		if(auxiliarProx->dado == item){
			if(isMtf == 1){
				aux->prox = auxiliarProx->prox;
				auxiliarProx->prox = *lista;
				*lista = auxiliarProx;
				if(controle == 1){
					custoMtf += 2;
				}else{
					custoMtf += controle + 1;
				}
			}
			break;
		}else if(aux->dado == item){
			if(isMtf == 1){
				custoMtf += 1;
			}
			break;
		}else{
			++controle;
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

void moverParaProximo(Lista **listaTr, int elemento){
	Lista *aux = *listaTr;
	int find = 0;
	int controle = 0;
	while(aux != NULL && find == 0){
		++controle;
		if(aux->dado == elemento && controle == 1){
			custoTr += 1;
			find = 1;
			break;
		}else{
			Lista *proximo = aux->prox;
			if(proximo != NULL){
				if(proximo->dado == elemento){
					aux->prox = proximo->prox;
					proximo->prox = aux;
					*listaTr = proximo;					
					find = 1;
					break;
				}
				Lista *proxDoProx = proximo->prox;
				if(proxDoProx != NULL){
					if(proxDoProx->dado == elemento){
						aux->prox = proxDoProx;
						proximo->prox = proxDoProx->prox;
						proxDoProx->prox = proximo;
						find = 1;
						break;
					}
				}
			} 
		}
		aux = aux->prox;
	}
}

void executarMtf(Lista *lista, Lista *listaTr, Requisicao **requisicao){
	Requisicao *aux = *requisicao;
	Lista *auxLista = lista;
	Lista *auxTr = listaTr;
	while(aux != NULL){
		switch(aux->tipo){ 
			case 'a': //printf("Movendo para frente %d\n", aux->elemento);
				moverParaFrente(&auxLista, aux->elemento, 1);
				imprimir(&auxLista);
				printf("\t Custo %d \t", custoMtf);
				moverParaProximo(&auxTr, aux->elemento);
				imprimir(&auxTr);
				printf("\t Custo \n");
				break;
			case 'i': //printf("Inserindo no fim..");
				adicionarElemento(aux->elemento, &auxLista, 1);
				imprimir(&auxLista);
				printf("\t Custo %d \n", custoMtf);
				break;
			case 'r': removerItem(&auxLista, aux->elemento, 1);
				  imprimir(&auxLista);
				  printf("\t Custo %d \n", custoMtf);
				  break;
		}
		aux = aux->prox;
	}
}

int main(){
	leituraItens();
	executarMtf(mtf, tr, &listaRequisicao);
	return 0;
}
