/* Args:
 *   argv[1]: Listen port.
 *   argv[2]: Client port.
 *
 * Example:
 * ./server_main 8080 8081
 */

#include <string.h>
#include <stdio.h>

#include "Message.h"
#include "Server.h"

using namespace std; 

int main(int argc, char *argv[])
{
  Server server(atoi(argv[1]), atoi(argv[2]));
  server.serveRequest();
  return 0;
}
