#include "user.h"

Node *empty_user_list() {
    Node *users         = malloc(sizeof(Node));
    users->next         = users;
    users->prev         = users;
    users->payload      = malloc(sizeof(User));
    User *user          = (User *) users->payload;
    user->id            = -1;
    return users;
};