#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#define TRUE 1
#define FALSE 0
//#define PASSWORD 123/*Change to your password*/
#define PASSLEN 3/*Change to Password Len*/
int server(char *args){
		int es_socket,new_socket,port = 2718,max_clients = 10,client_socket[max_clients],addrlen,opt = TRUE,activity;
		fd_set rfds;
		char *PASSWORD = "123"; /*change to your Password*/
		struct sockaddr_in address;
		int i = 0;
		while(i < max_clients){
			i++;
			client_socket[i] = 0;
		}
		printf("Establishing Socket\n");
		es_socket = socket(AF_INET,SOCK_STREAM,0);
		setsockopt(es_socket,SOL_SOCKET,SO_REUSEADDR,(char *)&opt,sizeof(opt));
		printf("Binding Port: %d\n",port);
		address.sin_family = AF_INET;
		address.sin_port = htons(port);
		address.sin_addr.s_addr = INADDR_ANY;
		bind(es_socket,(struct sockaddr *)&address,sizeof(address));
		printf("Listining on port: %d\n",port);
		listen(es_socket,max_clients);
		while(1){
			/*if(client_socket[i] > 0){
				DIR *d;
				struct dirent *ent;
				if((d = opendir("/")) != NULL){
					while((ent = readdir(d))!=NULL){
						send(client_socket[i],ent->d_name,strlen(ent->d_name),0);
						send(client_socket[i],"\n",strlen("\n"),0);
					}
				}
			}*/
			FD_ZERO(&rfds);
			FD_SET(es_socket,&rfds);
			i = 0;
			while(i < max_clients){
				i++;
				if(client_socket[i] > 0){
					send(client_socket[i],">",strlen(">"),0);
					char *dir = malloc(1024);
					recv(client_socket[i],dir,1024,0);
					//send(client_socket[i],dir,strlen(dir),0);
					//send(client_socket[i],"this comes after",strlen("this comes after"),0);
					if(strncmp(dir,"write",5) == 0){
						send(client_socket[i],"Password:",strlen("Password:"),0);
						char *passwd = malloc(80);
						recv(client_socket[i],passwd,80,0);
						send(client_socket[i],"Writing Disabled by Deafult Uncomment code to enable\n",strlen("Writing Disabled by Deafult Uncomment code to enable\n"),0);
						
						/*if(strncmp(passwd,PASSWORD,PASSLEN) == 0){
							send(client_socket[i],"File to write\n",strlen("File to write\n"),0);
							char *f2w = malloc(10240);
							recv(client_socket[i],f2w,10240,0);
							FILE *ff2w = fopen(f2w,"a");
							while(1){
								send(client_socket[i],"&",2,0);
								char *line = malloc(1024);
								recv(client_socket[i],line,1024,0);
								if(strncmp(line,"!EOF",4) == 0){
									break;
								}
								else{
									fprintf(ff2w,"%s",line);
									line = "";
								}
							}
							fclose(ff2w);
						}
						*/
					}
					else{
						dir[strlen(dir) - 1] = '\0';
						DIR *d;
						struct dirent *ent;
						if((d = opendir(dir)) != NULL){
							while((ent = readdir(d)) != NULL){
								send(client_socket[i],ent->d_name,strlen(ent->d_name),0);
								send(client_socket[i],"\n",strlen("\n"),0);
							}
						}
						else{
							FILE *f;
							if((f = fopen(dir,"r")) != NULL){
								char *fbuff = malloc(80);
								char *masterstr = malloc(10240);
								while((fgets(fbuff,1024,f))){
									strcat(masterstr,fbuff);
								}
								send(client_socket[i],masterstr,strlen(masterstr),0);
							}
							else{
								send(client_socket[i],"Error Openining directory\n",strlen("Error Opening directory\n"),0);
							}
						}
					}
				}
			}
			i = 0;
			while(i < max_clients){
				i++;
				if(client_socket[i] > 0){
					FD_SET(client_socket[i],&rfds);
				}
			}
			activity = select (max_clients+3,&rfds,NULL,NULL,NULL);
			if(FD_ISSET(es_socket,&rfds)){
				addrlen = sizeof(address);
				printf("Establishing new socket\n");
				new_socket = accept(es_socket,(struct sockaddr *)&address,&addrlen);
				/*  DIR *d;
                                struct dirent *ent;
                                if((d = opendir(args)) != NULL){
					int num = 0;
                                        while((ent = readdir(d))!=NULL){
						num++;
                                                send(new_socket,ent->d_name,strlen(ent->d_name),0);
                                                send(new_socket,"\n",strlen("\n"),0);
                                        }
                               		/*char *numc = malloc(1024);
					sprintf(numc,".;%d\n",num);
					send(new_socket,numc,strlen(numc),0);
					*/
     //                   }
				i = 0;
				while(i < max_clients){
					i++;
					if(client_socket[i] == 0){
						client_socket[i] = new_socket;
						i = max_clients;
					}
				}
			}
		}
}
