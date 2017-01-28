#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"
char *user;
char *password;

bool pagina_principal();
void pagina_inicio();
void obten_credenciales();

int main(int argc, char *argv[]){

	//TODO: ENCARGADO DE PODER INTERACTUAR Y CUBRIR LAS NECESIDADES DEL CLIENTE
	/*
	printf(RED "red\n" RESET);
  printf(GRN "green\n" RESET);
  printf(YEL "yellow\n" RESET);
  printf(BLU "blue\n" RESET);
  printf(MAG "magenta\n" RESET);
  printf(CYN "cyan\n" RESET);
  printf(WHT "white\n" RESET);
	*/
	bool correcto = pagina_principal();
	if(correcto){
		printf("Bienvenido %s !\n",user);
		pagina_inicio();
	}
	else{
		printf("ERROR EN IDENTIFICACION\n");
		return 0;
	}
	free(password);
	free(user);
	
}

void obten_credenciales(){
	printf(BLU "Introduce tu usuario y contraseña \n" RESET);	
	user = malloc (4 * sizeof(char) );
	password = malloc (4 * sizeof(char) );
	printf("User :");
	scanf("%s", user);
	fflush(stdout);
	printf("Password :");
	scanf("%s", password);
	fflush(stdout);
}


bool pagina_principal(){
	printf(RED "**************** BIENVENIDO **************** \n" RESET);
	printf("Espera ... ");
	fflush(stdout);
	sleep(2);
	system("clear");
	int intentos=3;
	bool correcto=false;
	while(intentos!=0 && !correcto){
		obten_credenciales();
		int pid = fork();
		if(pid==0){
			execlp("./administrador","./administrador",user,password, (char *) NULL );
			exit(-1);
		}
		int status;
		waitpid(pid,&status,0);
		//printf("El status es %d\n",status);
		if(status==0){
			--intentos;
			if(intentos>0){
				printf(RED "USUARIO Y CONTRASEÑA INCORRECTOS, TIENES %d INTENTOS \n" RESET,intentos);
			}
		}	
		else{
			correcto=true;
		}
	}
	return correcto;
}

void pagina_inicio(){
	printf("Selecciona la operacion que quieres realizar \n");
	printf("-------------------------------------------\n");
	printf("Apreta la tecla S para saber tu saldo \n");
	printf("Apreta la tecla I para introducir dinero \n");
	printf("Apreta la tecla F para finalizar\n");
	char letra = getchar();
	bool finished = false;
	while ( !finished ){
		if(letra=='s' || letra=='S'){
			printf("Has elegido saber tu saldo\n");
		}
		else if (letra=='i' || letra=='I'){
			printf("Has elegido introducir dinero\n");
		}
		else if(letra=='F' || letra=='f'){
			printf("Muchas gracias por confiar en nosotros ! \n");
			finished = true;
		}
	}
}
