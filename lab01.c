/* 
   Daniela Marques de Morais - 169562
   Programa para calcular a multiplicação entre matrizes 
   */

#include <stdio.h>
#include <stdlib.h>

typedef struct matriz {
	int linha; 
	int coluna;
	int **dados; 
	FILE *arquivo; 
} Matriz; 

void imprimeMatriz(Matriz *matriz){
	printf("%d %d \n", matriz->linha, matriz->coluna);
	for(int i = 0; i < matriz->linha; i++){
		for(int j = 0; j < matriz->coluna; j++){
			printf("%d ", matriz->dados[i][j]);
		}
		printf("\n");
	}

}


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
		}
	}	
}

/* Verifica se é possível a multiplicação da matriz e realiza o calculo */
void multiplicarMatriz(Matriz *matrizA, Matriz *matrizB){
	if(matrizA->coluna != matrizB->linha){
		printf("As matrizes nao seguem as propriedades necessarias para realizar a multiplicacao.");
	} else{
		Matriz resultado; 
		//Alocar matriz resultado baseado na linha e coluna das matrizes 
		resultado.linha = matrizA->linha;
		resultado.coluna = matrizB->coluna;
		resultado.dados = (int **) malloc(resultado.linha * sizeof(int *));

		for(int i = 0; i < matrizA->coluna; i++){
			resultado.dados[i] = (int *) malloc(resultado.coluna * sizeof(int));
		}
		//Executam multiplicao e insere na matriz resultado
		for(int linha = 0; linha < matrizA->linha; ++linha){
			for(int coluna = 0; coluna < matrizB->coluna; ++coluna){
				for(int aux = 0; aux < matrizA->coluna; ++aux) {
					resultado.dados[linha][coluna] = resultado.dados[linha][coluna] + matrizA->dados[linha][aux] * (matrizB->dados[aux][coluna]);
				}
			}
		}
		imprimeMatriz(&resultado);
	}
}

void liberarMemoria(Matriz *matriz){
	for(int i = 0; i < matriz->linha; i++){
		free(matriz->dados[i]);
	}
	free(matriz->dados);
}

int main(){
	Matriz matrizA;
	Matriz matrizB;
	abrirArquivo("matrizA.txt", &matrizA);
	abrirArquivo("matrizB.txt", &matrizB);
	if(matrizA.arquivo != NULL && matrizB.arquivo != NULL){
		lerMatriz(&matrizA);
		lerMatriz(&matrizB);
		multiplicarMatriz(&matrizA, &matrizB);
		liberarMemoria(&matrizA);
		liberarMemoria(&matrizB);
		fclose(matrizA.arquivo);
		fclose(matrizB.arquivo);
	}else{
		printf("Erro ao acessar arquivo!");
	}
	return 0;
}
