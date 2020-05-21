#include <winsock2.h>
#include <stdio.h>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>
#include <Windows.h>
#include <cstring>
#include "Client.h"
#include "ClientsPool.h"
#pragma comment(lib,"ws2_32.lib")
using namespace std;


int  main()
{
    int err, len;

    /*To Do!!!!!
    create a vector to store various ClientsPool;
    vector<ClientsPool> room;
    */
    vector<unique_ptr<ClientsPool>> ClientsPools;


    SOCKET sockServer; //Server's socket
    SOCKADDR_IN addrServer; //structure to store Server's address
    SOCKET sockClient; //Client's socket
    SOCKADDR_IN addrClient; //Structure to store Client's address

    WSADATA wsaData; //winsock's structure
    WORD wVersionRequested; //winsocket's version

    //Configure windows socket
    wVersionRequested = MAKEWORD(2, 2);
    //Initialize windows socket
    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0) { return -1; } // Terminate the program if it fails


    // Define server's socket
    sockServer = socket(AF_INET, SOCK_STREAM, 0);

    //Configure server's socket
    addrServer.sin_addr.S_un.S_addr = htonl(INADDR_ANY); //server's IP:192.168.0.*
    addrServer.sin_family = AF_INET;                     //INET protocol
    addrServer.sin_port = htons(6000);                    //port:6000

    //Bind server's socket with local port
    bind(sockServer, (SOCKADDR*)&addrServer, sizeof(sockaddr));

    //Listen local port
    listen(sockServer, 20);   //20 is the number of connections
    printf("Server is running:\nListening....\n");

    len = sizeof(addrClient);
    int i = 0; //count the connections that server gets;
    //ClientsPool clientspool;
    while (true) {
        //accept will block threads,until someone connects it.
        sockClient = accept(sockServer, (SOCKADDR*)&addrClient, &len);

        //Print out message if someone connects it
        cout << "Connection "
            << i + 1
            << " from:"
            << inet_ntoa(addrClient.sin_addr)
            << ":" << ntohs(addrClient.sin_port) << endl;


        //clientspool.add(sockClient,i);
        //Put the new client into an appropriate room
        char roomNumber[20]={"\0"};
        boolean existRoom=false;
        recv(sockClient, roomNumber, 20, 0);
        
        for (auto& clientspool : ClientsPools) {
            if (strcmp(roomNumber, clientspool->roomNumber) == 0) {
                clientspool->add(sockClient, i);
                existRoom = true;
                break;
            }
        }
       
        //Create a new room if the roomNumber doesn't match
        if (!existRoom) {
            auto ptr=make_unique<ClientsPool>(roomNumber);
            ptr->add(sockClient, i);
            ClientsPools.push_back(move(ptr));
        }
        
        //Increment i if client connects server successfully
        i += 1;

        
    }
    
    cout << "The server is shutting down\n";
    return 0;
}





