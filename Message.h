#ifndef MESSAGE_H
#define MESSAGE_H
#include <string.h>

enum MessageType { Request, Reply };

class Message
{
private:
  MessageType message_type;
  int operation;
  void *message;
  size_t message_size;
  int rpc_id;
public:
    Message();
    Message (int operation, void *p_message, size_t p_message_size,
	     int p_rpc_id);
    Message (char *marshalled_base64);
  char *marshal ();
  int getOperation ();
  int getRPCId ();
  void *getMessage () const;
  size_t getMessageSize ();
  MessageType getMessageType ();
  void setOperation (int _operation);
  void setMessage (void *message, size_t message_size);
  void setMessageType (MessageType message_type);
   ~Message ();
};
#endif // MESSAGE_H
