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
	int tamanho; 
	scanf("%d", &tamanho);
	
	while(scanf("%d%c", &numero, &proxChar) == 2){
		adicionarElemento(pilha, numero);
		if(proxChar == '\n' || proxChar == '\r')
			break;
	}
}

void removerElemento(Brinquedo **pilha){
	Brinquedo *aux = *pilha;
	*pilha = aux->prox;
	free(aux);	
}

//Verifica se a sequencia eh invalida, isto eh: Foi aberto e fechado o brinquedo
void validarMatrioshka(Brinquedo **pilha){
	Brinquedo *aux = *pilha; 
	Brinquedo *pilhaTemporaria;
	printf("Inicializando lista...\n");
	inicializarLista(&pilhaTemporaria);
	while(aux != NULL){
		printf("Entrei no while!\n");
		if(aux->valor >= 0){
			printf("Adicionado elemento positivo.. %d \n", aux->valor);
			adicionarElemento(&pilhaTemporaria, aux->valor);
		}else{
			if((*pilhaTemporaria).valor == ((aux->valor) * (-1))){
			 	//Removera item da lista temporaria
			 	printf("Removendo.. %d \n", (aux->valor) * (-1));
				removerElemento(&pilhaTemporaria);
			}else{
				printf("Erro! %d nao eh igual a %d", (*pilhaTemporaria).valor, aux->valor);
			}
		}
		aux = aux->prox;
	}	
	printf("Validando listaTempo....\n");
	//Se lista temporaria for vazia, entao a lista eh valida
	if(pilhaTemporaria == NULL){
		printf("\nValido!");
	}else{
		printf("\nINVALIDO");
	}
}

int main(){
	Brinquedo *pilha;
	inicializarLista(&pilha);
	lerEntrada(&pilha);
	imprimirPilha(&pilha);
	validarMatrioshka(&pilha);
	return 0;
}
