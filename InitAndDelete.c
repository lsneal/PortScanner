#include "Scanner.h"

void    InitData(char *ip_arg, t_data *data) {

    data->ip = strdup(ip_arg);
    data->port = -1;
    data->portStart = -1;
    data->portEnd = -1;
    data->PortIndex = 1;
    data->threads = calloc(sizeof(pthread_t *), NUM_THREADS);

}

void    DeleteData(t_data *data) {

    pthread_mutex_destroy(&data->mutex);
    free(data->ip);
    free(data->threads);

}