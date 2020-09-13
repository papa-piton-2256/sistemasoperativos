#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

/*Definicion de variables globales*/
int EAX,EBX,ECX,EDX;
int PC;
char IR[100];

int kbhit(void){
    struct timeval tv;
    fd_set read_fd;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&read_fd);
    FD_SET(0, &read_fd);
    
    if (select(1, &read_fd, NULL, NULL, &tv) == -1)    
        return 0;  
    if (FD_ISSET(0, &read_fd))                          
        return 1;  
    return 0;
}

void asignar(char codop[],char registro1[],char registro2[]){
  printf("\n");	
  char cod[3];
  char reg1[3];
  char reg2[3];
 
  sscanf(codop,"%2s",cod);
  sscanf(registro1,"%2s",reg1);
  sscanf(registro2,"%3s",reg2);
  printf("%s,%s,%s\n",cod,reg1,reg2);
}

int recibelinea(char *linea){ 
	char codop[3];
	char registro1[3];
	char registro2[3];

	sscanf(linea,"%3s",codop);
	printf("\n\r%s",codop);
	
	if(strcmp(codop,"MOV")==0||strcmp(codop,"ADD")==0){
	linea+=4;	
	sscanf(linea,"%3s",registro1);
    printf("\n\r%s",registro1);
    linea+=4;
    sscanf(linea,"%3s",registro2);
    printf("\n\r%s",registro2);
    asignar(codop,registro1,registro2);
	}	
	if(strcmp(codop,"INC")==0){
    linea+=4;	
	sscanf(linea,"%3s",registro1);
	sscanf("I","%s",registro2);
    asignar(codop,registro1,registro2);
	}
	if(strcmp(codop, "END") == 0){
		printf("\n");
	}
	return 0;
}

int main(int argc, char const *argv[]){
	
    char comando[10];
    char linea[20];
    char nombreArchivo[15]="";
	int cont=1;
	char respuesta[2];

    FILE *archivo;

    initscr();

    while(strcmp(comando, "salir") != 0){
        mvprintw(0,0,"(ejecutar/salir) ");  
        move(0,20);  
        refresh();  

        if(kbhit()){
            mvscanw(0,20,"%s %s",comando,nombreArchivo); 
            mvprintw(0,0,"(ejecutar/salir)");  
            move(0,20);  
            refresh();
        } 

    	if(strcmp(comando,"ejecutar") == 0){
    		archivo = fopen(nombreArchivo, "r");
        	if(archivo == NULL){
            clear();
            mvprintw(0,0,"No se pudo abrir el archivo %s\n",nombreArchivo);
            mvprintw(1,0,"Desea abrir otro archivo?(S/N)"); 
            move(1,33);
            refresh();  
            mvscanw(1,33,"%s",respuesta);
          
            	if(strcmp(respuesta,"N")==0){
                	endwin();
                	exit(0);
            	}else{
            	clear();
            	refresh(); 
            	strcpy(comando," ");
            	strcpy(nombreArchivo," ");
            	continue;
            	}
            } 

            while(feof(archivo)==0){
          	fgets(linea,50,archivo); 
          	recibelinea(linea);
          	sleep(1);
          	}
        strcpy(comando," ");
       	strcpy(nombreArchivo," ");
       	//clear();
        refresh();
    	}

    	if(strcmp(comando,"salir") == 0){
        endwin();
        exit(0);
    	}
	}
	return 0;
}
