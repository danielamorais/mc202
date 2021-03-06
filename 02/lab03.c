/* *
* Daniela Marques de Morais - 169562
* MC202 - Lab 02: Listas 
* */

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
int tamanhoTr = 0;

void inicializarLista(Lista **lista){
	*lista = NULL;	
}

void inicializarListaRequisicao(Requisicao **lista){
	*lista = NULL;
}

/* *
* Adiciona elemento no fim da lista e realiza calculo se foi enviado por um comando da lista de requisicao (a) 
* */
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
			tamanhoMtf += 1;

			custoMtf += tamanhoMtf;
		}else if(isMtf == 0){
			tamanhoTr += 1;
			custoTr += tamanhoTr;
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

/* *
* Adiciona item da requisicao (a, i ou r) na lista de requisicao
* */
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

/* *
* Efetua leitura de itens e executa os respectivos algoritmos (tr ou mtf)
* */
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
	tamanhoTr = n;
	for(int i = 0; i < n; i++){
		scanf(" %d", &numero);
		if(i == 0){
			adicionarPrimeiroElemento(numero, &mtf);
			adicionarPrimeiroElemento(numero, &tr);
		}else{
			adicionarElemento(numero, &mtf, 2);
			adicionarElemento(numero, &tr, 2);
		}
	}
	for(int i = 0; i < r; i++){
		scanf(" %c %d", &requisicao, &numero);
		i == 0 ? adicionarPrimeiraRequisicao(requisicao, numero, &listaRequisicao) : adicionarRequisicao(requisicao, numero, &listaRequisicao);
	} 

}

/* *
* Remove item e realiza o respectivo calculo do custo se eh MTF ou TR  
* */
void removerItem(Lista **lista, int item, int isMtf){
	Lista *aux = *lista;
	int controle = 1; 
	if(tamanhoMtf == 1){
		tamanhoMtf -= 1;
		custoMtf += 1;
		return ; 
	}
	if(tamanhoTr == 1){
		tamanhoTr -= 1;
		custoTr += 1;
		return ;
	}
	while(aux != NULL){ 
		Lista *auxiliarProx = aux->prox;
		if(auxiliarProx->dado == item){
			aux->prox = auxiliarProx->prox;
			free(auxiliarProx);
			if(isMtf == 1){
				tamanhoMtf -= 1;
				if(controle == 1){
					custoMtf += 2;
				}else{
					custoMtf += controle + 1; 
				}
			}else{
				tamanhoTr -= 1;
				if(controle == 1){
					custoTr += 2;
				}else{
					custoTr += controle + 1;
				}
			}
			break;
		}else if(aux->dado == item){
			*lista = aux->prox;
			free(aux);
			if(isMtf == 1){
				tamanhoMtf -= 1;
				custoMtf += controle;
			}else{
				tamanhoTr -= 1;
				custoTr += controle;
			}
			break;  	
		}else{
			aux = aux->prox;
			++controle;
		}
	}
}

/* *
* Move item para a primeira posicao da lista e realiza o calculo do custo
* */
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

void imprimir(Lista **item, int tamanho){
	if(tamanho > 1){	
		Lista *aux = *item;
		while(aux != NULL){
			printf("%d ", aux->dado);
			aux = aux->prox;
		}
	}
}
/* *
* Especifico para o TR: Realiza troca de posicao de elemento. Essa funcao eh reaproveitada quando um novo elemento eh inserido, caso seja um novo elemento nao eh necessario calcular o custo de trocar de posicao. 
* */
void moverParaProximo(Lista **listaTr, int elemento, int novoElemento){
	Lista *aux = *listaTr;
	int find = 0;
	int controle = 1;
	while(aux != NULL && find == 0){
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
					if(novoElemento != 1)
						custoTr += controle + 1;
					break;
				}
				Lista *proxDoProx = proximo->prox;
				if(proxDoProx != NULL){
					if(proxDoProx->dado == elemento){
						aux->prox = proxDoProx;
						proximo->prox = proxDoProx->prox;
						proxDoProx->prox = proximo;
						find = 1;
						if(novoElemento != 1)
							custoTr += controle + 2;
						break;
					}
				}
			} 
		}
		++controle;
		aux = aux->prox;
	}
}

/* *
 * Destruir toda a lista e liberar memoria 
 * */
void liberarMemoria(Lista **lista){
	Lista *atual, *proximoElemento; 
	proximoElemento = *lista; //Irá apontar para o primeiro elemento
	while(proximoElemento != NULL){
		atual = proximoElemento;
		proximoElemento = atual->prox;
		free(atual);
	}
}

/* *
* Realiza leitura de lista que contem as requisicoes e chama os algoritmos (TF ou MTF) necessarios
* */
void executarMtf(Lista **lista, Lista **listaTr, Requisicao **requisicao){
	Requisicao *aux = *requisicao;
	Lista *auxLista = *lista;
	Lista *auxTr = *listaTr;
	while(aux != NULL){
		switch(aux->tipo){ 
			case 'a': 
				moverParaFrente(&auxLista, aux->elemento, 1);
				moverParaProximo(&auxTr, aux->elemento, 0);
				break;
			case 'i':
				adicionarElemento(aux->elemento, &auxLista, 1);
				adicionarElemento(aux->elemento, &auxTr, 0);
				moverParaProximo(&auxTr, aux->elemento, 1);
				break;
			case 'r': 
				  if(tamanhoMtf > 0){
				  removerItem(&auxLista, aux->elemento, 1);
				  }
				  if(tamanhoTr > 0){
				  removerItem(&auxTr, aux->elemento, 0);			 
				  }
				  break;
		}
		aux = aux->prox;
	}
	printf("%d\n", custoMtf);
	imprimir(&auxLista, tamanhoMtf);
	printf("\n%d\n", custoTr);
	imprimir(&auxTr, tamanhoTr);
	liberarMemoria(&auxLista);
	liberarMemoria(&auxTr);
}

int main(){
	leituraItens();
	executarMtf(&mtf, &tr, &listaRequisicao);
	return 0;
}
