
#include<stdio.h>
#include<curses.h>
#include<stdlib.h>
#include<unistd.h>
void funcion(){
		mvprintw(2,1,"MUEVE ALGO");


}
/******
Andrés Huerta
*****/
void menu_responsivo(){
	int x,y;
	getmaxyx(stdscr,y,x);
	move(1,0);
	hline('$',x);
	move(y/2,0);
	hline('$',x);

}
int main(void){
	WINDOW * principal;
	
	
	initscr();
	principal = newwin(0,0,0,0);

	if(principal==NULL){
		addstr("imposible crear nueva ventana");
		endwin();
		return (1);
	}	
	
	menu_responsivo();
	funcion();
	
	mvprintw(3,2,"cancion reproduciendo...");
	refresh();
	usleep(1000000);
	clear();
	funcion();
	menu_responsivo();
	refresh();
	waddstr(principal,"Bienvenidos a un nuevo mundo");
	wrefresh(stdscr);
	wrefresh(principal);
	getch();


	endwin();
	return 0;
}
