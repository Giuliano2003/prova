// Server side implementation of TCP client-server model
#include <bits/stdc++.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
   
// Compile instructions:
//	g++ -o server TCP_multi_server.cpp

int main() {
    int sockfd, new_socket;
    int opt = 1;
    char buffer[1024];
    struct sockaddr_in servaddr, cliaddr;
    
    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) {
        perror("socket creation failed");
        exit(EXIT_FAILURE);
    }
       
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    
    servaddr.sin_family    = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(8080);
    
    if ( bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0 ) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    
    char keep_alive[2] = "y";
    
    if (listen(sockfd, 3) < 0) {
	perror("listen");
	exit(EXIT_FAILURE);
    }
    
    while(strcmp(keep_alive,"n")){
            memset(buffer,0,strlen(buffer));
	    	std::cout<<"WIITING FOR CONNECTIONS..."<<std::endl;
	    
	    	int addrlen = sizeof(cliaddr);
	    	if ((new_socket = accept(sockfd, (struct sockaddr*)&cliaddr,
			(socklen_t*)&addrlen)) < 0) {
				perror("accept");
				continue;
	    	}
	    	std::cout<<"...NEW CONNECTION OPEN"<<std::endl;
	    	int n;
	    	while(strcmp(buffer, "close")){
	    	memset(buffer,0,strlen(buffer));
	    	//receiving generic message, sending ack
				n = read(new_socket, buffer, 1024);
				buffer[n] = '\0';
		
				std::cout<<"[RECEIVED "<<n<<" bytes from "<<inet_ntoa(cliaddr.sin_addr)<<":"<<ntohs(cliaddr.sin_port)<<"]: "<<buffer<<std::endl;
		
				send(new_socket, "ack", 3, 0);
				std::cout<<"[SENT 3 bytes to "<<inet_ntoa(cliaddr.sin_addr)<<":"<<ntohs(cliaddr.sin_port)<<"]: ack"<<std::endl;
	    	}
	    	std::cout<<"CONNECTION CLOSED BY CLIENT"<<std::endl;
	    
	    	memset(buffer,0,strlen(buffer));
	    	n = read(new_socket, buffer, 1024);
	    	std::cout<<"CONNECTION RELEASED"<<std::endl;
	    
	    	close(new_socket);
	    	std::cout<<"Do you wish to accept other connections (y/n)? "<<std::endl;
	    	std::cin.getline(keep_alive,2);
    }
    close(sockfd);
    return 0;
}
