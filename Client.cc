#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <netinet/in.h>

#include "Client.h"
#include "socket_operations.cc"

void Client::print(const char * message) {
  printf("Client: %s\n", message);
}

Client::Client(char * _server_ip, int _server_port, int _listen_port){
  this->server_ip = new char(strlen(_server_ip) + 1);
  strcpy(this->server_ip, _server_ip);
  this->server_port = _server_port;
  this->listen_port = _listen_port;
}

Message* Client::execute(Message * _message){
  socket_operations::send(*_message, this->server_ip, this->server_port);
  print("Sent message.");
  socket_operations::ReceivedMessage response = socket_operations::receive(this->listen_port);
  print("Received message.");
  print((const char *)response.message.getMessage());
}

Client::~Client(){}

