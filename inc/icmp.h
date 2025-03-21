#ifndef ICMP_H
#define ICMP_H

#include <stdint.h>

/*
 * ICMP Header (RFC 792)
 * ---------------------
 * This structure defines the layout of the Internet Control Message Protocol (ICMP) header.
 * Commonly used for messages such as Echo Request (type = 8) and Echo Reply (type = 0).
 *
 * Total size: 8 bytes (for Echo messages)
 */

typedef struct s_icmp_header {
    uint8_t  type;        // ICMP message type (e.g., 8 = Echo Request, 0 = Echo Reply)
    uint8_t  code;        // Subtype code (depends on the type)
    uint16_t checksum;    // Error-checking for the ICMP header and payload

    // Used for Echo Request/Reply (can be ignored for other types)
    uint16_t identifier;  // Identifier to match requests/replies (often set to process ID)
    uint16_t sequence;    // Sequence number to match individual packets
} t_icmp_header;

#endif
