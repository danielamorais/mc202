#include <stdlib.h>
#include <stdio.h>

float potencia(float x, int n){
	float r;
	if(n ==1){
		return x;
	}
	if (n % 2 == 1){
		r = potencia(x, (n-1)/2);
		printf("retornando 2 multiplciacoes\n");
		return x*r*r;
	}else{
		r = potencia(x, n/2);
		printf("retornando 1 multiplicacao\n");
		return r*r;
	}
}

int main(){
	printf("%f", potencia(1.0, 3));
	return 0;
}
