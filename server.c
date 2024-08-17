#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char *argv[]) {
    int MySocket;

    MySocket = socket(AF_INET, SOCK_STREAM, 0);
    if (MySocket < 0) {
        printf("Socket creation failed.\n");
        return 0;
    }

    struct sockaddr_in sad;
    sad.sin_family = AF_INET;
    sad.sin_addr.s_addr = inet_addr("151.100.4.83");
    sad.sin_port = htons(27015);

    if (bind(MySocket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
        printf("bind() failed.\n");
        close(MySocket);
        return 0;
    }

    if (listen(MySocket, 6) < 0) {
        printf("listen() failed.\n");
        close(MySocket);
        return 0;
    }

    struct sockaddr_in cad;
    int clientSocket;
    unsigned int clientLen;

    printf("Waiting for a client to connect...");
    while (1) {
        clientLen = sizeof(cad);
        if ((clientSocket = accept(MySocket, (struct sockaddr *)&cad, &clientLen)) < 0) {
            printf("accept() failed.\n");
            close(MySocket);
            return 0;
        }

        printf("Handling client %s\n", inet_ntoa(cad.sin_addr));
    }

    close(MySocket);

    system("PAUSE");
    return 0;
}