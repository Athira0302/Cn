// FTP Client Program
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<arpa/inet.h>
#include<unistd.h>

int main() {
    int client_socket;
    struct sockaddr_in server_addr;
    char buffer[1024], filename[100];
    FILE *fp;

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(9000);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(client_socket, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Enter filename to receive: ");
    scanf("%s", filename);

    send(client_socket, filename, sizeof(filename), 0);

    fp = fopen("received.txt", "w");

    while(recv(client_socket, buffer, sizeof(buffer), 0) > 0) {
        fprintf(fp, "%s", buffer);
    }

    printf("File received successfully.\n");

    fclose(fp);
    close(client_socket);

    return 0;
}


