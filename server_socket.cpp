//
// Created by papraczy on 01/11/2019.
//

#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <zconf.h>
#include <iostream>
using namespace std;

#include "server_socket.h"
#include "SafeQueue.h"

#define PORT 7772

/*
 * Create a TCP socket of type IPv4
 * */
int Server_socket::create_socket() {
    //AF_INET- IPv4, SOCK_STREAM- TCP socket, 0- IP
    this->server_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (this->server_socket == -1) {
        cout << "Could not create socket";
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Server_socket::bind_socket() {
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    inet_pton(AF_INET, "192.168.1.1", &(address.sin_addr.s_addr));

    //Bind
    if (bind(this->server_socket, (struct sockaddr *) &address,
             sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    return 0;
}

int Server_socket::listen_accept() {
    cout << "listening: " << endl;
    if (listen(this->server_socket, 1) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    struct sockaddr  client_addr;     // address of the client
    socklen_t client_addr_len = sizeof(client_addr);  // length of the address
    cout << "accepting: ";
    if((this->new_socket = accept(this->server_socket, &client_addr,
                             &client_addr_len)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    cout << "Receieved this: ";
    while(true){
        int buffer[1024] = {0};
        int valread = read( new_socket , buffer, 512);
        for(int i = 0; i < sizeof(buffer)/sizeof(buffer[0]); i++){
            cout << buffer[i];
        }
        cout << endl;
    }
    cout << "Received some stuff\n";
    return 0;
}

Server_socket::Server_socket() {
    this->data_queue = new SafeQueue();
    this->create_socket();
    this->bind_socket();
    this->listen_accept();
}

