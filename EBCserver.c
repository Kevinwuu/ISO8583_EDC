#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "trans_input.h"
#pragma comment(lib, "ws2_32.lib")
// #pragma comment(lib, "libws2_32.a")
// #pragma comment(lib, "libwsock32.a")


int main()
{
    //創立套接字，listen_s監聽client訊息，s負責回傳訊息
    SOCKET listen_s,s;

    //wsa版本
    WSADATA wsaData;


    char szBuf[1024];
    int fromlen, nRcv;

    // winsock初始化
    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        printf("WSAStartup fail!\n");
        WSACleanup();
        system("PAUSE");
        return -1;
    }
    else{
        printf("Initialised.\n");

    }

    // 建立socket
    listen_s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listen_s == INVALID_SOCKET)
    {
        printf("socket open error!\n");
        WSACleanup();
        return -2;
    }
    else
    {
        printf("Socket created.\n");
    }

    // 設置saddr結構,結構內容初始化為0
    SOCKADDR_IN saddr;
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    // saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    saddr.sin_addr.s_addr - INADDR_ANY;

    char hostname[20]={'\0'};
    struct hostent *hp;
    gethostname(hostname, 1023);
    printf("Hostname: %s\n", hostname);
    hp = gethostbyname(hostname);
    // int len;
    // len = hp->h_length;
    // printf("%d\n", len);
    char ip_addr[15];
    int i = 0;
    strcpy(ip_addr,inet_ntoa(*(struct in_addr*)hp->h_addr_list[i]));
    // printf("Hostname: %s\n",hp->h_name);

    printf("IP = %s\n",ip_addr );

    printf("IP_len = %d\n",strlen(ip_addr) );

    //綁定server的local位置,用來給client連線
    if (bind(listen_s, (struct sockaddr *)&saddr, sizeof(saddr)) != -1)
    {
        printf("Bind Success.\n");
    }
    else{
        printf("Bind Fail !\n");
    }


    // 開始監聽port,設定監聽駐列
    if (listen(listen_s, 0) == SOCKET_ERROR) //等待Socket端連線
    {
        printf("Listen fail! \n");
        closesocket(listen_s);

        WSACleanup();
        system("PAUSE");
        return -4;
    }
    else
    {
        printf("Listen Sucess! \n\nWait for client ...\n\n");
    }


    // 接受到client連線後,建新的socket,原先socket再度回去listen
    s = accept(listen_s, NULL, NULL);
    if (s == INVALID_SOCKET)
    {
        printf("accept fail! \n");
        closesocket(listen_s);
        WSACleanup();
        return -5;
    }
    else
    {
        printf("Connected !\n");

        printf("---------------------------------------\n");
        printf("Wait...\n\n");



    }
    //已經連上client就不用再監聽
    closesocket(listen_s);


    while (1)
    {

        //讀出資料
        memset(szBuf,'\0',sizeof(szBuf));
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
        Sleep(1000);

        if (nRcv == SOCKET_ERROR)
        {
            printf("Recv error!\n");
            break;
        }
        if (strcmp(szBuf, "exit") == 0)
        {
            printf("Disconnect !\n");
            break;
        }
        printf("\n---------------------------------------\n");
        printf("Recieve : %s", szBuf);
        parseOutput(szBuf);
        printf("\n---------------------------------------\n");
        // szBuf[nRcv] = '\0';


        Sleep(1000);
        memset(szBuf, '\0', sizeof(szBuf));

         // 回復給client或直接結束
        printf("Send msg or Exit?(ok/exit):\n>>");
        gets(szBuf);

        if (strcmp(szBuf, "exit") == 0)
        {
            send(s, szBuf, (int)strlen(szBuf), 0);
            break;
        }else if(strcmp(szBuf,"ok") == 0)
        {
            printf("\nEnter msg:\n>>");
            gets(szBuf);
            send(s, szBuf, (int)strlen(szBuf), 0);

            printf("\nWait ...\n\n");
            system("pause");
        }else
        {
            printf("Wrong selection !\n");
            send(s, "exit", (int)strlen(szBuf), 0);
            break;
        }


    }

    closesocket(s);
    WSACleanup();

    printf("Server exit\n");
    _getch();

    return 0;
}
