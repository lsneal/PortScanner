#include "Scanner.h"

static bool ParseWithModeRange(char *range, t_data *data) {

    char *port = strtok(range, "-");

    if (port != NULL)
        data->portStart = atoi(port);
    if (data->portStart <= 0 || data->portStart > 65536) {
        return (false);
    }

    port = strtok(NULL, "-");

    if (port != NULL) 
        data->portEnd = atoi(port);
    if (data->portEnd <= 0 || data->portEnd > 65536 || data->portEnd <= data->portStart) {
        return (false);
    }
    return (true);
}

static bool    ParseNoMode(char *portNumber, t_data *data) {

    data->port = atoi(portNumber);
    if (data->port <= 0 || data->port > 65536)
        return (false);
    return (true);
}

int    Parsing(int argc, char **argv, t_data *data) {

    if (argc == 3) {
        if (ParseNoMode(argv[2], data) == false) {
            return (-1);
        }
        return (1);
    }
    else if (argc == 4) {
        if (strcmp(argv[2], "-r") == 0) {
            if (ParseWithModeRange(argv[3], data) == false) {
                return (-1);
            }
        }
        else if (strcmp(argv[2], "-b") == 0) {
            if (ParseNoMode(argv[3], data) == false) {
                return (-1);
            }
            return (3);
        }
        else
            return (404);
        return (2);
    }
    return (0);
}

struct Command {
    const char *name;
    const char *description;
};

struct Command commands[] = {
    {"./scan <IP> <PORT>", "Scan just one port"},
    {"./scan <IP> -r <RANGE> 1-65536", "Scan ports in the two-number range "},
    {"./scan <IP> -b <PORT>", "Scan and display a port service banner (if available). Currently only works for port 80"}
};

void    DisplayCustomerHelp() {

    printf("\nList commands available:\n\n");
    for (unsigned int i = 0; i < (int)sizeof(commands) / sizeof(commands[0]); i++) {
        printf("%s - %s\n", commands[i].name, commands[i].description);
    }
}
