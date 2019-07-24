#include <sys/types.h>
#include <sys/socket.h>
#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>

using namespace std;

int main()
{
    int sockfd;
    struct sockaddr_in addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    addr.sin_family = AF_INET;
    addr.sin_port = 9981;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    int result = connect(sockfd, (struct sockaddr*)&addr, sizeof(addr));
    if(result == -1)
    {
        cout << "error" << endl;
    }
    else
    {
        char ch[10] = "1111";
        write(sockfd, ch, strlen(ch));
    }
    
}