#ifndef TRACEROUTE_H
#define TRACEROUTE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "flag.h"

typedef struct s_traceroute_result {
    int udp_socket_fd;
    int icmp_socket_fd;

    int current_ttl;

    struct s_network *network;


    int destination_reached;

    t_flag flags;
} t_traceroute;

t_traceroute *init_traceroute(const char *target_ip, char *hostname, t_flag *flags);

int resolve_destination(const char *inputTargetAddress, char **resolvedAddress);

int create_udp_socket(int ttl);
int create_icmp_socket();
void free_traceroute(t_traceroute *tr);

int run_traceroute(t_traceroute *tr);

int send_udp_probe(t_traceroute *tr, int seq, int ttl);
int recv_icmp_reply(t_traceroute *tr, struct timeval *start, char *ip_str, size_t ip_str_len, double *rtt_out);


int find_source_ip(char **source_ip, const char *dest_ip);


#endif