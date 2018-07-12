#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#pragma comment(lib, "ws2_32.lib")
#include <Windows.h>

int main()
{

    //創立套接字
    SOCKET s;

    //wsa版本
    WSADATA wsaData;

    char szBuf[1024];
    char szServer[1024];

    unsigned int addr;
    int nRcv;

    //winsock初始化,回傳0才代表成功
    if (WSAStartup(MAKEWORD(2, 2), &wsaData))
    {
        printf("WSAStartup fail ! \n");
        WSACleanup();
        _getch();
        return -1;
    }
    else{
        printf("Initialised.\n");
    }


    //建立socket
    s = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (s < 0)
    {
        printf("Socket open error !\n");
        WSACleanup();
        _getch();
        return -2;
    }
    else{
        printf("Socket created.\n");
        printf("Start connect ...\n\n");

    }

    // 設置要連線到的servr結構,內容初始化
    // struct sockaddr_in sa;
    SOCKADDR_IN saddr;
    memset(&saddr, 0, sizeof(SOCKADDR_IN));
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(8080);
    saddr.sin_addr.s_addr = inet_addr("127.0.0.1");


    // 連線到server
    if (connect(s, (SOCKADDR *)&saddr, sizeof(saddr)) == SOCKET_ERROR)
    {
        printf("Connected error !\n");
        closesocket(s);
        WSACleanup();
        return -4;
    }
    else
    {
        printf("Connected success ! \n");
    }
    printf("---------------------------------------\n");
    // szBuf[nRcv] = '\0';

    //是否要傳送訊息
    while (1)
    {
        printf("Send msg or Exit?(ok/exit)\n>>");
        gets(szBuf);
        if (strcmp(szBuf, "exit") == 0)
        {
            printf("buf = %s\n", szBuf);
            send(s, szBuf, (int)strlen(szBuf), 0);
            break;
        }
        else if(strcmp(szBuf, "ok") == 0){
            printf("buf = %s\n", szBuf);
            printf("\nEnter msg\n>>");

            memset(szBuf, '\0', sizeof(szBuf));
            gets(szBuf);
            printf("buf = %s\n", szBuf);
            send(s, szBuf, (int)strlen(szBuf), 0);
            system("pause");

        }
        else{
            printf("Wrong selection !\n");
            break;
        }



        printf("\nWait server msg...\n");
        printf("---------------------------------------\n");


        // 開始讀取
        nRcv = recv(s, szBuf, sizeof(szBuf) - 1, 0);
        printf("STOP\n");
        if (nRcv == SOCKET_ERROR)
        {
            printf("recv error ! \n");
            break;
        }
        // szBuf[nRcv] = '\0';

        // 如果收到exit就不再繼續傳輸
        if (strcmp(szBuf, "exit") == 0)
        {
            printf("disconnect\n");
            break;
        }

        printf("recieve : %s\n", szBuf);
        printf("-------------------------------\n");

    }

    closesocket(s);
    WSACleanup();
    printf("Client exit");
    getch();
    return 0;
}
