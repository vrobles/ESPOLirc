#ifndef CONNECT_USER_H
#define CONNECT_USER_H

#include <stdio.h>
#include <stdlib.h>   //strlen
#include <errno.h>
#include <stdio.h> //printf
#include <string.h>	//strlen 
#include <netdb.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h> //socklen_t 
#include <arpa/inet.h> //inet_addr
#include <time.h>
#include <unistd.h>    //write
#include <pthread.h>   //for threading



#include "user.h"
#include "util.h"
#include "text.h"
#include "commands.h"
#include "receive_commands.h"

#define LISTENQ 1
#define MAXDATASIZE 100
#define MAXLINE 4096

Node *user_list;
char *runtimeDate;
pthread_mutex_t user_list_mutex;

/*Prototipos de funciones*/
int open_socket();
int bind_to_port(int, int);
void connection_handler(User *);

#endif
