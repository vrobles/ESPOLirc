#include "../include/user.h"

Node *empty_user_list() {
    Node *users         = malloc(sizeof(Node));
    users->next         = users;
    users->prev         = users;
    users->payload      = malloc(sizeof(User));
    User *user          = (User *) users->payload;
    user->id            = -1;
    return users;
}

int length(Node *list) {
    if(list == NULL || (list->payload)->id == -1)
        return 0;
    else {
        Node *first = list;
        Node *p     = first;
        int   i     = 1;
        p           = p->next;
        while(p != first) {
            p  = p->next;
            i += 1;
        }
        return i;
    }
}

Node *add_node(Node *list) {
    Node *node = malloc(sizeof(Node));
    if(list == NULL) {
        list          = node;
        list->prev    = list;
        list->next    = list;
    }
    else {
        node->next       = list;
        node->prev       = list->prev;
        list->prev->next = node;
        list->prev       = node;
        if(list->next == list) {
            list->next = node;
        }
        list = node;
    }
    list->payload = malloc(sizeof(User));
    return list;
}

Node *add_user(Node *list, char *name, char *nick, char *hostname,
               int id, char *channel, int socket) {
    if(list == NULL)
        return list;
    else {
        User *user            = (User *) list->payload;
        if (user->id != -1)
            list = add_node(list);
			
        user                  = (User *) list->payload;
        user->id              = id;
        user->socket          = socket;
        user->name            = malloc(strlen(name) + 1);
		user->nick            = malloc(strlen(nick) + 1);
        user->current_channel = malloc(strlen(channel) + 1);
        user->hostname        = malloc(strlen(hostname) + 1);
        strcpy(user->name, name);
        strcpy(user->hostname, hostname);
        strcpy(user->current_channel, channel);
        return list;
    }
}

User *get_user_by_nick(Node *users, char *nick) {
    int i;
    int list_length = length(users);
    Node *p         = users;
    User *user      = p->payload;
    for(i = 0; i < list_length; i++) {
        if(strcmp(user->nick, nick) == 0) {
            return user;
        }
        p    = p->next;
        user = p->payload;
    }
    return NULL;
}

Node *remove_node(Node *list) {
    if(list == NULL) {
        return NULL;
    }
    else if(list->next == list) {
        free(list);
        return NULL;
    }
    else {
        Node *p = list;
        list->prev->next = list->next;
        list->next->prev = list->prev;
        list = list->next;
        free(p);
        return list;
    }
}

Node *remove_user(Node *list, char *nick) {
    if(list == NULL) {
        return NULL;
    }
    else {
        Node *p    = list;
        User *user = (User *) p->payload;
        if(strcmp(user->nick, nick) == 0) {
            list = remove_node(p);
            return list;
        }
        p    = p->next;
        user = (User *) p->payload;
        while(p != list) {
            if(strcmp(user->nick, nick) == 0) {
                list = remove_node(p);
                return list;
            }
            p    = p->next;
            user = (User *) p->payload;
        }
        printf("el NIck  %s no esta en la lista.\n", nick);
        return list;
    }
}