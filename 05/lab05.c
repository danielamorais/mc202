#include <stdio.h>
#include <stdlib.h>

typedef struct ArvoreArquivo{
	char[20] nome;
	int quantidade;
	struct ArvoreArquivo *esq, *dir;
	enum { MENOS, ZERO, MAIS } fator;
} *ArvoreArquivo; 

void iniciarArvore(ArvoreArquivo **raiz){ 
	*raiz = NULL; 
} 

//TODO
void destruirArvore(ArvoreArquivo **raiz){

}

int main(){ 
	return 0; 
}
