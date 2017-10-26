#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <algorithm>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "Message.h"
#include "Server.h"
#include "socket_operations.cc"

void Server::print(const char * message) {
  printf("Server: %s\n", message);
}

Server::Server(int _listen_port, int _client_port) {
  this->listen_port = _listen_port;
  this->client_port = _client_port;
}

void Server::serveRequest(){ 
  while(true){
    socket_operations::ReceivedMessage received = socket_operations::receive(this->listen_port);
    pid_t pid = fork();
    if (pid) {
      // parent process - do nothing
    }
    else {
      Message reply = doOperation(&received.message);
      char s[32];
      sprintf(s, "Received from %s: %d.", inet_ntoa(received.socket.sin_addr), (int) received.socket.sin_port);
      print(s);
      print((const char *) received.message.getMessage());
      socket_operations::send(reply, inet_ntoa(received.socket.sin_addr), this->client_port);
      break;
    }
  }


}

Server::~Server() {}

Message * Server::getRequest() {}

Message Server::doOperation(Message * _message) {
  char vowels[6] = "aeioy";
  char * s = new char[strlen((char*)_message->getMessage()) + 1];
  int counter = 0;
  for (char * c = (char*) _message->getMessage(); *c; ++c) {
    if (!std::binary_search(vowels, vowels + 5, *c)) {
      s[counter++] = *c;
    }
  }
  s[counter] = 0;
  return Message(0, (void *) s, counter, 0);
}


void Server::sendReply (Message * _message) {}

