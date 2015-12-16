#include "../include/commands.h"

char *NICK           = "NICK";
char *USER           = "USER";
char *LIST           = "LIST";
char *JOIN           = "JOIN";
char *PART           = "PART";
char *PRIVMSG        = "PRIVMSG";
char *QUIT           = "QUIT";
char *TIME			 = "TIME";
char *USERS			 = "USERS";
char *INFO			 = "INFO";
char *VERSION		 = "Socket ESPOL Chat - Version: 1.0.1";




//MOTD
//Da el "mensaje del día" para un servidor que explica las políticas del servidor y otra información. Siempre debe leer esto antes de usar cualquier servidor.

//NAMES
//names <#canal> Muestra los nicks de toda la gente en un canal dado.

//SETNAME
//Permite a los usuarios cambiar su 'Nombre real' sin volver a conectar

//VERSION 
//se utiliza para consultar la versión del programa servidor. 