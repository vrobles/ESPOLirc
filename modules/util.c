#include "../include/util.h"

char *uppercase(char str[]) {
    int p = 0;
    while (str[p]) {
        str[p] = toupper(str[p]);
        p += 1;
    }
    return str;
}

char *strset(char *str) {
    char *result = malloc(strlen(str)+1);
    strcpy(result, str);
    return result;
}

char *stradd(char *str1, char *str2) {
    char *result = malloc(strlen(str1)+strlen(str2)+1);
    strcpy(result, str1);
    strcat(result, str2);
    return result;
}

void send_all(char *channel, char *message, Node *users) {
    Node *first  = users;
    Node *p      = users;
    User *target = (User *) p->payload;

    if(strcmp(target->current_channel, channel) == 0)
        write(target->socket, message, strlen(message));
		
    p = p->next;
    target = (User *) p->payload;
    while(p != first) {
        if(strcmp(target->current_channel, channel) == 0) 
            write(target->socket, message, strlen(message));
			
        p = p->next;
        target = (User *) p->payload;
    }
};