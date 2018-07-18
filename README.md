# ISO8583_EDC

Use web socket to emulate EBC, try to send/recieve messaage according to [ISO8583](https://en.wikipedia.org/wiki/ISO_8583).

## Goal
1. Read msg from EBC
2. Unpack & pack.
3. Conmmunicate between cash register & EBC

## Note
to fix ```undefined reference to `WSACleanup@0' ```  compiling error, according to your enviroment.

- **use IDE**
[codeblock](https://hackerandgeek.blogspot.com/2010/01/codeblockswinsock-library.html)

- **use Editer**
    install MINGW gcc/g++
    
        gcc server.c -o client -lws2_32
        gcc client.c -o client -lws2_32

## Usage
    start server
    start client
    


## Result



- **client**
![](https://i.imgur.com/aCL2qwe.png)

- **server**
![](https://i.imgur.com/H2c8VQb.png)


- **EBC unpack**
![](https://i.imgur.com/LkVJvPB.png)
