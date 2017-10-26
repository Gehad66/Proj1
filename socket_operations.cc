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

namespace socket_operations
{
  void print(const char * message){
    printf("Socket Operations: %s\n", message);
  }
  void makeLocalSA (struct sockaddr_in *sa, int port)
  {
    sa->sin_family = AF_INET;
    sa->sin_port = htons (port);
    sa->sin_addr.s_addr = htonl (INADDR_ANY);
  }

  void makeDestSA (struct sockaddr_in *sa, char *hostname, int port)
  {
    struct hostent *host;
    sa->sin_family = AF_INET;
    if ((host = gethostbyname (hostname)) == NULL)
      {
	print("Unknown host name.");
	exit (-1);
      }
    sa->sin_addr = *(struct in_addr *) (host->h_addr);
    sa->sin_port = htons (port);
  }

  void send (const Message & message, char *hostname, int port)
  {
    int s, n;
    struct sockaddr_in mySocketAddress, yourSocketAddress;

    if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
      {
	perror ("socket failed");
	return;
      }
    makeLocalSA (&mySocketAddress, 0);

    if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
      {
	perror ("Bind Failed");
	close (s);
	return;
      }

    makeDestSA (&yourSocketAddress, hostname, port);
    if ((n =
	 sendto (s, message.getMessage (), strlen ((const char *) message.getMessage ()), 0,
		 (const sockaddr*) &yourSocketAddress, sizeof (struct sockaddr_in))) < 0)
      perror ("Send failed\n");
    print("Send successful.");
    close (s);
    print("Socket closing successful.");
  }				//end of sender
  struct ReceivedMessage {
    ReceivedMessage() {}
    ReceivedMessage(const Message & _message, const struct sockaddr_in & _socket) {
      message = _message;
      socket = _socket;
    }
    Message message;
    struct sockaddr_in socket;
  };

  ReceivedMessage receive (int port)
  {
    int SIZE = 1 << 13;
    char message[SIZE];
    struct sockaddr_in mySocketAddress, aSocketAddress;
    int s, aLength, n;

    if ((s = socket (AF_INET, SOCK_DGRAM, 0)) < 0)
      {
	perror ("Socket  failed");
	return ReceivedMessage();
      }

    makeLocalSA (&mySocketAddress, port);

    if (bind (s, (const sockaddr*) &mySocketAddress, sizeof (struct sockaddr_in)) != 0)
      {
	perror ("Bind  failed\n");
	close (s);
	return ReceivedMessage();
      }

    aLength = sizeof (aSocketAddress);
    aSocketAddress.sin_family = AF_INET;	/* note that this is needed */
    if ((n = recvfrom (s, message, SIZE, 0, (sockaddr*) &aSocketAddress, (socklen_t*) &aLength)) < 0)
      {
	perror ("Receive 1");
      }

    print("Receive successful.");
//fork
    print(message);

    close (s);
    return ReceivedMessage(Message(0, (void *)message, strlen(message),0), aSocketAddress);
  }
}
