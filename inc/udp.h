#ifndef UDP_H
#define UDP_H

#include <stdint.h>

#define PAYLOAD_SIZE 1
#define UDP_HEADER_SIZE sizeof(t_udp_header)
#define IP_HEADER_SIZE sizeof(t_ip_header)

// UDP Header
typedef struct s_udp_header {
    uint16_t src_port;  // Source port
    uint16_t dest_port; // Destination port
    uint16_t length;    // Header + payload length
    uint16_t checksum;  // Checksum
} t_udp_header;

/*
 * UDP Header Details:
 * -------------------
 * - The UDP (User Datagram Protocol) header is a Layer 4 (Transport Layer) structure.
 * - It is used for connectionless, unreliable communication between hosts.
 * - The header is minimalistic, consisting of only 8 bytes, with no mechanisms for retransmission or flow control.

 * Fields:
 * -------
 * 1. src_port (16 bits):
 *    - The source port number.
 *    - Identifies the sending application.
 *    - Typically, it is dynamically assigned for client-side applications.
 *    - Range: 0–65535.
 *        - Ports 0–1023: Well-known ports (e.g., 53 for DNS).
 *        - Ports 1024–49151: Registered ports.
 *        - Ports 49152–65535: Dynamic/private ports.

 * 2. dest_port (16 bits):
 *    - The destination port number.
 *    - Identifies the receiving application or service.
 *    - Examples:
 *        - 53: DNS server.
 *        - 123: NTP server.

 * 3. length (16 bits):
 *    - Specifies the total length of the UDP packet, including the header and payload.
 *    - Minimum value: 8 bytes (header-only, no payload).
 *    - Maximum value: 65535 bytes (although it is limited by the IP packet size).

 * 4. checksum (16 bits):
 *    - Used for error-checking the header and payload.
 *    - Calculated over a pseudo-header (from the IP header), the UDP header, and the payload.
 *    - If the checksum is set to 0, it indicates no checksum is being used (optional in IPv4, mandatory in IPv6).

 * Pseudo-Header:
 * --------------
 * - The UDP checksum calculation includes a pseudo-header from the IP layer:
 *    - Source IP address.
 *    - Destination IP address.
 *    - Protocol (set to 17 for UDP).
 *    - UDP length.

 * Usage:
 * ------
 * - UDP is commonly used in scenarios where low latency and simplicity are prioritized over reliability.
 * - Examples:
 *     - DNS (Domain Name System).
 *     - VoIP (Voice over IP).
 *     - Streaming services.
 *     - DHCP (Dynamic Host Configuration Protocol).
 */

#endif
