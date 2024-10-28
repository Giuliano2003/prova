#include <stdio.h>       // Per printf, perror
#include <stdlib.h>      // Per exit
#include <string.h>      // Per memset
#include <unistd.h>      // Per close, read
#include <sys/types.h>   // Per definizioni di base (es. socklen_t)
#include <sys/socket.h>  // Per socket, bind, listen, accept
#include <netinet/in.h>  // Per strutture sockaddr_in, INADDR_ANY
#include <arpa/inet.h>   // Per htons, inet_addr (opzionale per client)



int main(){
    int socketfd;
    struct sockaddr_in server_addr;
    char *msg="ciao";
    
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if(socketfd < 0) {
        printf("Errore nella creazione della socket \n");
        exit(-1);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(8080);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");  // IP del server

    int status = connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    if(status < 0){
        printf("Errore nella creazione della connessione \n");
        return -1;
    }

    int nb = send(socketfd, msg, sizeof(msg), 0);
    printf("Messaggio inviato %d", nb);
}
