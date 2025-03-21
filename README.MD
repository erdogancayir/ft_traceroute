# 🌍 Traceroute (C Implementation)

A full implementation of the classic `traceroute` utility in C, using raw sockets to trace the path to a destination host by sending UDP packets and receiving ICMP responses from intermediate routers.

---

## 🚀 Features

- **Raw UDP Packet Sending** using incrementally increasing TTL
- **ICMP Response Handling** (Time Exceeded, Destination Unreachable)
- **RTT Measurement** for each probe
- **Reverse DNS Resolution** (optional with `-n` flag)
- **Verbose Logging and Configurable Flags**
- Output mimics the native `traceroute` utility

---

## ⚙️ Building & Running

### Compile:
```bash
make
```

### Run:
```bash
sudo ./traceroute [options] <target>
```

> Note: `sudo` is required to use raw sockets.

---

## 🧪 Example Output

```bash
sudo ./traceroute google.com
```
```
traceroute to google.com (142.251.140.14), 30 hops max, 60 byte packets
 1  _gateway (192.168.1.1)  1.76 ms  1.51 ms  1.74 ms  
 2  * * *  
 3  fra16s41-in-f14.1e100.net (142.250.74.78)  12.9 ms  13.2 ms  12.7 ms  
```
Use `-n` to disable DNS resolution and print IPs only.

---

## 🧩 Supported Flags

| Flag           | Description                                         |
|----------------|-----------------------------------------------------|
| `--help`       | Show usage information                              |
| `-m <ttl>`     | Set max TTL (hops), default: `30`                   |
| `-q <count>`   | Probes per hop, default: `3`                        |
| `-t <timeout>` | Timeout per probe in milliseconds, default: `1000` |
| `-p <port>`    | Starting destination port, default: `33434`         |
| `-n`           | Disable DNS resolution (show IPs only)              |

---

## 🧠 How It Works

1. **UDP Packet Construction:** A raw socket sends UDP packets to a closed port with increasing TTL.
2. **ICMP Listening:** Another socket listens for ICMP `Time Exceeded` or `Destination Unreachable` responses.
3. **RTT Calculation:** The round-trip time is measured with `gettimeofday()`.
4. **DNS Lookup:** `getnameinfo()` is used for reverse DNS (unless `-n` is used).
5. **Logging:** Results per hop and per query are printed in traceroute format.

---

## 🧵 Technical Details

- Raw UDP socket: `socket(AF_INET, SOCK_RAW, IPPROTO_UDP)`
- ICMP listener: `socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)`
- Custom IP & ICMP header parsing using defined structs
- Timeout control via `select()`
- DNS resolution via `getnameinfo()` (optional)

---

## 🛠️ Makefile Usage

```bash
make        # Build the project
make clean  # Remove object files
make fclean # Remove object files & binary
make re     # Rebuild everything
```

Also includes a colorful banner upon build for better terminal visibility.

---

## 🎁 Bonus Features

- `-v` Verbose logging
- `-n` Disable reverse DNS lookup
- `-m`, `-q`, `-t`, `-p` flags fully supported
- `--help` with complete usage guide
- Colorful build banner via `Makefile`

---

## ✅ Sample Run

```bash
sudo ./traceroute -m 20 -q 3 -n google.com
```
```
traceroute to google.com (142.251.140.14), 20 hops max, 60 byte packets
 1  192.168.1.1  1.51 ms  1.52 ms  1.54 ms
 2  * * *
 3  142.250.74.78  13.2 ms  12.7 ms  12.9 ms
```

---

## 👨‍💻 Developer Notes

This project was developed to provide hands-on experience with:

- Low-level networking
- Packet inspection
- Raw socket programming
- ICMP and DNS systems
- CLI tool development in C

It mirrors the system's `traceroute` output with full flag and feature support.

---

## 📜 License

MIT License

---

## 🔗 References

- [RFC 792 - ICMP](https://tools.ietf.org/html/rfc792)
- [Linux Raw Sockets](https://man7.org/linux/man-pages/man7/raw.7.html)
- [Raw Sockets](https://medium.com/@erdogancayir/raw-socketler-kullan%C4%B1m%C4%B1-raw-sockets-89f65d8ce063)
- `man traceroute`, `man getnameinfo`, `man select`

---

> "Traceroute is not just about destinations, it's about the journey of your packets." 🚀

