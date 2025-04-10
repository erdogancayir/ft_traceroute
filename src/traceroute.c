#include "traceroute.h"
#include "flag.h"
#include "network.h"
#include "sys/time.h"
#include "netinet/in.h"
#include <netinet/ip_icmp.h>
#include <netinet/ip.h>
#include <unistd.h>

t_traceroute *init_traceroute(const char *target_ip, char *hostname, t_flag *flags)
{
    t_traceroute *tr = calloc(1, sizeof(t_traceroute));
    if (!tr)
    {
        perror("Failed to allocate memory for traceroute");
        return NULL;
    }

    tr->current_ttl = 1;

    tr->destination_reached = 0;

    tr->udp_socket_fd = create_udp_socket(tr->current_ttl);
    if (tr->udp_socket_fd < 0)
        return NULL;

    tr->icmp_socket_fd = create_icmp_socket();
    if (tr->icmp_socket_fd < 0)
        return NULL;

    tr->flags = *flags;

    tr->network = create_network(target_ip);
    if (!tr->network)
    {
        perror("Failed to allocate memory for network");
        return NULL;
    }

    tr->network->src_ip = 

    tr->network->hostname = hostname;

    return tr;
}

int run_traceroute(t_traceroute *tr)
{
    printf("traceroute to %s (%s), %d hops max, %d byte packets\n",
           tr->network->hostname, tr->network->target_ip, tr->flags.max_ttl, 60);

    for (int ttl = 1; ttl <= tr->flags.max_ttl; ttl++)
    {
        tr->current_ttl = ttl;
        printf("%2d  ", ttl);

        if (setsockopt(tr->udp_socket_fd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0)
        {
            perror("setsockopt failed");
            close(tr->icmp_socket_fd);
            return -1;
        }

        int received = 0;
        char last_ip[INET_ADDRSTRLEN] = "";
        double rtts[tr->flags.query_count];
        char last_host[NI_MAXHOST] = "";

        for (int query = 0; query < tr->flags.query_count; query++)
        {
            struct timeval start;
            gettimeofday(&start, NULL);

            if (send_udp_probe(tr, query, ttl) < 0)
            {
                rtts[query] = -1;
                continue;
            }

            char ip_str[INET_ADDRSTRLEN] = "";
            double rtt_ms = 0;

            int reply = recv_icmp_reply(tr, &start, ip_str, sizeof(ip_str), &rtt_ms);
            if (reply == 1)
            {
                received = 1;
                if (strlen(last_ip) == 0)
                {
                    strncpy(last_ip, ip_str, sizeof(last_ip));

                    if (tr->flags.numeric_output_only)
                    {
                        struct sockaddr_in sa;
                        sa.sin_family = AF_INET;
                        inet_pton(AF_INET, ip_str, &sa.sin_addr);

                        struct hostent *he = gethostbyaddr(&sa.sin_addr, sizeof(sa.sin_addr), AF_INET);
                        if (he && he->h_name)
                            strncpy(last_host, he->h_name, sizeof(last_host));
                        else
                            strncpy(last_host, ip_str, sizeof(last_host));
                    }
                    else
                    {
                        strncpy(last_host, ip_str, sizeof(last_host));
                    }
                }
                rtts[query] = rtt_ms;
            }
            else
            {
                rtts[query] = -1;
            }
        }

        if (received)
        {
           if (tr->flags.numeric_output_only && strcmp(last_ip, last_host) != 0)
                printf("%s (%s)  ", last_host, last_ip);
            else
                printf("%s  ", last_ip);

            for (int i = 0; i < tr->flags.query_count; i++)
            {
                if (rtts[i] < 0)
                    printf("* ");
                else
                    printf("%.3f ms  ", rtts[i]);
            }
        }
        else
        {
            for (int i = 0; i < tr->flags.query_count; i++)
                printf("* ");
        }

        printf("\n");

        if (received && tr->destination_reached)
            break;
    }

    close(tr->icmp_socket_fd);
    return 0;
}


void free_traceroute(t_traceroute *tr)
{
    if (tr)
    {
        if (tr->network)
        {
            if (tr->network->target_ip)
                free(tr->network->target_ip);

            free(tr->network);
        }
        
        free(tr);
    }
}