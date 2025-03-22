#ifndef FLAGS_H
#define FLAGS_H

#define ICMP_ECHOREPLY      0  // Not used in classic traceroute
#define ICMP_DEST_UNREACH   3  // Destination unreachable (final hop)
#define ICMP_TIME_EXCEEDED 11  // TTL expired in transit (intermediate hop)


// State flags for traceroute
typedef struct s_flag {
    int max_ttl;          // -m <ttl>
    int query_count;      // -q <count>
    int timeout;          // -t <timeout>
    int start_port;       // -p <port>
    int numeric_output_only;    //-n
} t_flag;


int create_flag(int ac, char **av, t_flag *flags, char **target_hostname);

#endif