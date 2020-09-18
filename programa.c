#include<ncurses.h>
#include<unistd.h>
void menu(){
	mvprintw(10,10,"PC IR EAX EBX ECX EDX");
	refresh();
}

int main(){
	
	int pc,ir,eax,ebx,ecx,edx;
	pc =ir=eax=ebx=ecx=edx=0;
	
	
	initscr();
	menu();
	mvprintw(11,10,"%d  %d  %d   %d   %d   %d",pc,ir,eax,ebx,ecx,edx);
	refresh();
	sleep(5);
	clear();
	menu();
	pc++,ir++,eax++,ebx++,ecx++,edx++;
	menu();
	mvprintw(11,10,"%d  %d  %d   %d   %d   %d",pc,ir,eax,ebx,ecx,edx);
	refresh();
	sleep(3);
	endwin();
		
	
	return 0;
}
