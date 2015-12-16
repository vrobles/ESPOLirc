#include "../include/user.h"
#include "../include/util.h"
#include "../include/text.h"
#include "../include/receive_commands.h"
#include "../include/commands.h"

void receive_nick(User *user, Node *users, char *nick, char *send_line) {
	if(nick == NULL){
		send_line = strset("Nick no ingresado!!!, Ingrese un nick. \n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}
	if(get_user_by_nick(users, nick) != NULL){
		send_line = strset("Este Nick ya existe!!!, Ingrese un nuevo nick. \n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}
	
	user->nick = strset(nick);
	
	send_line = strset(":");
    send_line = stradd(send_line, user->nick);
    send_line = stradd(send_line, "@");
    send_line = stradd(send_line, user->hostname);
    send_line = stradd(send_line, " ");
	
	send_line = stradd(send_line, NICK);
	send_line = stradd(send_line, " :");
	send_line = stradd(send_line, user->nick);
	send_line = stradd(send_line, "\n");
	send_all(user->current_channel, send_line, users);	
}

void receive_user(User *user, char *name, char *send_line) {
    send_line = stradd(send_line, WELCOME);
	if(name != NULL)
		user->name = strset(name);
    send_line = stradd(send_line, user->name);
	send_line = stradd(send_line, "\n");
    send_line = stradd(send_line, WELCOME_NICK);
    send_line = stradd(send_line, user->nick);
    send_line = stradd(send_line, "\n");

    write(user->socket, send_line, strlen(send_line));
}

void receive_info(User *user,char *send_line,char *runtimeDate) {
    send_line = stradd(send_line, VERSION);
    send_line = stradd(send_line,runtimeDate);
    send_line = stradd(send_line, "\n");
    write(user->socket, send_line, strlen(send_line));
}


void receive_list(User *user, Node *users, char *send_line) {
	Node *first  = users;
    Node *p      = users;
    User *target = (User *) p->payload;
	char *prim_line = strset("Los canales son: ");
	char arreglo[30][40];
	char aux[40];
	int i, j, k, l=0;
	
	strcpy(arreglo[l++], target->current_channel);	
	
    p = p->next;
    target = (User *) p->payload;

	
    while(p != first) {
		strcpy(arreglo[l++], target->current_channel);		
        p = p->next;
        target = (User *) p->payload;
    }
	// ORDENAR CADENAS
    for(i=0; i<l-1; i++){
        k=i;
        strcpy(aux, arreglo[i]);
        for(j=i+1; j<l; j++){
            if(strcmp(arreglo[j], aux)<0){
                k=j;
                strcpy(aux, arreglo[j]); //permite hacer una copia auxiliar de la cadena arreglo[j];
            }
        }
        strcpy(arreglo[k],arreglo[i]);
        strcpy(arreglo[i],aux);
    }	
	send_line = stradd(prim_line, *arreglo);
	for(i=1;i<l;i++){
		if(strcmp(arreglo[i], arreglo[i-1]) != 0){
			send_line = stradd(send_line, ", ");
			send_line = stradd(send_line, arreglo[i]);
		}
	}
	send_line = stradd(send_line, "\n");
    write(user->socket, send_line, strlen(send_line));
}


void receive_join(User *user, Node *users, char *channel, char *send_line) {
	if(channel == NULL){
		send_line = strset("Channel no ingresado!!!, Ingrese un channel. \n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}
	if(strcmp(user->nick, NICK) == 0){
		send_line = strset("Nick no ingresado!!!, Ingrese un nick. \n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}
    send_line = strset(":");
    send_line = stradd(send_line, user->nick);
    send_line = stradd(send_line, "!");
    send_line = stradd(send_line, user->hostname);
    send_line = stradd(send_line, " ");
    send_line = stradd(send_line, JOIN);

    send_line = stradd(send_line, " #");
    send_line = stradd(send_line, channel);
    send_line = stradd(send_line, "\n");
    user->current_channel = strset(channel);
    write(user->socket, send_line, strlen(send_line));
    send_names(user, users, send_line);
}

void receive_part(User *user, Node *users, char *send_line) {
    send_line = strset(":");
    send_line = stradd(send_line, user->nick);
    send_line = stradd(send_line, "@");
    send_line = stradd(send_line, user->hostname);
    send_line = stradd(send_line, " ");
    send_line = stradd(send_line, PART);

    send_line = stradd(send_line, " #");
    send_line = stradd(send_line, user->current_channel);
    send_line = stradd(send_line, "\n");

    send_all(user->current_channel, send_line, users);
    user->current_channel = strset(DUMMY_CHANNEL);
}

void receive_privmsg(User *user, Node *users, char *send_line, char *message) {
    char *line, *channel, *word;

    line           = malloc(strlen(message) + 1);
    line           = strcpy(line, message);

    strtok(line, " \t\r\n/");
    channel        = strtok(NULL, " #\t\r\n/");
	
	if(strlen(channel)==2){
		send_line = strset("Channel no ingresado!!!, Ingrese un channel. \n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}	

    send_line      = strset(":");
    send_line      = stradd(send_line, user->nick);
    send_line      = stradd(send_line, "@");
    send_line      = stradd(send_line, user->hostname);
    send_line      = stradd(send_line, " ");
    send_line      = stradd(send_line, PRIVMSG);

    send_line      = stradd(send_line, " #");
    send_line      = stradd(send_line, channel);
    send_line      = stradd(send_line, " :");

    word           = strtok(NULL, " :\t\r\n/");

    while (word   != NULL) {
        send_line  = stradd(send_line, word);
        send_line  = stradd(send_line, " ");
        word       = strtok(NULL, " \t\r\n/");
    }
	send_line      = stradd(send_line, "\n");
    send_others(user->nick, channel, send_line, users);
}
Node *receive_quit(User *user, Node *users, pthread_mutex_t list_mutex, char *send_line) {
    receive_part(user, users, send_line);

    pthread_mutex_lock(&user->socket_mutex);
    close(user->socket);
    pthread_mutex_unlock(&user->socket_mutex);

    pthread_mutex_lock(&list_mutex);
    users = remove_user(users, user->nick);
    pthread_mutex_unlock(&list_mutex);

    if(length(users) > 0) {
        return users;
    }
    else {
        return empty_user_list();
    }
}

void receive_time(User *user, char *send_line) {
	// time_t t = time(NULL);
 //    struct tm tm = *localtime(&t);
 //    char date[16], time[16];
	// if(strcmp(user->current_channel, DUMMY_CHANNEL) != 0) {
 //        send_line = strset(":");
 //        send_line = stradd(send_line, user->nick);
 //        send_line = stradd(send_line, "!");
 //        send_line = stradd(send_line, user->hostname);
 //        send_line = stradd(send_line, " ");
 //        send_line = stradd(send_line, PRIVMSG);

 //        send_line = stradd(send_line, " #");
 //        send_line = stradd(send_line, user->current_channel);
 //        send_line = stradd(send_line, " :");
 //    }else {
 //        send_line = strset(":irc.operativos.org NOTICE * :*** ");
 //    }
	// sprintf(date, "%02d/%02d/%04d\n", tm.tm_mday, tm.tm_mon + 1,tm.tm_year + 1900);
 //    send_line     = stradd(send_line, "Fecha del Servidor: ");
 //    send_line     = stradd(send_line, date);
 //    sprintf(time, "%02d:%02d:%02d -- %s\n", tm.tm_hour, tm.tm_min,tm.tm_sec, tm.tm_zone);
    time_t rawtime;
    struct tm * timeinfo;
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    //sprintf(runtimeDate, "Fecha y hora actual del servidor :%s\n", asctime (timeinfo));
    send_line = stradd(send_line, "Fecha y hora actual del servidor: ");
    send_line = stradd(send_line,  asctime (timeinfo));
    write(user->socket, send_line, strlen(send_line));
	
}

void receive_allusers(User *user, Node *users, char *send_line){
    Node *first  = users;
    Node *p      = users;
    User *target = (User *) p->payload;
    char *prim_line = strset("ircESPOL:\t");
    char arreglo[30][40];
    char arreglonick[30][40];
    char arregloip[30][40];

    char aux[40];
    int i, j, k, l=0;
    
    strcpy(arreglo[l++], target->name);
    strcpy(arreglo[l++], "\t");
    strcpy(arreglo[l++], target->nick);
    strcpy(arreglo[l++], "\t");
    strcpy(arregloip[l++], target->hostname);  
    
    p = p->next;
    target = (User *) p->payload;

    
    while(p != first) {
        strcpy(arreglo[l++], "\nircESPOL:\t");
        strcpy(arreglo[l++], target->name);
        strcpy(arreglo[l++], "\t");
        strcpy(arreglo[l++], target->nick);
        strcpy(arreglo[l++], "\t");
        strcpy(arregloip[l++], target->hostname);      
        p = p->next;
        target = (User *) p->payload;
    }
    // ORDENAR CADENAS
    /*for(i=0; i<l-1; i++){
        k=i;
        strcpy(aux, arreglo[i]);
        for(j=i+1; j<l; j++){
            if(strcmp(arreglo[j], aux)<0){
                k=j;
                strcpy(aux, arreglo[j]);
            }
        }
        strcpy(arreglo[k],arreglo[i]);
        strcpy(arreglo[i],aux);
    }*/
    send_line = stradd("ircESPOL:\tUser\tNick\tIP", "\n");
    send_line = stradd(send_line, prim_line);   
    send_line = stradd(send_line, *arreglo);
    send_line = stradd(send_line, *arreglonick);
    send_line = stradd(send_line, *arregloip);
    for(i=1;i<l;i++){
        if(strcmp(arreglo[i], arreglo[i-1]) != 0){
            //send_line = stradd(send_line, " ");   
            send_line = stradd(send_line, arreglo[i]);
            send_line = stradd(send_line, arreglonick[i]);
            send_line = stradd(send_line, arregloip[i]);

        }
    }
    send_line = stradd(send_line, "\n");
    write(user->socket, send_line, strlen(send_line));
}

void receive_names(User *user, Node *users, char *send_line, char *channel){
    printf("%s\n", channel);
    if(channel == NULL){
        send_line = strset("Channel no ingresado!!!, Ingrese un channel. \n");
        write(user->socket, send_line, strlen(send_line));
        return;
    }

    Node *first  = users;
    Node *p      = users;
    User *target = (User *) p->payload;
    char *prim_line = strset("ircESPOL:\t");
    char arreglo[30][40];
    char arreglonick[30][40];
    char arregloip[30][40];

    char aux[40];
    int i, j, k, l=0;
    
    if (strcmp(target->current_channel,channel)==0){
        strcpy(arreglo[l++], target->name);
        strcpy(arreglo[l++], "\t");
        strcpy(arreglo[l++], target->nick);
        strcpy(arreglo[l++], "\t");
        strcpy(arregloip[l++], target->hostname);
        strcpy(arreglo[l++], "\t\t");  
        strcpy(arregloip[l++], target->current_channel);  
    }
    p = p->next;
    target = (User *) p->payload;
    
    while(p != first) {
        if (strcmp(target->current_channel,channel)==0){
            strcpy(arreglo[l++], "\nircESPOL:\t");
            strcpy(arreglo[l++], target->name);
            strcpy(arreglo[l++], "\t");
            strcpy(arreglo[l++], target->nick);
            strcpy(arreglo[l++], "\t");
            strcpy(arregloip[l++], target->hostname);
            strcpy(arreglo[l++], "\t\t");  
            strcpy(arregloip[l++], target->current_channel);  
        }     
        p = p->next;
        target = (User *) p->payload;
    }
    send_line = stradd("ircESPOL:\tUser\tNick\tIP\t\tChannel", "\n");
    send_line = stradd(send_line, prim_line);   
    send_line = stradd(send_line, *arreglo);
    send_line = stradd(send_line, *arreglonick);
    send_line = stradd(send_line, *arregloip);
    for(i=1;i<l;i++){
        if(strcmp(arreglo[i], arreglo[i-1]) != 0){
            //send_line = stradd(send_line, " ");   
            send_line = stradd(send_line, arreglo[i]);
            send_line = stradd(send_line, arreglonick[i]);
            send_line = stradd(send_line, arregloip[i]);
        }
    }
    send_line = stradd(send_line, "\n");
    write(user->socket, send_line, strlen(send_line));
}