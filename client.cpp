#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <errno.h>
#include <string.h>

int main(int argc,char* argv[])
{
    struct sockaddr_in serverAddr;
    int nFd = 0;
    int nRet = 0;
    int nReadLen = 0;
    char szBuff[BUFSIZ] = {0};

    /* 判断有没有输入要连接的ip地址 */
    if (argc == 1)
    {
        perror("please input the ip address that you want to connect\n");
        return -1;
    }

    /* 创建套接字描述符 */
    nFd = socket(AF_INET,SOCK_STREAM,0);
    if (-1 == nFd)
    {
        perror("socket:");
        return -1;
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(argv[1]);
    serverAddr.sin_port = htons(8080);//默认以8080端口连接

    /* 和服务器端建立连接 */
    nRet = connect(nFd,(struct sockaddr*)&serverAddr,sizeof(serverAddr));
    if (nRet == -1)
    {
        printf("connect:");
        return -1;
    }

    while(1)
    {
        /* 从终端读取数据 */
        memset(szBuff,0,BUFSIZ);
        nReadLen = read(STDIN_FILENO,szBuff,BUFSIZ);
        if (nReadLen > 0)
        {
            write(nFd,szBuff,strlen(szBuff));
        }
    }

} 