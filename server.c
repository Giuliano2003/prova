#include <stdio.h>       // Per printf, perror
#include <stdlib.h>      // Per exit
#include <string.h>      // Per memset
#include <unistd.h>      // Per close, read
#include <sys/types.h>   // Per definizioni di base (es. socklen_t)
#include <sys/socket.h>  // Per socket, bind, listen, accept
#include <netinet/in.h>  // Per strutture sockaddr_in, INADDR_ANY
#include <arpa/inet.h>   // Per htons, inet_addr (opzionale per client)

int main(){
    int listen_socket, new_socket;
    struct sockaddr_in server_addr, client_addr;
    char *msg;
    char buffer[124];

    // Creazione del socket di ascolto
    listen_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(listen_socket < 0) {
        printf("Errore nella creazione della socket !\n");
        exit(EXIT_FAILURE);
    }

    // Impostazione dell'indirizzo del server
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(8080);

    // Bind del socket all'indirizzo del server
    int val = bind(listen_socket, (const struct sockaddr *)&server_addr, sizeof(server_addr));
    if(val < 0) {
        perror("Binding fallito!");
        exit(EXIT_FAILURE);
    }

    // Inizializzazione delle dimensioni del client_addr
    socklen_t size = sizeof(client_addr);

    // Inizio dell'ascolto di connessioni
    listen(listen_socket, 4);
    printf("Aspettando richieste server:\n");

    // Accettare una connessione in entrata
    new_socket = accept(listen_socket, (struct sockaddr *)&client_addr, &size);
    if(new_socket < 0) {
        perror("Errore nell'accettazione");
        exit(EXIT_FAILURE);
    }

    // Pulizia del buffer prima di leggere i dati
    memset(buffer, 0, sizeof(buffer));

    printf("Connessione accettata\n");

    // Leggere i dati dal socket
    read(new_socket, buffer, 124);
    printf("Hai mandato: %s\n", buffer);

    // Chiudere i socket
    close(new_socket);  // Chiudere il socket della connessione accettata
    close(listen_socket);  // Chiudere il socket di ascolto
}
