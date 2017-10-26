/* Args:
 *   argv[1]: Server IP address.
 *   argv[2]: Server port number.
 *   argv[3]: Listen port number.
 *   argv[4]: Message string to be sent to the server.
 *
 * Example:
 * ./client_main 127.0.0.1 8080 8081 hello
 */
#include <string.h>
#include <stdio.h>

#include "Message.h"
#include "Client.h"
#include "Server.h"

int main(int argc, char *argv[])
{
  Client client(argv[1], atoi(argv[2]), atoi(argv[3]));
  Message m(0, argv[4], strlen(argv[4]), 0);
  client.execute(&m);
  return 0;
}

