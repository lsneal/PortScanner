# Port Scanner with Banner Grabbing

It's a simple port scanner, with the added feature of banner grabing, which retrieves the service banner corresponding to the port requested by the user.

I did this project to learn the basics of network programming in C, and to learn how to send specific requests to certain services, such as HTTP

## Port Scanning:
- The program uses the TCP three-way handshake to determine the status of a port on the target machine.
- It sends a SYN (synchronization) packet to the specified IP address and port.
- If the port is open, the target machine responds with a SYN-ACK (synchronization-acknowledgment) packet.
- If the port is closed, the target machine responds with a RST (reset) packet.


## Banner Grabbing:
After successfully establishing a connection, the program attempts to retrieve information about the service associated with the open port.
It uses the getservbyport function to obtain service details.


## Dependencies:
The program relies on standard C libraries for socket programming and network operations.


## Notes:
This project is intended for educational purposes.
Ensure you have the necessary permissions before scanning any network.
