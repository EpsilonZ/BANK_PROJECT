#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"
#include <unistd.h>
#include <termios.h>


char getch();

int main(int argc, char *argv[]){
	
	//TODO: ENCARGADO DE CREAR CUENTAS Y ACTUALIZARLAS SI EL CLIENTE QUIERE
	printf(GRN "Bienvenido al banco Epsilon\n\n" RESET);
	/*printf(MAG "Si quieres realizar operaciones apreta la tecla Y\n");
	printf(MAG "Si quieres crearte una nueva cuenta bancaria apreta la tecla N\n");
	printf(MAG "Si no quieres realizar nada mas apreta O\n");
	*/
	//si quiero realizar operaciones muto a cliente
	//si quiero crear cuenta escribo en cuentas.txt
	//si no quiero hacer nada mas fin
	bool fin_operaciones=false;
	while( !fin_operaciones ){
		printf(MAG "Si quieres realizar operaciones apreta la tecla Y\n");
		printf(MAG "Si quieres crearte una nueva cuenta bancaria apreta la tecla N\n");
		printf(MAG "Si no quieres realizar nada mas apreta O\n");
		char letra = getch();
		if(letra=='O' || letra=='o' ){
			//fin 
			fin_operaciones = true;
			printf("Muchas gracias, hasta la próxima!\n");
		}	
		else if(letra=='Y' || letra=='y'){
			//mutar a cliente
			int pid = fork();
			if(pid==0){
				execlp("./cliente","./cliente",(char *) NULL);
				exit(-1);
			}
			int status;
			waitpid(pid,&status,0);
			int return_code = WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status);
			printf(MAG "Se han realizado %d operaciones\n" RESET,return_code);
		}
		else if(letra=='N' || letra=='n'){
			//nueva cuenta
			bool creada = false;
			while( !creada ){
				int pid = fork();
				if (pid == 0){
					execlp("./creador","./creador", (char *) NULL);
					exit(-1);
				}
				int status;
				waitpid(pid,&status,0);
				int return_code = WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status);
				if(status == 0){
					printf("Cuenta creada con exito!\n");
					creada = true;
				}
				else if(status == 1){
					printf("Cuenta con ese usuario ya existe\n");
				}
			}
		}
	}
}

char getch(){

    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    //printf("%c\n",buf);
    return buf;
 }
