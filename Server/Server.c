#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "doprocessing.h"

int main(int atgc, char *argv[])
{
    int socket_desc, new_socket, c;
    struct sockaddr_in server, client;
    int pid;
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1)
    {
        printf("Connot create socket");
    }
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(8888);
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        puts("bind failed");
        return 1;
    }
    puts("bind done");
    listen(socket_desc, 3);
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c)))
    {
        if (new_socket < 0)
        {
            perror("accept failed");
            return 1;
        }
        else{
            pid = fork();
            if(pid == 0){
                close(socket_desc);
                doprocessing(new_socket);
                exit(0);
            }
            else{
                close(new_socket);
            }
        }
    }
    return 0;
}