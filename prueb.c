#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>

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

int main(int argc, char const *argv[])
{
	char comando[10];
	char linea[20];
    char nombreArchivo[15]="";
	int cont=1;
    FILE *fich;

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
    fich = fopen("file", "r");
        while(fgets(linea, 20, (FILE*) fich)) {
        printf("%d: %s\n", cont, linea);
        cont++;
        }  
    fclose(fich);
    }
    if(strcmp(comando,"salir") == 0){
        endwin();
        exit(0);
    }}

	return 0;
}