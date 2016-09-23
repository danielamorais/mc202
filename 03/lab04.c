#include <stdio.h>
#include <stdlib.h>

typedef struct Brinquedo{
	int valor;
	struct Brinquedo *prox;
	int cor; //0 vermelho e 1 azul
} Brinquedo; 

typedef struct Resultado{
	int item; 
	int cor; 
	struct Resultado *prox; 
} Resultado;

int tamanho = 0;
int primeiroNumero = 0;
int ultimoNumero = 0;

void inicializarPilha(Brinquedo **pilha){
	*pilha = NULL;
}

void inicializarLista(Resultado **lista){
	*lista = NULL;
}

/* *
 * Destruir toda a pilha e liberar memoria 
 * */
void liberarMemoriaPilha(Brinquedo **pilha){
	Brinquedo *atual, *proximoElemento; 
	proximoElemento = *pilha; //Irá apontar para o primeiro elemento
	while(proximoElemento != NULL){
		atual = proximoElemento;
		proximoElemento = atual->prox;
		free(atual);
	}
}

/* *
 * Destruir toda a lista e liberar memoria 
 * */
void liberarMemoriaLista(Resultado **lista){
	Resultado *atual, *proximoElemento; 
	proximoElemento = *lista; //Irá apontar para o primeiro elemento
	while(proximoElemento != NULL){
		atual = proximoElemento;
		proximoElemento = atual->prox;
		free(atual);
	}
}

//Retornar 1 para caso seja invalido, 0 para caso seja possivel inserir 
int verificarItemLista(Resultado **lista, int item, int cor){
	Resultado *aux = *lista;
	while(aux != NULL){
		if(aux->item == item){
			if(aux->cor != cor){
				return 1; 
			}	
			return 2; 
		}
		aux = aux->prox;	
	}
	return 0; 
}

void adicionarElemento(Brinquedo **pilha, int valor){
	Brinquedo *novoElemento = malloc(sizeof(Brinquedo));
	if(novoElemento == NULL){
		printf("Erro ao inserir novo elemento!");
		exit(1);
	}
	novoElemento->valor = valor;
	novoElemento->prox = *pilha;
	novoElemento->cor = 0; //Inicializa como zero para nao haver problemas no calculo
	*pilha = novoElemento; 
}

void imprimirLista(Resultado **lista){
	Resultado *aux = *lista;
	while(aux != NULL){
		if(aux->cor == 0)
			printf("%d: vermelho \n", aux->item);
		else
			printf("%d: azul \n", aux->item);
		aux = aux->prox;
	}
}

void lerEntrada(Brinquedo **pilha){
	int numero; 
	char proxChar;
	scanf("%d", &tamanho);
	int k = 0;
	while(scanf("%d%c", &numero, &proxChar) == 2){
		++k; 		
		adicionarElemento(pilha, numero);
		if(k == 1){
			primeiroNumero = numero;
		}
		if(proxChar == '\n' || proxChar == '\r'){
			ultimoNumero = numero; 			
			break;		
		}
	}
}

void removerElemento(Brinquedo **pilha){
	Brinquedo *aux = *pilha;
	*pilha = aux->prox;
	free(aux);	
}

//Verifica se a sequencia eh invalida, isto eh: Foi aberto e fechado o brinquedo
int validarMatrioshka(Brinquedo **pilha){
	Brinquedo *aux = *pilha; 
	Brinquedo *pilhaTemporaria;
	inicializarPilha(&pilhaTemporaria);
	while(aux != NULL){
		if(aux->valor >= 0){
			adicionarElemento(&pilhaTemporaria, aux->valor);
		}else if(pilhaTemporaria != NULL){
			if((*pilhaTemporaria).valor == ((aux->valor) * (-1))){
			 	removerElemento(&pilhaTemporaria);
			}
		}else{
			return 0;
		}
		aux = aux->prox;
	}	
	if(pilhaTemporaria == NULL){
		return 1;
	}
	return 0;
}

