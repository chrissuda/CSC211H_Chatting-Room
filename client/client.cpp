#include<winsock2.h>
#include <stdio.h>
#include <string>
#include <iostream>
#include <Windows.h>
#include <exception>
#include <cstring>
#include <thread>
#pragma comment(lib,"ws2_32.lib")
#pragma warning(disable:4996) 
using namespace std;
//function prototype
void initialize(SOCKET sockClient);
void sendToServer(SOCKET sockClient);
void recvFromServer(SOCKET sockClient);

int main() {
    int err;

    SOCKET sockClient; //Client's socket;
    //SOCKADDR_IN addrClient;// client's address
    SOCKADDR_IN addrServer; // server's address
    WSADATA wsaData;
    WORD wVersionRequested;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);

    if (err != 0) { return -1; } //Terminate the porgram if it has error;

    //Create a socket for client;
    sockClient = socket(AF_INET, SOCK_STREAM, 0);

    //Define the address that wants to connect to (Server's)
    //To Do: Add IP here
    addrServer.sin_addr.S_un.S_addr = inet_addr(""); //Target's IP
    addrServer.sin_family = AF_INET;                          //IPV4
    addrServer.sin_port = htons(); //Target's port

    while (true) {
        try
        {
            std::cout << "Connecting...."
                << "IP:"
                << inet_ntoa(addrServer.sin_addr)
                << ":" << ntohs(addrServer.sin_port) << endl;

            //Waiting to connect to Server
            do {

                err = WSAConnect(sockClient, (SOCKADDR*)&addrServer, sizeof(addrServer),NULL,NULL,NULL,NULL);
                Sleep(1000);
            } while (err < 0);

            initialize(sockClient);

            thread tsend(sendToServer, sockClient);
            thread trecv(recvFromServer, sockClient);
            tsend.join();
            trecv.join();

        }
        catch (const exception& e)
        {
            std::cout << "connection fail:" << e.what() << endl;
            std::cout << "Programming is terminating....!\n";
        }
        Sleep(1000);
        //Shut down socket
        std::cout << "Session is shutdown by YOU\n";
        closesocket(sockClient);
        WSACleanup();
        continue;
    }
    

    Sleep(1000);
    //Shut down socket
    std::cout << "Session is shutdown by client\n";
    closesocket(sockClient);
    WSACleanup();

    return 0;
};

void initialize(SOCKET sockClient) {
    string name;
    string roomNumber;
    char recvBuf[50];

    //Asking for room number
    cout << "Type the room Number:";
    getline(cin, roomNumber);
    send(sockClient, roomNumber.c_str(), roomNumber.length() + 1, 0);

    //Receive bytes from server
    recv(sockClient, recvBuf, 50, 0);
    //Welcome:!This is Chris's server\n
    printf("%s\n", recvBuf);

    //Asking for user's name
    cout << "Type your name:";
    getline(cin, name);
    send(sockClient, name.c_str(), name.length() + 1, 0);
    
    //Receive message
    recv(sockClient, recvBuf, 50, 0);
    

};

void sendToServer(SOCKET sockClient) {

    while (true) {
        //Send data to server
        string sendBuf;
        getline(cin, sendBuf);
        //Convert string to const char*
        int bytes = send(sockClient, sendBuf.c_str(), sendBuf.length()+1, 0);

        //Exception handling: Program will terminate if it can't send to server
        if (bytes <= 0) { return; }
    }
};

void recvFromServer(SOCKET sockClient)
{
    char recvBuf[100];
    while (true) {
        int bytes = recv(sockClient, recvBuf, 100, 0);
        if (bytes > 1) {
            printf("%s\n", recvBuf);
        }
    }
};

