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
#include <sstream>
#include <thread>

using namespace std;

#include "server_socket.h"
#include "DataAnalyser.h"
#include "SafeQueue.h"
#include "Calculator.h"

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

/*
 * Bind an IP address and port to the socket
 * */
int Server_socket::bind_socket() {
    struct sockaddr_in address;
    //indicate socket address family- IPv4
    address.sin_family = AF_INET;
    //convert IP address to a binary format
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

/*
 * Puts the server socket into the listening state,
 * accepts the incoming connections and
 * starts a thread for data analysis
 * */
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
                             &client_addr_len)) > 0)
    {
        //client connection established
        this->start_threads(&this->new_socket, this->data_queue);
    }

    return 0;
}

Server_socket::Server_socket() {
    this->data_queue = new SafeQueue();
    this->create_socket();
    this->bind_socket();
    this->listen_accept();
}

void Server_socket::start_threads(int *new_socket, SafeQueue *data_queue) {
    //read data incoming to a client socket
    auto data_reader = [](int *new_socket, SafeQueue *data_queue) {
        cout << "Receieved this: ";

        while (true) {
            try
            {
                // do stuff
                char buffer[1024] = {0};
                int valread = read(*new_socket, buffer, 512);

                //prepare data packet
                string data_read = "";

                //convert a data packet into a string of hex for the analysis purposes
                for (int i = 0; i < valread; i++) {
                    data_read += Calculator::getHex(int(buffer[i]) & 0xFF);
                }
                data_queue->push(data_read);
            }
            catch (std::exception const &exc) {
                std::cerr << "Exception caught " << exc.what() << "\n";
            }
        }
    };
    //start a thead for analysing data
    DataAnalyser *data_analyser = new DataAnalyser(data_queue);
    thread analyse_data_handler(*data_analyser);
    //start a thread for reading data from the client socket
    thread read_data_handler(data_reader, &this->new_socket, this->data_queue);
    read_data_handler.join();
}




