#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include "Client.h"
#include<stdlib.h>
#include <string>
using namespace std;


void Client::recvFromClient() {
    
    check();
    sendToClient("###Start Chatting###\n", 25);


    while (true) {
     
        //Receive data from client
        //recv():blocking mode
        int bytes = recv(SockClient, recvBuf, 100, 0);
        if (bytes > 1) {
            //Print out message from client
            cout <<name << ":" << recvBuf<<"\n";

            //send to client
            strcpy(sendBuf, recvBuf);

            //Loop over a *SockClients vector to send back information to different clients
            for (int i = 0;i<(SockClients->size());i++) {
                if (i !=index) {
                    sendToClient(SockClients->at(i));
                }
            }
        }
        else if (bytes == 1) {
            ;//Step Over if server only receive "\n" by Enter, which is only 1 byte.
        }

        else {//Shut down Socket
            cout <<name<<" has lost connections\n";
            
            sendToClient("Session is closed by server\n", 50);

            closesocket(SockClient);
            return;
        }
    }
    
};

void Client::initialize() {
    char n[20];
    string word;
    //Send out message
    send(SockClient,"Welcome! This is Chris's server\n",50, 0);

    //Get name from client
    recv(SockClient, n, 50, 0);
    name = n;

    //Send back greeting with name to client;
    word = "Server: Welcome home "+name+" !\n";
    send(SockClient,word.c_str(), word.length() + 1, 0);

    cout << "Client:" << index + 1 << endl;

};

void Client::check() {
    string word="";

    //check if other are in your room
    if (allname->size() <= 1) {
        sendToClient("Oops,Nobody is in this room besides you\nWait!...\n", 50);
        cout << "Wait...";
        while (allname->size() <= 1) {
            Sleep(1000);
        }
    }
   
    //Loop over all the name;
    for (int i = 0;i<allname->size();i++){
        if (i != index) {
            word += allname->at(i) + ",";
        }
    }
    word += "are in this room\n";
    sendToClient(word.c_str(), word.length()+1);
   
};

void Client::sendToClient(SOCKET sockClient) {
    string ch = allname->at(index) + ":";
    ch += sendBuf;
    send(sockClient,ch.c_str(), 100, 0);
};
void Client::sendToClient(string word, int size) {
    string ch = "Server:" + word;
    send(SockClient, ch.c_str(), 100, 0);
};
