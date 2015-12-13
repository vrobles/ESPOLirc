#include "../include/user.h"
#include "../include/util.h"
#include "../include/text.h"
#include "../include/receive_commands.h"
//#include "../include/responses.h"
//#include "../include/errors.h"
#include "../include/commands.h"

void receive_nick(User *user, Node *users, char *nick, char *send_line) {
    send_line = strset(":");
    send_line = stradd(send_line, user->name);
    send_line = stradd(send_line, "!");
    send_line = stradd(send_line, user->hostname);
    send_line = stradd(send_line, " ");
	if(nick != NULL)
		user->nick = strset(nick);
	else if(get_user_by_name(users, name) != NULL){
		send_line = stradd(send_line, "NICK ya existe!!!, Ingrese un nuevo nick: ");
		send_line = stradd(send_line, "\n");
		write(user->socket, send_line, strlen(send_line));
		return;
	}
		
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
