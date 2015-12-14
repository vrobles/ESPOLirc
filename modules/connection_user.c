#include "../include/connect_user.h"

/* This will handle connection for each client */
void connection_handler(User *user){
	printf("Usuario %d conectado\n", user->id);
	char message[MAXLINE + 1];
	char *line = malloc(MAXLINE + 1);
	char *send_message = malloc(MAXLINE + 1);
	char *command, *mensaje;
	int read_size;
	
	//Send some messages to the client
    mensaje = "Soy el Manejador de conexion. Yo me comunicare con usted.\n Ahora escriba un comando\n";
    write(user->socket , mensaje , strlen(mensaje));
    pthread_mutex_lock(&user->socket_mutex);
    read_size = read(user->socket, message, MAXLINE);
    pthread_mutex_unlock(&user->socket_mutex);
       
	while(read_size > 0 && strlen(message)!=2){
		message[read_size] = 0;
		line = strcpy(line, message);
		command = strtok(line, " \t\r\n/"); //strtok:: la primera cadena delimitado por espacio
		command = uppercase(command);
	
		while(command != NULL) {
			if(strcmp(command, NICK) == 0) {
                receive_nick(user, user_list, strtok(NULL, " \t\r\n/"), send_message); //strtok:: la segunda cadena de line
            }else if(strcmp(command, USER) == 0) {
                receive_user(user, strtok(NULL, " \t\r\n/"), send_message);
			}else if(strcmp(command, LIST) == 0) {
                receive_list(user, user_list, send_message);
            }else if(strcmp(command, JOIN) == 0) {
                receive_join(user, user_list, strtok(NULL, " #\t\r\n/"), send_message);
            }else if(strcmp(command, PART) == 0) {
                receive_part(user, user_list, send_message);
            }else if(strcmp(command, PRIVMSG) == 0) {
                receive_privmsg(user, user_list, send_message, message);
            }
			
			printf("El Usuario %d envio este comando:: \"%s\"]\n", user->id, command);
			command = strtok(NULL, " \t\r\n/");
		}
	
	
	    //Enviar respuesta al cliente
		mensaje = "Escriba otro comando\n";
        write(user->socket , mensaje , strlen(mensaje));
		
		//clear the message buffer
		memset(message, 0, MAXLINE);
		
	    pthread_mutex_lock(&user->socket_mutex);
        read_size = read(user->socket, message, MAXLINE);
        pthread_mutex_unlock(&user->socket_mutex);
	}
     
	 
	 
    if(read_size == 0){
        //puts("Cliente Desconectado");
		printf("Usuario %d Desconectado\n", user->id);
        fflush(stdout);
    }
    else if(read_size == -1){
        perror("comunicacion fallida");
    } 
}