//0 para vermelho 1 para azul
int getCor(int valor){
	if(valor % 2 == 0){
		return 1;
	}
	return 0; 
}

int contarElementosLista(Resultado **lista){
	Resultado *aux = *lista;
	int i = 0;
	while(aux != NULL){
		++i;
		aux = aux->prox; 
	}
	return i;
}

/*
 * Lista com o elemento com a respectiva cor ordenados 
 */
void adicionarElementoLista(Resultado **lista, int item, int cor){
	Resultado *novoElemento = malloc(sizeof(Resultado));
	if(novoElemento == NULL){
		printf("Erro ao inserir novo elemento!");
		exit(1);
	}
	novoElemento->item = item;
	novoElemento->cor = cor; 
	novoElemento->prox = *lista;
	*lista = novoElemento; 	
}

void ordenarVetor(Resultado vetor[], int tamanho){
	int i, j;
	Resultado aux;
        for(i=tamanho-1; i >= 1; i--){  
		for(j=0; j < i ; j++){
			if(vetor[j].item > vetor[j+1].item){
				aux = vetor[j];
				vetor[j] = vetor[j+1];
				vetor[j+1] = aux;
			}
		}
	}          
}

void calcularCor(Brinquedo **pilha){
	Brinquedo *pilhaTemporaria;
	inicializarPilha(&pilhaTemporaria);
	Brinquedo *aux = *pilha; 
	Resultado *lista; 
	inicializarLista(&lista);

	while(aux != NULL){
		if(aux-> valor >= 0){
			adicionarElemento(&pilhaTemporaria, aux->valor);
		}else if(pilhaTemporaria->prox != NULL){
			Brinquedo *anotherAux = pilhaTemporaria->prox; 
			anotherAux->cor = getCor(aux->valor + pilhaTemporaria->cor + anotherAux->cor);
			Brinquedo *atual = pilhaTemporaria;
			atual->cor = getCor(atual->cor + atual->valor);
			pilhaTemporaria = pilhaTemporaria->prox;
			int statusLista = verificarItemLista(&lista, atual->valor, atual->cor);
			if(statusLista == 0){
				adicionarElementoLista(&lista, atual->valor, atual->cor);
				free(atual);
			}else if(statusLista == 1){
				printf("sequencia invalida ou nao pode colorir");
				free(atual);
				return ;
			}
		}else{
			pilhaTemporaria->cor = getCor(aux->valor + pilhaTemporaria->cor);
			Brinquedo *atual = pilhaTemporaria;
			int statusLista = verificarItemLista(&lista, atual->valor, atual->cor);
			if(statusLista == 0){
				adicionarElementoLista(&lista, atual->valor, atual->cor);
			}else if(statusLista == 1){
				printf("sequencia invalida ou nao pode colorir");
				return ;
			}
			break;
		}
		aux= aux -> prox;
	}
	int n = contarElementosLista(&lista);
	Resultado vetor[n];
	//imprimir vetor
	Resultado *myAux = lista;
	for(int i = 0; i < n; i++){
		if(myAux == NULL){
			break; 
		}
		vetor[i] = *myAux;
		myAux = myAux->prox;
	}
	ordenarVetor(vetor, n);
	//imprimir
	printf("sequencia valida pode ser colorida\n");
	for(int i = 0; i < n; i++){
		if(vetor[i].cor == 1){
			printf("%d: azul\n", vetor[i].item);
		}else{
			printf("%d: vermelho\n", vetor[i].item);
		}
	}
  	liberarMemoriaLista(&lista);
}

int main(){
	Brinquedo *pilha;
	inicializarPilha(&pilha);
	lerEntrada(&pilha);
	if(primeiroNumero == (ultimoNumero * (-1)) && validarMatrioshka(&pilha) == 1){
		calcularCor(&pilha);
	}else{
		printf("sequencia invalida ou nao pode colorir");
	}
	liberarMemoriaPilha(&pilha);
	return 0;
}
