#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#include<Winsock2.h>
#include<windows.h>
#include<cstdio>


#pragma comment(lib,"ws2_32.lib")

int main()
{
    WORD ver = MAKEWORD(2, 2);
    WSADATA dat;
    WSAStartup(ver,&dat);

    SOCKET sock = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);
    
    sockaddr_in _sin = {};
    _sin.sin_family = AF_INET;
    _sin.sin_port = (htons)4567;
    _sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //INADDR_ANY


    if(SOCKET_ERROR ==bind(_sock, (sockaddr*)&_sin,sizeof(_sin)))
    {
         printf("bind sockaddr_in error!\n");
    }
    else
    {
        printf("bind sockaddr_in ok!\n");
    }

    if(SOCKET_ERROR == listen(_sock, 5))
    {
        printf("listen error!\n");
    }
        else
    {
        printf("listen ok!\n");
    }
    
    sockaddr_in clientAddr = {};
    int nAddrLen = sizeof(sockaddr_in);
    SOCKET _cSock = INVALID_SOCKET;

    _cSock = accept(_sock,(sockaddr*)&clientAddr,&nAddrLen);
    if(INVALID_SOCKET == _cSock)
    {
        printf("accept error!\n");
    }

    printf("New connections join,Ip: %d",inet_ntoa(clientAddr.sin_addr));


    char _recvBuf[128] = {};

    while (true)
    {
      
      int nLen = recv(_cSock,_recvBuf,128,0);
      if(nLen <= 0)
      {
          printf("maybe Clinet exit!\n");
          break;
      }

      if( 0 == strcmp(_recvBuf,"getname"))
      {
          char msgBuf[] = "张三";
           send(_cSock,msgBuf,strlen(msgBuf) + 1,0); 
      }
      else if(0 == strcmp(_recvBuf,"getage"))
      {
          char msgBuf[] = "23";
            send(_cSock,msgBuf,strlen(msgBuf) + 1,0); 
      }
      else{
          char msgBuf[] = "??????";
          send(_cSock,msgBuf,strlen(msgBuf) + 1,0); 
      }

   }
   

  


    closesocket(_sock);


    WSACleanup();
    return 0;
}