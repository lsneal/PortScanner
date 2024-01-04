#include "Scanner.h"

void ScanSimplePort(t_data *data) {

    struct sockaddr_in sa;
    struct servent     *service = {0};
    int sock, rtn;

    // Check si l'ip est valide
    if (inet_addr(data->ip) == INADDR_NONE) {
        printf("Invalid IP : %s\n", data->ip);
        return;
    }

    // init la strut sockaddr
    memset(&sa, 0, sizeof(sa));

    // AF_INET == ipv4
    sa.sin_family = AF_INET;

    // convertit le format string de l'ip en format ip (inet_addr)
    sa.sin_addr.s_addr = inet_addr(data->ip);

    // mettre le port au format reseau 16bits
    sa.sin_port = htons(data->port);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        // afficher une erreur en cas d'echec de la creation du socket
        perror("socket");
        return;
    }

    // tente de se co a l'ip secifique et au port
    rtn = connect(sock, (struct sockaddr*)&sa, sizeof(sa));

    if (rtn == 0) {
        service = getservbyport(htons(data->port), NULL);
        if (!service) 
            printf("Port => %s%d%s : Status => %sopen%s : Service => %sunknown%s\n", MAGENTA, data->port, RESET_COLOR, GREEN, RESET_COLOR, YELLOW, RESET_COLOR);
        else
            printf("Port => %s%d%s : Status => %sopen%s : Service => %s%s%s\n", MAGENTA, data->port, RESET_COLOR, GREEN, RESET_COLOR, YELLOW, service->s_name, RESET_COLOR);
    }
    else {
        printf("Port => %s%d%s : Status => closed\n", MAGENTA, data->port, RESET_COLOR);
    }
    close(sock);
}

void *ScanMultiPort(void *arg) {

    t_data *data = (t_data *)arg;
    struct sockaddr_in sa;
    struct servent     *service = {0};
    int portNum;
    int rtn;
    int sockfd;

    memset(&sa, 0, sizeof(sa));
    while (1) {

        pthread_mutex_lock(&data->mutex);
        portNum = data->PortIndex;
        data->PortIndex++;
        if (data->PortIndex > data->portEnd) {
            pthread_mutex_unlock(&data->mutex);
            break ;
        }
        pthread_mutex_unlock(&data->mutex);

        sockfd = socket(AF_INET, SOCK_STREAM, 0);
        if (sockfd < 0) {
            perror("Error opening socket");
            continue ;
        }

        sa.sin_family = AF_INET;
        sa.sin_addr.s_addr = inet_addr(data->ip);
        sa.sin_port = htons(portNum);

        rtn = connect(sockfd, (struct sockaddr *)&sa, sizeof(sa));

    if (rtn == 0) {
        service = getservbyport(htons(portNum), NULL);
        if (!service) 
            printf("Port => %s%d%s : Status => %sopen%s : Service => %sunknown%s\n", MAGENTA, portNum, RESET_COLOR, GREEN, RESET_COLOR, YELLOW, RESET_COLOR);
        else
            printf("Port => %s%d%s : Status => %sopen%s : Service => %s%s%s\n", MAGENTA, portNum, RESET_COLOR, GREEN, RESET_COLOR, YELLOW, service->s_name, RESET_COLOR);
    }
        close(sockfd);
    }
    return (NULL);
}

void    ScanBanner(t_data *data) {

    struct sockaddr_in sa;
    int sock, rtn;

    if (inet_addr(data->ip) == INADDR_NONE) {
        printf("Invalid IP : %s\n", data->ip);
        return;
    }

    memset(&sa, 0, sizeof(sa));

    sa.sin_family = AF_INET;
    sa.sin_addr.s_addr = inet_addr(data->ip);
    sa.sin_port = htons(data->port);

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("socket");
        return;
    }
    rtn = connect(sock, (struct sockaddr*)&sa, sizeof(sa));
    if (rtn == 0) {
        if (data->port != 80)
            RequestBanner(sock, data, sa);
        else if (HttpRequest(data->port, sock, data) == false)
            fprintf(stderr, "Error scan banner\n");   
    }
    else 
        printf("Port => %d is closed\n", data->port);
    close(sock);
}