#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <netdb.h>

int resolve_destination(const char *inputTargetAddress, char **resolvedAddress)
{
    struct in_addr addr;
    struct hostent *host;

    // Check if the input is already an IP address
    if (inet_pton(AF_INET, inputTargetAddress, &addr) == 1)
    {
        *resolvedAddress = strdup(inputTargetAddress);
        return 1;
    }

    // Resolve the hostname
    host = gethostbyname(inputTargetAddress);
    if (host != NULL)
    {
        *resolvedAddress = strdup(inet_ntoa(*(struct in_addr *)host->h_addr));
        return 1;
    }

    return 0; // Resolution failed
}