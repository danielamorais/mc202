#include <stdlib.h>
#include <stdio.h>

int main(){
	int num[5];
	int numero;
	char next_char;
	int i = 0;
	while (scanf("%d%c", &numero, &next_char) == 2) {
    		//printf("%d", numero);
		num[i] = numero;
		i++;
		if (next_char == '\n') break;
	}

	for(int j = 0; j < 5; j++){
		printf("%d", num[j]);
	}
	return 0;
}
