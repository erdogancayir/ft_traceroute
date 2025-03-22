#include "traceroute.h"

int main(int ac, char **av)
{
    if (ac < 2)
    {
        fprintf(stderr, "Usage: %s <target_ip_or_hostname>\n", av[0]);
        return EXIT_FAILURE;
    }

    // Check for --help
    if (strcmp(av[1], "--help") == 0)
    {
        print_help(av[0]);
        return EXIT_SUCCESS;
    }

    t_flag flags;
    char *target_hostname = NULL;

    if (create_flag(ac, av, &flags, &target_hostname) < 0)
        return EXIT_FAILURE;

    char *resolvedAddress = NULL;
    int result = resolve_destination(target_hostname, &resolvedAddress);
    if (result == 0 || resolvedAddress == NULL)
    {
        fprintf(stderr, "Failed to resolve the target address\n");
        return EXIT_FAILURE;
    }

    t_traceroute *tr = init_traceroute(resolvedAddress, target_hostname, &flags);
    if (!tr)
    {
        fprintf(stderr, "Failed to initialize traceroute.\n");
        free_traceroute(tr);
        return EXIT_FAILURE;
    }

    if (run_traceroute(tr) < 0)
    {
        fprintf(stderr, "Traceroute failed.\n");
        free_traceroute(tr);
        return EXIT_FAILURE;
    }
}

void print_help(char *program_name)
{
    printf("Usage: %s [options] <target_ip_or_hostname>\n\n", program_name);
    printf("Options:\n");
    printf("  --help           Show this help message and exit.\n");
    printf("  -m <ttl>         Set maximum number of hops (max TTL).\n");
    printf("  -q <count>       Set number of queries per hop.\n");
    printf("  -t <timeout>     Set timeout per probe in milliseconds.\n");
    printf("  -p <port>        Set starting destination port (default: 33434).\n");
    printf("  -n               Do not resolve IP addresses to their domain names.\n");
}