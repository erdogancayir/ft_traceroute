#include <sys/time.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include "traceroute.h"
#include "icmp.h"

#include "ip.h"

int recv_icmp_reply(t_traceroute *tr, struct timeval *start,
                    char *ip_str, size_t ip_str_len, double *rtt_out)
{
    char buffer[512];
    struct sockaddr_in sender;
    socklen_t sender_len = sizeof(sender);

    struct timeval timeout;
    timeout.tv_sec = tr->flags.timeout / 1000;
    timeout.tv_usec = (tr->flags.timeout % 1000) * 1000;

    fd_set read_fds;
    FD_ZERO(&read_fds);
    FD_SET(tr->icmp_socket_fd, &read_fds);

    int ready = select(tr->icmp_socket_fd + 1, &read_fds, NULL, NULL, &timeout);
    if (ready <= 0)
        return 0;

    ssize_t len = recvfrom(tr->icmp_socket_fd, buffer, sizeof(buffer), 0,
                           (struct sockaddr *)&sender, &sender_len);
    if (len < 0)
        return -1;

    struct timeval end;
    gettimeofday(&end, NULL);

    *rtt_out = (end.tv_sec - start->tv_sec) * 1000.0 +
               (end.tv_usec - start->tv_usec) / 1000.0;

    inet_ntop(AF_INET, &(sender.sin_addr), ip_str, ip_str_len);

    t_ip_header *ip_hdr = (t_ip_header *)buffer;
    int ip_header_len = (ip_hdr->version_ihl & 0x0F) * 4;
    t_icmp_header *icmp_hdr = (t_icmp_header *)(buffer + ip_header_len);

    if (icmp_hdr->type == ICMP_TIME_EXCEEDED)
    {
        return 1;
    }
    else if (icmp_hdr->type == ICMP_DEST_UNREACH)
    {
        tr->destination_reached = 1;
        return 1;
    }

    return 0;
}
