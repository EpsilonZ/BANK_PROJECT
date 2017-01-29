#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char *argv[]){

	//TODO: ENCARGADO DE BUSCAR CUENTA en "base de datos"
	
	int status=0;	
	if(argc==3){
		char *user = argv[1];
		char *password = argv[2];
		//printf("El user a buscar es %s y la password a buscar es %s\n", user, password);
		char *credenciales;
		credenciales = malloc(strlen(user) + strlen(password) + 1);
		strcpy(credenciales,user);
		strcat(credenciales,password);
		int fd = open ("cuentas.txt", O_RDONLY);
		char aux[8];
		int llegits;
		bool found = false;
		while(llegits = read (fd,&aux,8) == 8 && !found){
			if(strcmp(credenciales,aux)==0){
				found=true;
			}
		}
		if(found){
			//printf("ENCONTRADO!\n");
			status=1;
		}
		free(credenciales);
	}
	else{
		//printf("ERROR\n");
	}
	exit(status);
}
