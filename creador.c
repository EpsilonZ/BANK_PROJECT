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
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

char *user;
char *password;

void obten_credenciales();
char getch();

int main(int argc, char *argv[]){

	//FIXME: cuando escribe en cuentas.txt el fichero se corrompe y por algo que todavia no se escribe caracteres "invalidos"
	//TODO:Encargado de crear la cuenta
	obten_credenciales();
	int fd = open ("cuentas.txt", O_RDONLY | O_WRONLY );
	printf("Oh dear, something went wrong with read()! %s\n", strerror(errno));
	bool existe = false;
	int llegits;
	char credenciales[strlen(user) + strlen(password) + 1];
	strcpy(credenciales,user);
	strcat(credenciales,password);
	char aux[8];
	while (  (llegits = read (fd,&aux,8) ) > 0 && !existe){
		if(strcmp(aux,credenciales) == 0){
			printf("existe\n");
			existe = true;
		}
	}
	int exit_value = existe ? 1 : 0;
	printf("%s\n",credenciales);	
	if( ! existe ){	
		write(fd,&credenciales,strlen(credenciales)*sizeof(char));
	}
	free(password);
	free(user);
	exit(exit_value);
}


void obten_credenciales(){
	printf(BLU "Introduce el nombre que quieres como usuario (máximo 4 carácteres) \n" RESET);	
	user = malloc (4 * sizeof(char) );
	password = malloc (4 * sizeof(char) );
	printf("User :");
	scanf("%s", user);
	fflush(stdout);
	printf("Password :");
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
