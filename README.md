# rtos_assignment1

There are only two files, server.c and client.c for half duplex connection. Run the server.c in the cloud and client.c in your perosnal laptop.
Usage :: gcc server.c ------- compile the server.c file on the cloud computer
         ./a.out <port_no> ------- run the server.c first using some port number
         
         gcc client.c ------- compile the client.c file on your personal computer
         ./a.out <IP_address> <port_no> ------- run the client.c using the public IP address of the cloud computer and same port number
         
         Now, One way connection has been established.
