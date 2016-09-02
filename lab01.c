/* 
   Daniela Marques de Morais - 169562
   Programa para calcular a multiplicação entre matrizes 

   Lembrar do casting, o ponteiro anda (fscanf) não há nenhum problema 
   */

#include <stdio.h>
#include <stdlib.h>


typedef struct matriz {
	int linha; 
	int coluna;
	int **dados; 
	FILE *arquivo; 
} Matriz; 

void abrirArquivo(char *nome, Matriz *matriz){
	matriz->arquivo = fopen(nome, "r");
	if(matriz->arquivo == NULL){
		perror("Erro ao abrir arquivo:");
	}
}

/* 
 * Alocar matriz dinamicamente, ler arquivo txt para preencher como elementos da matriz alocada
 *
 * */
void lerMatriz(Matriz *matriz){   
	fscanf(matriz->arquivo, "%d %d", &matriz->linha, &matriz->coluna);

	//Alocar matriz dinamicamente
	matriz->dados = (int **) malloc(matriz-> linha * sizeof(int *));
	int i = 0;
	for(i = 0; i < matriz->linha; i++){
		matriz->dados[i] = (int *) malloc(matriz->coluna * sizeof(int));
	}


	//Preencher elementos da matriz 
	for(int i = 0; i < matriz->linha; i++){
		for(int j = 0; j < matriz->coluna; j++){
			fscanf(matriz->arquivo, " %d", &matriz->dados[i][j]);
			printf("Lendo %d \n\n ", matriz->dados[i][j]);
		}
	}	

	//Exibir dados
	for(int i = 0; i < matriz->linha; i++){
		for(int j = 0; j < matriz->coluna; j++){
			printf("%d ", matriz->dados[i][j]);
		}
		printf("\n");
	}
}

void multiplicarMatriz(Matriz *matrizA, Matriz *matrizB, Matriz *resultado){
	//Alocar matriz resultado baseado na linha e coluna das matrizes 
	resultado->linha = matrizA->linha;
	resultado->coluna = matrizB->coluna;
	resultado->dados = (int **) malloc(resultado->linha * sizeof(int *));

	int *aux = (int *) malloc(resultado->linha * resultado->coluna * sizeof(int)); 
	for(int i = 0; i < matrizA->coluna; i++){
		resultado->dados[i] = (int *) malloc(resultado->coluna * sizeof(int));
	}
	int operacao = 0;
	//Executam multiplicao e insere na matriz resultado
	for(int i = 0; i < matrizA->linha; ++i){
		for(int j = 0; j < matrizB->coluna; ++j){
			for(int k = 0; k < matrizA->coluna; ++k) {
				resultado->dados[i][j] += matrizA->dados[i][k] * (matrizB->dados[k][j]);
			}
		}
	}

	//Exibir resultado
	 for(int i = 0; i < resultado->linha; i++){
                 for(int j = 0; j < resultado->coluna; j++){
                         printf("%d ", resultado->dados[i][j]);
                 }
                 printf("\n");
         }
	
}

int main(){
	Matriz matrizA;
	Matriz matrizB;
	Matriz resultado; 
	abrirArquivo("matrizA.txt", &matrizA);
	abrirArquivo("matrizB.txt", &matrizB);
	if(matrizA.arquivo != NULL && matrizB.arquivo != NULL){
		lerMatriz(&matrizA);
		lerMatriz(&matrizB);
		multiplicarMatriz(&matrizA, &matrizB, &resultado);
		//Liberar memoria
		//	printf("Tentando liberar...");	
		//	for(int i = 0; i < matrizA.linha; i++){
		//		free(matrizA.dados[i]);
		//	}
		//	printf("passou for..");
		//	free(matrizA.dados);
		fclose(matrizA.arquivo);
		fclose(matrizB.arquivo);
	}else{
		printf("Erro ao acessar arquivo!");
	}
	return 0;
}
