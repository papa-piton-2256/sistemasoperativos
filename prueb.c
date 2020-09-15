#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>

/*Definicion de variables globales*/
int EAX=0,EBX=0,ECX=0,EDX=0;
int PC=0;
char IR[100];
char codop[2];
char reg1[2];
char reg2[2];


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

void asignar(char codop[],char registro1[],char regis2[]){
    PC+=1;
	printf("\r%d\t%s\n",PC,IR);
    printf("Tokens:(%s)(%s)(%s)\n",codop,registro1,regis2);
    
    /*if(strcmp(codop,"END")==0){
        printf("\n");
    }*/

}

int recibelinea(char *linea){ 
	char codop[3];char instru[3];
	char registro1[3];char re1[3];
	char registro2[3];char regis2[10];

	int longline=strlen(linea);
    int cuenta;int cuenta2=0;
    for(cuenta=0;cuenta<longline-1;cuenta++){
        if(cuenta<=7){
        }else{
        regis2[cuenta2]=linea[cuenta];
        cuenta2++;  
        }   
    }
	sscanf(linea,"%3s",codop);
	//printf("\n\r%s",codop);	
	//if(strcmp(codop,"MOV")==0||strcmp(codop,"ADD")==0||strcmp(codop,"SUB")==0||strcmp(codop,"MUL")==0||strcmp(codop,"DIV")==0){
	linea+=4;	
	fflush(stdin);
	sscanf(linea,"%3s",registro1);
    //printf("\n\r%s",registro1);
    /*linea+=4;
    fflush(stdin);
    sscanf(linea,"%3s",registro2);*/
 
	if(strcmp(codop,"DEC")!=0&&strcmp(codop,"INC")!=0&&strcmp(codop,"END")!=0){
	strcpy(IR, codop); 
	strcat(IR, " ");
    strcat(IR, registro1);
    strcat(IR, ",");
    strcat(IR, regis2);
    }else{
    	if(strcmp(codop,"END")==0){
            registro1[0]='\0';
        }
    strcpy(IR, codop); 
	strcat(IR, " ");
    strcat(IR, registro1);
    }
    
    asignar(codop,registro1,regis2);

	int lon=strlen(codop);
	int lon2=strlen(registro2);
	int i=0,f=0;
	while(i<lon){
		instru[i]=codop[i];
		i++;
	}
	while(f<lon){
		re1[f]=registro1[f];
		f++;
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

            printf("\n\n\rPC\tIR\t\tEAX\tEBX\tECX\tEDX\n");
  			printf("\r------------------------------------------------------\n");
            while(feof(archivo)==0){
          	fgets(linea,50,archivo); 
          	recibelinea(linea);
          	sleep(1);
          	}
          	 fclose(archivo);
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
