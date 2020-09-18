#include<stdio.h>
#include<string.h>
#include<ncurses.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
int EAX=0,EBX=0,ECX=0,EDX=0;
int PC=0;
char IR[100];
char* codop=NULL;
char* reg1=NULL;
char* reg2=NULL;



void menu_responsivo(){
        int x,y;
        getmaxyx(stdscr,y,x);
        move(1,0);
        hline('$',x);
	move(2,0);
	printw("PC	IR	EAX   EBX   ECX   EDX");
        move(y/2,0);
        hline('$',x);
        move(2,1);
        refresh();
}
void asignar(){

	if(!strcmp("END",codop)){
		mvprintw(11,10,"voy a mover algo ");
		refresh();
	}
	codop=NULL;
	reg1=NULL;
	reg2=NULL;

}

void tokenizar(char** lectura){
	int count=0;


	//Extraemos primer token lo pasamos a base
	char* base=strtok(*lectura," \n");	
	codop=base;
	
	//Extraemos el segundo token 
	base=strtok(NULL," ,\n");
	//Revisamos si obtuvimos el segundo token, (podría haber uno ex. END)
	if(base!=NULL){
		reg1=base;
	}
	//Extraemos tercer token 
	base=strtok(NULL," ,\n");
	if(base!=NULL){
		reg2=base;
	}
	asignar();
}
int main(){

	initscr();
	menu_responsivo();
	FILE * arch;
	arch = fopen("file","r");
	size_t tam =11;	
	char* lectura=NULL;

	while(getline(&lectura,&tam,arch)!=-1){

	tokenizar(&lectura);
	
	}
	getch();
	endwin();

	fclose(arch);

	return 0;
}
