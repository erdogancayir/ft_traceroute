#include "flag.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

// Function to initialize traceroute flags
int create_flag(int ac, char **av, t_flag *flags, char **target_hostname)
{
    // Set defaults
    flags->max_ttl = 30;
    flags->query_count = 3;
    flags->timeout = 1000;
    flags->start_port = 33434;
    flags->numeric_output_only = 1;

    for (int i = 1; i < ac; i++)
    {
        if (strcmp(av[i], "--help") == 0)
        {
            // already handled in main
            continue;
        }
        else if (strcmp(av[i], "-m") == 0 && i + 1 < ac)
        {
            flags->max_ttl = atoi(av[++i]);
        }
        else if (strcmp(av[i], "-q") == 0 && i + 1 < ac)
        {
            flags->query_count = atoi(av[++i]);
        }
        else if (strcmp(av[i], "-t") == 0 && i + 1 < ac)
        {
            flags->timeout = atoi(av[++i]);
        }
        else if (strcmp(av[i], "-p") == 0 && i + 1 < ac)
        {
            flags->start_port = atoi(av[++i]);
        }
        else if (strcmp(av[i], "-n") == 0)
        {
            flags->numeric_output_only = 0;
        }
        else if (av[i][0] != '-' && i == ac - 1)
        {
            *target_hostname = av[i]; // target is last non-option
        }
        else
        {
            fprintf(stderr, "Unknown or malformed option: %s\n", av[i]);
            return -1;
        }
    }

    if (!*target_hostname)
    {
        fprintf(stderr, "Error: No target specified.\n");
        return -1;
    }

    return 0;
}

