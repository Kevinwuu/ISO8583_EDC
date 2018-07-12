#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
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

    printf("buffer : %s\n",szBuf);
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
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    // printf(AL)
    // saddr.sin_addr.s_addr - INADDR_ANY;


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
        printf("Read message...\n\n");
        closesocket(listen_s);


    }
    //已經連上client就不用再監聽


    while (1)
    {

        //讀出資料
        memset(szBuf,'\0',sizeof(szBuf));
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
        printf("1\n");
        printf("%s\n", szBuf);
        printf("2\n");
        if (nRcv == SOCKET_ERROR)
        {
            printf("Recv error!\n");
            break;
        }
        printf("3\n");
        if (strcmp(szBuf, "exit") == 0)
        {
            printf("Disconnect !\n");
            break;
        }
        printf("4\n");

        printf("Recieve : %s", szBuf);
        printf("\n---------------------------------------\n");
        // szBuf[nRcv] = '\0';

         // 回復給client或直接結束
        printf("Send msg or Exit?(ok/exit):\n>>");
        gets(szBuf);

        if (strcmp(szBuf, "exit") == 0)
        {
            send(s, szBuf, (int)strlen(szBuf), 0);
            break;
        }
        printf("\nEnter msg:\n>>");
        gets(szBuf);
        send(s, szBuf, (int)strlen(szBuf), 0);

        printf("Wait client msg...\n\n");

    }


    closesocket(s);
    WSACleanup();

    printf("Server exit\n");
    _getch();

    return 0;
}
