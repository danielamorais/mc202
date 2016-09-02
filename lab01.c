/* 
Daniela Marques de Morais - 169562
Programa para calcular a multiplicação entre matrizes 
*/

#include <stdio.h>

FILE *arquivoA, *arquivoB;

typedef struct matriz {
	int linha; 
	int coluna;
	int **dados; 
	FILE *arquivo; 
} Matriz; 

FILE * abrirArquivo(char *nome){
	FILE *arquivo;
	arquivo = fopen(nome, "r");
	if(arquivo == NULL){
		perror("Erro ao abrir arquivo:");
		return NULL; //fixme 
	}else{
		return arquivo; 
	}
}

Matriz lerMatriz(Matriz *matriz){
	int conteudo = 0;
	int contadorLinhas = 0;   
	while(fscanf(matriz->arquivo, "%d", &conteudo) != EOF){
		++contadorLinhas;
		switch(contadorLinhas){
			case 1: matriz->linha = conteudo;
				break;
			case 2: matriz->coluna = conteudo;
				int *linha = (int *) malloc(matriz->linha * sizeof(int));
				for(int i =0; i < matriz->coluna; i++){
					linha[i] = (int *) malloc(matriz->coluna * sizeof(int);		
				}
				matriz->dados = linha; 
				break;
			default:
				
				break;  
		}
	}
	printf("Linha %d: ", matriz.linha);
	printf("Coluna %d: ", matriz.coluna);
	return matriz; 
}

void main(){
	Matriz matrizA;
	Matriz matrizB;
	matrizA.arquivo = abrirArquivo("matrizA.txt");
	matrizB.arquivo = abrirArquivo("matrizB.txt");
	if(matrizA.arquivo != NULL && matrizB.arquivo != NULL){
		lerMatriz(matrizA.arquivo);
		lerMatriz(matrizB.arquivo);
		printf("Deu certo!\n");
		fclose(matrizA.arquivo);
		fclose(matrizB.arquivo);		 
	}else{
		printf("Erro ao acessar arquivo!");
	}
}
