#include "traceroute.h"
#include "network.h"

#include "sys/time.h"
#include "netinet/in.h"

int send_udp_probe(t_traceroute *tr, int seq, int ttl)
{
    if (!tr || !tr->network)
        return -1;

    // Dynamic port for each probe
    int port = tr->flags.start_port + ttl + seq;
    tr->network->dest_addr.sin_port = htons(port);

    // Send 1-byte payload
    char payload = 0;
    ssize_t sent = sendto(tr->udp_socket_fd, &payload, sizeof(payload), 0,
                          (struct sockaddr *)&tr->network->dest_addr,
                          sizeof(tr->network->dest_addr));

    if (sent < 0)
    {
        perror("sendto failed");
        return -1;
    }

    return 0; // success
}
