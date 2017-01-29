#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include "defs.h"

int main(int argc, char *argv[]){
	
	//TODO: ENCARGADO DE CREAR CUENTAS Y ACTUALIZARLAS SI EL CLIENTE QUIERE
	printf(GRN "Bienvenido al banco Epsilon\n\n" RESET);
	printf(MAG "Si quieres realizar operaciones apreta la tecla Y\n");
	printf(MAG "Si quieres crearte una nueva cuenta bancaria apreta la tecla N\n");
	printf(MAG "Si no quieres realizar nada mas apreta O\n");
	//si quiero realizar operaciones muto a cliente
	//si quiero crear cuenta escribo en cuentas.txt
	//si no quiero hacer nada mas fin
	bool fin_operaciones=false;
	while( !fin_operaciones ){
		char letra = getchar();
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
			int return_code;
			waitpid(pid,&status,0);
			return_code = WIFEXITED(status) ? WEXITSTATUS(status) : WTERMSIG(status);
			printf("Se han realizado %d operaciones\n",return_code);
		}
		else if(letra=='N' || letra=='n'){
			//nueva cuenta
		}
		
	}
	
}
