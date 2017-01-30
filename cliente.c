#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "defs.h"
#include <unistd.h>
#include <termios.h>

int operaciones=0;
char *user;
char *password;

char getch();
bool pagina_principal();
void pagina_inicio();
void obten_credenciales();

int main(int argc, char *argv[]){

	//TODO: ENCARGADO DE PODER INTERACTUAR Y CUBRIR LAS NECESIDADES DEL CLIENTE
	
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
	exit(operaciones);
}

void obten_credenciales(){
	printf(BLU "Introduce tu usuario y contraseña \n" RESET);	
	user = malloc (4 * sizeof(char) );
	password = malloc (4 * sizeof(char) );
	printf("User de 4 letras :");
	scanf("%s", user);
	fflush(stdout);
	printf("Password de 4 letras:");
	int i=0;
	while(i < 4){
		char aux = getch();
		if ( aux != 127 ){
			password[i] = aux;
			printf("*");
			fflush(stdout);
			++i;
		}
		else{
			if(i>0){
				printf("\b \b");
				--i;
			}
		}
	}
	printf("\n");
	//scanf("%s", password);
	//fflush(stdout);
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
	printf(GRN "Selecciona la operacion que quieres realizar \n" RESET);
	printf(GRN "-------------------------------------------\n" RESET);
	printf(GRN "Apreta la tecla S para saber tu saldo \n" RESET);
	printf(GRN "Apreta la tecla D para sacar dinero \n" RESET);
	printf(GRN "Apreta la tecla I para introducir dinero \n" RESET);
	printf(GRN "Apreta la tecla F para finalizar\n" RESET);
	bool finished = false;
	while ( !finished ){
		char letra = getchar();
		if(letra=='d' || letra== 'D'){
			++operaciones;
			printf(YEL "Has elegido sacar dinero\n" RESET );
			//pedir cantidad y restarsela a su total
		}
		else if(letra=='s' || letra=='S'){
			++operaciones;
			printf(YEL "Has elegido saber tu saldo\n" RESET );
			//buscar el usuario y enseñar su saldo
		}
		else if (letra=='i' || letra=='I'){
			++operaciones;
			printf(YEL "Has elegido introducir dinero\n" RESET);
			//buscar su usuario y aumentarle la cantidad de dinero
		}
		else if(letra=='F' || letra=='f'){
			printf(YEL "Muchas gracias por confiar en nosotros ! \n" RESET);
			finished = true;
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
