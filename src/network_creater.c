#include "traceroute.h"
#include "network.h"

#include "traceroute.h"
#include "network.h"

t_network *create_network(const char *target_ip)
{
    t_network *network = calloc(1, sizeof(t_network));
    if (!network)
    {
        perror("Failed to allocate memory for network");
        return NULL;
    }

    network->target_ip = strdup(target_ip);
    if (!network->target_ip)
    {
        perror("Failed to allocate memory for target IP");
        free(network);
        return NULL;
    }
    

    struct addrinfo hints, *res = NULL;
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // IPv4
    hints.ai_socktype = SOCK_DGRAM;

    int err = getaddrinfo(target_ip, NULL, &hints, &res);
    if (err != 0 || !res)
    {
        fprintf(stderr, "getaddrinfo() failed: %s\n", gai_strerror(err));
        free(network->target_ip);
        free(network);
        return NULL;
    }

    // Fill destination address
    struct sockaddr_in *addr = (struct sockaddr_in *)res->ai_addr;
    network->dest_addr = *addr;
    network->dest_ip_bin = addr->sin_addr.s_addr;

    network->dest_port = 33434; // Default traceroute starting port
    network->dest_addr.sin_port = htons(network->dest_port);

    freeaddrinfo(res);

    return network;
}
