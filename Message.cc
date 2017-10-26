#include "Message.h"

using namespace std;
void* Message::getMessage () const{
  return message;
}

size_t Message::getMessageSize () {
  return message_size;
}

char* Message::marshal (){}

int Message::getOperation (){
  return operation;
}

int Message::getRPCId (){
  return rpc_id;
}

MessageType Message::getMessageType () {
  return message_type;
}

void Message::setOperation (int _operation){
}

void Message::setMessage (void *p_message, size_t p_message_size) {
    this->message_size = p_message_size;
    this->message = (void*) new char(p_message_size + 1);
    strcpy((char*) this->message, (char*) p_message);
}

void Message::setMessageType (MessageType message_type) {
  this->message_type = message_type;
}

Message::Message (int operation, void *p_message, size_t p_message_size, int p_rpc_id) {
  if (p_message_size) {
    rpc_id = p_rpc_id;
    this->operation = operation;
    setMessage(p_message, p_message_size);
  }
}

Message::Message (){}

Message::~Message (){}
