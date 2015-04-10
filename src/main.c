#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ncurses.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
int main(int a, char *b[]){
	if(a < 2){
		 printf("                                ______________\n"
                       "                                            / \n"
                       "                                           /  \n"
                       "                                          /   \n"
                       "                                         /    \n"
                       "                                        /     \n"
                       "                                       /      \n"
                       "                                      /       \n"
                       "                                     /        \n"
                       "                                    /         \n"
                       "                                   /          \n"
                       "                                  /           \n"
                       "                                 /            \n"
                       "                                /             \n"
                       "                                ______________\n");
		printf("Usage: $EXEC opt\n");
	}
	else{
		printf("				______________\n"
		       "                                            / \n"
		       "                                           /  \n"
		       "                                          /   \n"
		       "                                         /    \n"
                       "                                        /     \n"
                       "                                       /      \n"
                       "                                      /       \n"
                       "                                     /        \n"
                       "                                    /         \n"
		       "                                   /          \n"
	               "                                  /           \n"
		       "                                 /            \n"
		       "                                /             \n"
                       "				______________\n");
		if(strcmp(b[1],"--server") == 0){
			if(a > 2){
				//printf("Exec\n");
				server(a,b[2]);
			}
			else{
				server(a,NULL);
			}
		}
		else if(strcmp(b[1],"--client") == 0){
			client(b[2]);
		}
		else if(strcmp(b[1],"--help") == 0){
			printf("Usage:			./zod --{server,client, or help}\n");
		}
		else{
			printf("Syntax error\n");
		}
	}
}
