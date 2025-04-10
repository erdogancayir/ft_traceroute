#ifndef NETWORK_H
#define NETWORK_H

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>

typedef struct s_network
{
    char *hostname;
    char *target_ip;                    // Resolved IP string
    struct sockaddr_in dest_addr;      // sockaddr for sendto
    in_addr_t dest_ip_bin;             // Binary IP (network byte order)
    uint16_t dest_port;                // Destination port (default 33434)
} t_network;

t_network *create_network(const char *target_ip);


#endif
