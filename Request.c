#include "Scanner.h"

bool    HttpRequest(int port, int sock, t_data *data) {
    
    if (port == 80) {

        char    ip[15];
        sprintf(ip, "%s", data->ip);
        char *http = "GET / HTTP/1.1\r\nHost: ";
        char *http_request = malloc(sizeof(char *) + (strlen(ip) + strlen(http)) + 1);

        strcpy(http_request, http); 
        strcat(http_request, ip);
        strcat(http_request, "\r\n\r\n");

        if (send(sock, http_request, strlen(http_request), 0) < 0) {
            perror("Erreur send request");
            close(sock);
            free(http_request);
            return (false);
        }
        char response[4096];
        size_t  bytes_received = recv(sock, response, sizeof(response), 0);
        
        if (bytes_received > 0) {
            printf("%sREPLY TO THE REQUEST : %s\n\n\n", GREEN, RESET_COLOR);
            printf("%s\n", response);
        }
        else if (bytes_received == 0)
            return (false);
        free(http_request);
    }
    else
        return (false);
    return (true); 
}

/* Make a request with a string yoooo, but unreliable */
void    RequestBanner(int sock, t_data *data, struct sockaddr_in sa) {

    char buffer[4096];
    struct hostent *server;
    int n;

    server = gethostbyname(data->ip);
    memcpy(&sa.sin_addr.s_addr, server->h_addr, server->h_length);

	memset(buffer, 0, sizeof(buffer));
	strcpy(buffer, "yoooo\r\n");

	n = write(sock, buffer, strlen(buffer));
	if(n < 0)
		return;
	
	bzero(buffer, 4096);
	n = read(sock, buffer, 4096);
	if(n < 0)
		return;
    fprintf(stdout,"%s\n", buffer);
}