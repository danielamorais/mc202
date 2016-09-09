#include <stdlib.h>
#include <stdio.h> 

typedef struct Pessoa {
	int idPessoa; 
	int codPartido; 
	int statusResposta; //0 para não respondeu e 1 para respondeu
} Pessoa;

typedef struct No {
	Pessoa p;
	struct No *prox; 
} No; 

Pessoa lerPessoa(){
	Pessoa pessoa; 
	printf("Digite a identidade\n");
	scanf("%d", &pessoa.idPessoa);
	printf("Digite o codigo do partido\n");
	scanf("%d", &pessoa.codPartido);
	return pessoa;
}

void inicializarLista(No **lista){
	*lista = NULL;
}

void adicionarPrimeiroElemento(Pessoa pessoa, No **lista){
	No *novoElemento;
	novoElemento = malloc(sizeof(No));
	if (novoElemento == NULL){
		printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
		exit(1);
	}
	novoElemento->p = pessoa;
	novoElemento-> prox = *lista;
	*lista = novoElemento;
}

void adicionarElemento(Pessoa pessoa, No **lista){
	if((*(*lista)).prox == NULL){
		No *novoElemento;
		novoElemento = malloc(sizeof(No));
		if (novoElemento == NULL){
			printf("Erro ao inserir novo elemento! Problema ao alocar memoria");
			exit(1);
		}
		novoElemento->p = pessoa; 
		novoElemento-> prox = NULL; 
		(*(*lista)).prox = novoElemento; //Ira apontar para o primeiro elemento
	}else{
		No *aux = (*(*lista)).prox;
		adicionarElemento(pessoa, &aux);
	}
}





int main(){
	int controle = 0;
	No *lista;
	inicializarLista(&lista);
	Pessoa pessoa = lerPessoa(); 
	adicionarPrimeiroElemento(pessoa, &lista);
	printf("\nDigite 1 apos finalizar o cadastro para sair\n");
	while(controle != 1){
		pessoa = lerPessoa();
		adicionarElemento(pessoa, &lista);
		scanf("%d", &controle);
	}
	//Exibir valores
	No *atual;
	atual = lista;
	while(atual != NULL){
		printf("ID %d\n", (atual->p).idPessoa);
		atual = atual->prox;
	}
	return 0;
}
