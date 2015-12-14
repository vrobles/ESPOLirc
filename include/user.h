#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#ifndef USER_H
#define USER_H

typedef struct _User {
    char *name; //nombre real
	char *nick; //su nick
    char *hostname; //su ip
    int id; 
    char *current_channel;
    int socket;
    pthread_t thread;
    pthread_mutex_t socket_mutex;
} User;

typedef struct _Node {
    struct _Node *prev;
    struct _Node *next;
    User *payload;
} Node;


Node *empty_user_list();
int length(Node *);
Node *add_user(Node *, char *, char *, char *, int, char *, int);
User *get_user_by_nick(Node *, char *);
Node *remove_user(Node *, char *);

#endif