#include "Scanner.h"

int main(int argc, char **argv) {

    t_data  data;
    
    if (argc == 2) {
        printf("./scan %s--help%s\n", CYAN, RESET_COLOR);
        if (strcmp(argv[1], "--help") == 0)
            DisplayCustomerHelp();
        return (1);
    }
    if (argc != 3 && argc != 4) {
        fprintf(stderr, "%sError%s : ./scan <%sIP%s> <%sMODE%s> <%sPORT%s>\n", RED, RESET_COLOR, CYAN, RESET_COLOR, GREEN, RESET_COLOR, MAGENTA, RESET_COLOR);
        fprintf(stderr, "For mode help : ./scan --help\n");
        return (1);
    }
    InitData(argv[1], &data);
    pthread_mutex_init(&data.mutex, NULL);
    pthread_mutex_init(&data.mutexServices, NULL);
    ParseAndScan(argc, argv, data);
    DeleteData(&data);
    return (0);
}


bool    ParseAndScan(int argc, char **argv, t_data data) {
   
    if (Parsing(argc, argv, &data) == 404) {
        fprintf(stderr, "%sError%s : ./executable <%sIP%s> <%sMODE%s> <%sPORT%s>\n", RED, RESET_COLOR, CYAN, RESET_COLOR, GREEN, RESET_COLOR, MAGENTA, RESET_COLOR);
        return (false);
    }
    else if (Parsing(argc, argv, &data) == -1) {
        fprintf(stderr, "%sError%s: port min < %s1%s > and port max < %s65536%s >", RED, RESET_COLOR, GREEN, RESET_COLOR, MAGENTA, RESET_COLOR);        
        return (false);
    }
    else if (Parsing(argc, argv, &data) == 1) {
        ScanSimplePort(&data);
    }
    else if (Parsing(argc, argv, &data) == 2) {
        for (int i = 0; i < NUM_THREADS; i++)
            pthread_create(&data.threads[i], NULL, ScanMultiPort, &data);
        for (int i = 0; i < NUM_THREADS; i++)
            pthread_join(data.threads[i], NULL);
    }
    else if (Parsing(argc, argv, &data) == 3) {
        ScanBanner(&data);
    }
    return (true);
}