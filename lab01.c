#include <stdio.h>

FILE *arquivoA, *arquivoB;
//int conteudo;
//int linhaA, linhaB, colunaA, colunaB;  

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

Matriz lerMatriz(FILE *arquivo){
	int conteudo = 0;
	int contadorLinhas = 0; 
	Matriz matriz;  
	while(fscanf(arquivo, "%d", &conteudo) != EOF){
		++contadorLinhas;
		//printf("%d \n", conteudo);
		switch(contadorLinhas){
			case 1: matriz.linha = conteudo;
				break;
			case 2: matriz.coluna = conteudo;
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
		/		/*  */  
			//		int contPrimeiraLinha = 0; 
			//		int contPrimeiraColuna = 0; 
			//		while(fscanf(arquivoA, "%d", &conteudo) != EOF){
			//			printf("%d", conteudo);
			//
			//			++contPrimeiraLinha;
			//			++contPrimeiraColuna; 
			//			   printf("Coluna: %d Character: %d", contPrimeiraColuna, conteudo); 
			//			   if(contPrimeiraColuna == 3){
			//			   printf("Entao a linha eh %d", contPrimeiraLinha); 
			//			   }
			//			   
			//			if(contPrimeiraLinha == 1){
			//				if (contPrimeiraColuna == 1){
			//					linhaA = (int) conteudo;
			//				} else if(contPrimeiraColuna == 3){
			//					printf("entrou aqui"); 
			//					colunaA = (int) conteudo;
			//				}
			//			}
			//
			//		}
			printf("Linha A %d \n", linhaA);
		printf("Coluna A %d \n", colunaA);

		printf("Deu certo!\n");
		*/
			fclose(matrizA.arquivo);
		fclose(matrizB.arquivo);		 
	}else{
		printf("Erro ao acessar arquivo!");
	}
}
