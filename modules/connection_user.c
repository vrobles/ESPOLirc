#include "../include/connect_user.h"

/* This will handle connection for each client */
void connection_handler(User *user){
	printf("Usuario %d conectado\n", user->id);
	char message[MAXLINE + 1];
	char *line = malloc(MAXLINE + 1);
	char *send_message = malloc(MAXLINE + 1);
	char *command;
	char *mensaje;
	int sock = user->socket;
	int read_size;
   // char client_message[2000];
	
	
	
	    //Send some messages to the client
    mensaje = "Soy el Manejador de conexion. Yo me comunicare con usted, Ahora escriba algo\n";
    write(sock , mensaje , strlen(mensaje));
	
	
	pthread_mutex_lock(&user->socket_mutex);
    read_size = read(user->socket, message, MAXLINE);
    pthread_mutex_unlock(&user->socket_mutex);
	
	while(read_size > 0) {
		message[read_size] = 0;
		line = strcpy(line, message);
		command = strtok(line, " \t\r\n/");
       // command = uppercase(command);
	
	    //Enviar respuesta al cliente
		mensaje = "Su mensaje fue recibido, continue escribiendo algo\n";
        write(sock , mensaje , strlen(mensaje));
		
		//clear the message buffer
		//memset(client_message, 0, 2000);
	
	    pthread_mutex_lock(&user->socket_mutex);
        read_size = read(user->socket, message, MAXLINE);
        pthread_mutex_unlock(&user->socket_mutex);
	}
     
	 

     /*
	 //Receive a message from client
    while( (read_size = recv(sock , client_message , 2000 , 0)) > 0 ){
        //Enviar respuesta al cliente
		message = "Su mensaje fue recibido, continue escribiendo algo\n";
        write(sock , message , strlen(message));

	//clear the message buffer
	memset(client_message, 0, 2000);
    }
     */
	 
    if(read_size == 0){
        puts("Cliente Desconectado");
        fflush(stdout);
    }
    else if(read_size == -1){
        perror("comunicacion fallida");
    } 
     
    //return 0;
}
