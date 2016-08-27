#include <stdio.h>

FILE *arquivoA, *arquivoB;
int conteudo;
int linhaA, linhaB, colunaA, colunaB;  
void main(){
		arquivoA = fopen("matrizA.txt", "r");
		if(arquivoA == NULL){
				perror("matrizA.txt:");
		}
		arquivoB = fopen("matrizB.txt", "r");
		if(arquivoB == NULL){
				perror("matrizB.txt:");
		}else{
				int contPrimeiraLinha = 0; 
				int contPrimeiraColuna = 0; 
				while(fscanf(arquivoA, "%d", &conteudo) != EOF){
						printf("%d", conteudo);
						
						++contPrimeiraLinha;
						++contPrimeiraColuna; 
						/* printf("Coluna: %d Character: %d", contPrimeiraColuna, conteudo); 
						if(contPrimeiraColuna == 3){
								printf("Entao a linha eh %d", contPrimeiraLinha); 
						}
						*/
						if(contPrimeiraLinha == 1){
								if (contPrimeiraColuna == 1){
										linhaA = (int) conteudo;
								} else if(contPrimeiraColuna == 3){
										printf("entrou aqui"); 
										colunaA = (int) conteudo;
								}
						}
						 
				}
				printf("Linha A %d \n", linhaA);
				printf("Coluna A %d \n", colunaA); 
				fclose(arquivoA);
				fclose(arquivoB);		 
		}
}
