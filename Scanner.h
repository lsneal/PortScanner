#ifndef SCANNER_H
#define SCANNER_H

#include <sys/socket.h>
#include <errno.h>
#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>

#define RESET_COLOR "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN "\033[36m"
#define WHITE "\033[37m"

#define NUM_THREADS 4
#define NUM_PORT 65536

typedef struct s_data {

    char    *ip;
    int     port;
    int     portStart;
    int     portEnd;

    //////////////////////////

    int             PortIndex;
    pthread_t       *threads;
    pthread_mutex_t mutex;
    pthread_mutex_t mutexServices;

}               t_data;

void    InitData(char *ip_arg, t_data *data);
void    DeleteData(t_data *data);

bool    ParseAndScan(int argc, char **argv, t_data data);
int     Parsing(int argc, char **argv, t_data *data);

void    ScanSimplePort(t_data *data);
void    *ScanMultiPort(void *arg);

void    DisplayPortService(int port, t_data *data);
void    DisplayCustomerHelp();


bool    HttpRequest(int port, int sock, t_data *data);
void    ScanBanner(t_data *data);
void    RequestBanner(int sock, t_data *data, struct sockaddr_in sa);

#endif