#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <curses.h>
#include <netdb.h>
static void finish(int sig);
int client(char *args){
	printf("Argument Dump(Debug purposes):%s\n",args);
	char *address = args;
	int es_socket,addrlen;
	int port = 2718;
	printf("Establishing Socket\n");
	es_socket = socket(AF_INET,SOCK_STREAM,0);
	struct hostent *server;
	printf("Resolving Hostname\n");
	server = gethostbyname(address);
	struct sockaddr_in server_address;
	printf("Setting Zeros\n");
	bzero((char *)&server_address,sizeof(server_address));
	server_address.sin_family = AF_INET;
	printf("Binding Address To Machine\n");
	//server_address.sin_port = htons(port);
	//bcopy((char *)&server->h_addr,(char *)&server_address.sin_addr.s_addr,server->h_length);
	server_address.sin_port = htons(port);
	server_address.sin_addr.s_addr = inet_addr(address);
	printf("Connecting to server\n");
	connect(es_socket,(struct sockaddr *)&server_address,sizeof(server_address));
	if(connect < 0){
		printf("Failed to connect!\n");
		exit(EXIT_FAILURE);
	}
	printf("Connected!\n");
	int linelen = 0;
	int i = 0;
/*	while(i < strlen(buff)){
		i++;
		if(buff[i] == '\n'){
			linelen++;
		}
	}*/
	while (1){
		//printf(">");
		char *recvbuff = malloc(1024);
		fgets(recvbuff,1024,stdin);
		send(es_socket,recvbuff,1024,0);
		char *buffer = malloc(1024);
		recv(es_socket,buffer,1024,0);
		printf("%s\n",buffer);
	}
	close(es_socket);
}
