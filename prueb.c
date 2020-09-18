#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
#include <unistd.h>
//pruebita
//agregue comentarios
/*Definicion de variables globales*/
int EAX=0,EBX=0,ECX=0,EDX=0;
int PC=0;
char IR[100];
char codop[2];
char reg1[2];
char reg2[2];

void menu_responsivo(){
        int x,y;
        getmaxyx(stdscr,y,x);
        move(1,0);
        hline('$',x);
        move(y/2,0);
        hline('$',x);
	move(2,1);
	refresh();
}


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


	char codop[4], instru[4], registro1[4], re1[4], registro2[4],regis2[11];

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
    char comando[10],linea[20],nombreArchivo[15]="",respuesta[2];
    int cont=1,y,x;
 
    FILE *archivo;
    
    initscr();
    keypad(stdscr,TRUE);
    menu_responsivo();
    getmaxyx(stdscr,y,x);
    int pad=strlen("(ejecutar/salir)>");
	 
   while( strcmp(comando, "salir") != 0){
       
	 mvprintw(2,x/2,"(ejecutar/salir)>");  
         refresh();  
     	
	if(kbhit()){
            mvscanw(2,x/2+pad,"%s %s",comando,nombreArchivo); 
            mvprintw(2,x/2,"(ejecutar/salir)>");  
            move(1,20);  
            refresh();
         }

    	else if(strcmp(comando,"ejecutar") == 0){
    		archivo = fopen(nombreArchivo, "r");
        	if(archivo == NULL){
            clear();
            menu_responsivo();
            mvprintw(1,1,"No se pudo abrir el archivo %s\n",nombreArchivo);
            mvprintw(2,1,"Desea abrir otro archivo?(S/N)"); 
            move(2,34);
            refresh();  
            mvscanw(2,34,"%s",respuesta);
          
            	if(strcmp(respuesta,"N")==0){
                	endwin();
			exit(0);
			break;
            	}else{
            	clear();
            	refresh(); 
            	strcpy(comando," ");
            	strcpy(nombreArchivo," ");
            	}
		}
            

	menu_responsivo();
            while(feof(archivo)==0){
          	if(!kbhit()){
		fgets(linea,50,archivo); 
          	recibelinea(linea);
          	sleep(1);
		}else{
		mvscanw(2,x/2+pad,"%s %s",comando,nombreArchivo); 
            mvprintw(2,x/2,"(ejecutar/salir)>");  
            move(1,20);  
            refresh();
		}
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
