#ifndef IP_H
#define IP_H

#include <stdint.h>

/*
 * IPv4 Header (Layer 3 - Network Layer)
 * -------------------------------------
 * This struct defines the IPv4 packet header, which is always 20 bytes minimum.
 * Each field matches the RFC 791 IPv4 header specification.
 */

typedef struct s_ip_header {
    uint8_t  version_ihl;     // Version (4 bits) + Internet Header Length (4 bits)
    uint8_t  tos;             // Type of Service
    uint16_t total_length;    // Total length of the packet (header + data)
    uint16_t id;              // Unique ID for fragmentation
    uint16_t frag_offset;     // Flags (3 bits) + Fragment offset (13 bits)
    uint8_t  ttl;             // Time to Live
    uint8_t  protocol;        // Upper layer protocol (ICMP=1, TCP=6, UDP=17)
    uint16_t checksum;        // Header checksum
    uint32_t src_ip;          // Source IP address (network byte order)
    uint32_t dest_ip;         // Destination IP address (network byte order)
} t_ip_header;

/*
 * IP Header Details:
 * ------------------
 * - The IP header is a Layer 3 (Network Layer) structure used in IPv4 protocol.
 * - It specifies how packets are routed across the network.
 * - This header is part of every IPv4 packet, preceding the payload (e.g., TCP/UDP data).

 * Fields:
 * -------
 * 1. version_ihl (8 bits):
 *    - The first 4 bits: IP version (IPv4 = 4).
 *    - The next 4 bits: Header length (number of 32-bit words; minimum = 5, meaning 20 bytes).

 * 2. tos (8 bits):
 *    - Type of Service (QoS - Quality of Service).
 *    - Specifies priority and handling requirements for the packet.
 *    - Examples:
 *        - Low delay.
 *        - High throughput.

 * 3. total_length (16 bits):
 *    - Total size of the IP packet, including the header and payload, in bytes.
 *    - Minimum: 20 bytes (header-only).
 *    - Maximum: 65,535 bytes.

 * 4. id (16 bits):
 *    - A unique identifier for the packet.
 *    - Used for reassembling fragmented packets.

 * 5. frag_offset (16 bits):
 *    - Specifies the position of this fragment in the original packet.
 *    - Used for packet fragmentation and reassembly.
 *    - Includes flags in the higher bits (e.g., "Don't Fragment", "More Fragments").

 * 6. ttl (8 bits):
 *    - Time to Live.
 *    - A counter decremented by each router.
 *    - If TTL reaches zero, the packet is discarded to prevent infinite loops.

 * 7. protocol (8 bits):
 *    - Specifies the transport layer protocol carried in the payload.
 *    - Examples:
 *        - ICMP: 1
 *        - TCP: 6
 *        - UDP: 17

 * 8. checksum (16 bits):
 *    - Error-checking mechanism for the header.
 *    - Ensures the integrity of the header data.

 * 9. src_ip (32 bits):
 *    - Source IP address (in network byte order).

 * 10. dest_ip (32 bits):
 *    - Destination IP address (in network byte order).

 * Usage:
 * ------
 * - This header is parsed by routers to forward the packet to the correct destination.
 * - The version_ihl and protocol fields help determine how the packet is processed.
 */

int create_ip_header(t_ip_header *ip, const char *src_ip, const char *dest_ip, int ttl);
void log_ip(t_ip_header *ip_hdr);


#endif
