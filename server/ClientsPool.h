#include <winsock2.h>
#include <Windows.h>
#include <iostream>
#include <stdio.h>
#include <cstring>
#include <vector>
#include <thread>
#include "Client.h"
#ifndef _ClientsPool_H
#define _ClientsPool_H
using namespace std;


class ClientsPool {
public:
	char *roomNumber;

	//Allocate vector on the stack enable faster access , and automatic garbage collection;
	vector<shared_ptr<Client>> clients;
	vector<string> names;
	vector<SOCKET> SockClients;
	vector<thread> th;

	ClientsPool(char *num) {

		roomNumber = num;
		clients.reserve(20);
		names.reserve(20);
		th.reserve(20);
	}
	~ClientsPool() {
		cout << "Server Calling destructor!\n";
	}
	/* Allocate vector pointer on the stack while itself is on the heap
	vector<shared_ptr<Client>>* clients = new vector<shared_ptr<Client>>;
	vector<SOCKET>* SockClients = new vector<SOCKET>;
	vector<thread> *th=new vector<thread>; //create a pointer to thread
	*/

	void add(SOCKET sockClient,int i);
};


#endif

