//
// Created by papraczy on 01/11/2019.
//

#ifndef SERVER_SERVER_SOCKET_H
#define SERVER_SERVER_SOCKET_H

#include "SafeQueue.h"

class Server_socket {

private:
    int server_socket;
    int new_socket;
    SafeQueue *data_queue;

public:
    Server_socket();
    Server_socket(SafeQueue &data_queue);
    ~Server_socket();
    int create_socket();
    int bind_socket();
    int listen_accept();
};


#endif //SERVER_SERVER_SOCKET_H
