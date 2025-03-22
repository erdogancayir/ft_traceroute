#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <netdb.h>

int resolve_destination(const char *inputTargetAddress, char **resolvedAddress)
{
    struct in_addr addr;
    struct addrinfo hints, *res;

    // Check if the input is already an IP address
    if (inet_pton(AF_INET, inputTargetAddress, &addr) == 1)
    {
        *resolvedAddress = strdup(inputTargetAddress);
        return 1;
    }

    // Prepare the hints struct for getaddrinfo
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET; // Only allow IPv4 addresses
    hints.ai_socktype = SOCK_DGRAM; // Datagram socket (e.g., UDP), common for name resolution

    // Try to resolve the hostname to an IP address
    if (getaddrinfo(inputTargetAddress, NULL, &hints, &res) != 0)
        return 0;

    // Extract the first IPv4 address result
    struct sockaddr_in *addr_in = (struct sockaddr_in *)res->ai_addr;

    // inet_ntoa() = "network to ASCII" (binary to string, e.g., 142.250.74.78)
    *resolvedAddress = strdup(inet_ntoa(addr_in->sin_addr));

    freeaddrinfo(res);

    return (*resolvedAddress != NULL);
}