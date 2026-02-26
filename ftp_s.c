/iiih/ FTP Server Program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024], filename[100];
    FILE *fp;

    server_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));
    listen(server_socket, 5);

    printf("Waiting for connection...\n");
    client_socket = accept(server_socket, NULL, NULL);
    printf("Client connected.\n");

    recv(client_socket, filename, sizeof(filename), 0);

    fp = fopen(filename, "r");

    if(fp == NULL) {
        strcpy(buffer, "File not found");
        send(client_socket, buffer, sizeof(buffer), 0);
    } else {
        while(fgets(buffer, sizeof(buffer), fp) != NULL) {
            send(client_socket, buffer, sizeof(buffer), 0);
        }
        fclose(fp);
    }

    close(client_socket);
    close(server_socket);

    return 0;
}

