#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>

int main(int argc, char **argv) {
    // CREAZIONE DELLA SOCKET
    int Csocket;
    char *Messaggio = malloc(sizeof(*Messaggio));
    Csocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (Csocket < 0) {
        printf("socket creation failed.\n");
        close(Csocket);
        return 0;
    }

    char ipServer[20];
    int porta;
    struct sockaddr_in sad;
    memset(&sad, 0, sizeof(sad));
    sad.sin_family = AF_INET;

    printf("Inserisci l'indirizzo IPv4: ");
    scanf("%s", ipServer);
    sad.sin_addr.s_addr = inet_addr(ipServer); // IP del server

    printf("Inserisci la porta: ");
    scanf("%d", &porta);
    sad.sin_port = htons(porta); // Server port

    // CONNESSIONE AL SERVER
    if (connect(Csocket, (struct sockaddr *)&sad, sizeof(sad)) < 0) {
        printf("Failed to connect.\n");
        close(Csocket);
        return 0;
    }

    scanf("%s\n", Messaggio);
    // Si puo' notare il semplice utilizzo di write:
    if (write(Csocket, Messaggio, strlen(Messaggio)) < 0) {
        printf("Impossibile mandare il messaggio.\n");
        close(Csocket);
    } else {
        printf("Messaggio spedito con successo.\n");
    }

    close(Csocket);
    return 0;
}