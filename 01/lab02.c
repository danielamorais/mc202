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
	if(*lista == NULL){
		No *novoElemento;
		novoElemento = malloc(sizeof(No));
		if (novoElemento == NULL){
			printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
			exit(1);
		}
		novoElemento->dado = dado; 
		novoElemento-> prox = (*(*lista)).prox; 
		(*(*lista)).prox = &novoElemento; //Ira apontar para o primeiro elemento
	}else{
		printf("nao eh  IGual, irei acessar %d \n", (*(*lista)).dado);
		No *aux = (*(*lista)).prox;
		adicionarElemento(&aux, dado);
		/*  
		    while(*aux != NULL){
		    printf("entrando no while..%d \n", (*(aux->prox)).dado);
		    aux = (*(aux->prox)).prox;
		    }
		    printf("ultimo elemento.. %d\n", aux->dado);	 
		//Chegou no ultimo elemento
		novoElemento->prox = NULL;
		aux->prox = novoElemento;
		*/	
	}
	//novoElemento->prox = *lista; //Ira apontar para null 
	//*lista = novoElemento; //Ira apontar para novo elemento
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

void firstElement(No **lista, int dado){
	No *novoElemento;
	novoElemento = malloc(sizeof(No));
	if (novoElemento == NULL){
		printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
		exit(1);
	}
	novoElemento->dado = dado;
	printf("IGual a NULL\n");
	novoElemento-> prox = *lista;
	*lista = novoElemento;
}

int main(){
	No *lista, *atual;
	int dado;  
	inicializarLista(&lista);
	//Ler elemento
	char next_char;
	int number;

	while (scanf("%d%c", &number, &next_char) == 2) {
		/*  some stuff */
		++k;
		printf("acesso %d", k);
		if(k == 1){
			firstElement(&lista, number);
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
