//
// Created by papraczy on 01/11/2019.
//

#ifndef SERVER_SERVER_SOCKET_H
#define SERVER_SERVER_SOCKET_H

#include "SafeQueue.h"
#include "DataAnalyser.h"

#define DATA_LEN 16384

class Server_socket {

private:
    int server_socket;
    int new_socket;
    uint16_t data_arr[DATA_LEN];
    SafeQueue *data_queue;
    int create_socket();
    int bind_socket();
    int listen_accept();
    void start_threads(int *new_socket, SafeQueue *data_queue);


public:
    Server_socket();
    ~Server_socket();
};


#endif //SERVER_SERVER_SOCKET_H
