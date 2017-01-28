#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

char *user;
char *password;

void pagina_principal(bool correcto);
void pagina_inicio();
void obten_credenciales();

int main(int argc, char *argv[]){

	//TODO: ENCARGADO DE PODER INTERACTUAR Y CUBRIR LAS NECESIDADES DEL CLIENTE

	bool correcto;
  pagina_principal(&correcto);
	if(correcto){
		pagina_inicio();
	}
	else{
		printf("ERROR EN IDENTIFICACION\n");
		return 0;
	}
	while(1);
	free(password);
	free(user);
}

void obten_credenciales(){
	printf("Introduce tu usuario y contraseña \n");	
	user = malloc (4 * sizeof(char) );
	password = malloc (4 * sizeof(char) );
	printf("User :");
	scanf("%s", user);
	fflush(stdout);
	printf("Password :");
	scanf("%s", password);
	fflush(stdout);
}


void pagina_principal(bool correcto){
	printf("**************** BIENVENIDO **************** \n");
	printf("Espera ... ");
	fflush(stdout);
	sleep(1);
	system("clear");
	int intentos=3;
	correcto=false;
	while(intentos!=0 && !correcto){
		obten_credenciales();
		int pid = fork();
		if(pid==0){
			execlp("./administrador","./administrador",user,password, (char *) NULL );
			exit(-1);
		}
		int status;
		waitpid(pid,&status,0);
		printf("El status es %d\n",status);
		if(status==0){
			--intentos;
			if(intentos>0){
				printf("USUARIO Y CONTRASEÑA INCORRECTOS, TIENES %d INTENTOS \n",intentos);
			}
		}	
		else{
			printf("Bienvenido %s", user);
			correcto=true;
		}
	}
}

void pagina_inicio(){
	printf("Selecciona la operacion que quieres realizar \n");
	printf("-------------------------------------------\n");
	printf("Apreta la tecla S para saber tu saldo \n");
	printf("Apreta la tecla I para introducir dinero \n");
	printf("Apreta la tecla F para finalizar\n");
	char letra = getchar() ;
	if(letra=='s' || letra=='S'){
		printf("Has elegido saber tu saldo\n");
	}
	else if (letra=='i' || letra=='I'){
		printf("Has elegido introducir dinero\n");
	}
	else if(letra=='F' || letra=='f'){
		printf("Muchas gracias por confiar en nosotros ! \n");
		system("clear");
	}
}
