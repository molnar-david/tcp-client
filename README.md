# tcp-client

A very basic TCP client that can connect and send messages to a server, by default to localhost. This can be changed by changing the ipAddress variable. Implemented using [Windows Sockets 2](https://docs.microsoft.com/en-us/windows/win32/winsock/windows-sockets-start-page-2).

Can be used to connect to my [TCP server](https://github.com/molnar-david/tcp-server/) instead of PuTTY.

## How to use:
1. Start the TCP server
2. Start the TCP client
3. Send whatever message you want to the server. If you're connected to my server above, it will echo it back for you
4. Send an empty string to close the session

*Made with the help of the [Networking in C++](https://www.youtube.com/playlist?list=PLZo2FfoMkJeEogzRXEJeTb3xpA2RAzwCZ) YouTube series by [Sloan Kelly](https://www.youtube.com/c/sloankelly)*  
*The tutorial series didn't include a lot of error checking, so most of it I had to look up and write myself*
