#include<stdio.h>

int main(){
	char* arreglo[5][10];
	int i=0;
	for(i=0;i<5;i++)
		fgets(*arreglo[i],10,stdin);
	
	for(i=0;i<5;i++){
		printf("%s",*arreglo[i]);
	}
}
