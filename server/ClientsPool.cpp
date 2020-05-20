#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <string>
#include <vector>
#include <thread>
#include "ClientsPool.h"
#include "Client.h"
#include <utility> //std::move()
#include <memory>
using namespace std;

//Add a client into ClientsPool
void ClientsPool::add(SOCKET sockClient,int i) {

    //Update socket vector first
    SockClients.push_back(sockClient);

    //Initialize Client class and Update clients' vector int ClientsPool
    //Using Shared_ptr
    auto sp1 = make_shared<Client>(SockClients, i,names);
    names.push_back(sp1->name);

    auto sp2 = sp1;
    clients.push_back(sp1);


    //Create a thread to receive data from a client
    thread trecv(&Client::recvFromClient, sp2.get());

    th.push_back(move(trecv));
    Sleep(500);
    th.back().detach();
};

