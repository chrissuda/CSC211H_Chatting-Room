#include <winsock2.h>
#include <vector>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstring>

#ifndef _Client_H
#define _Client_H
using namespace std;
class ClientParent {
public:
    virtual void initialize() = 0;
    virtual void check() = 0;
    virtual void recvFromClient() = 0;
};

class Client: public ClientParent {
    private:
        const vector<SOCKET>* SockClients; //store a pointer pointing to vector sockClients in class ClientsPool
        SOCKET SockClient;
        char recvBuf[100] = { '0' };
        char sendBuf[100] = { '0' };
        int index; //represent the location where this Client is stored in an array
        const vector<string>* allname;
        
    public:
        string name;

        Client(const vector<SOCKET>& pt, int i,const vector<string> &n) {
            SockClients = &pt;
            SockClient = pt.at(i);
            index = i;
            allname = &n;
            initialize();
        };

    void initialize();
    void check();
    void recvFromClient();
    void sendToClient(SOCKET sockClient);
    void sendToClient(string word,int size); //send to self-client by default
};

#endif
