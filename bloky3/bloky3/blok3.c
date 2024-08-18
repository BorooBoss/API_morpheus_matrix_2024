#include <stdlib.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <windows.h>
#include <ctype.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>


#pragma warning(disable:4996)
#pragma comment(lib, "Ws2_32.lib")
#define IPSERVER "147.175.115.34"
#define PORTSERVER "777"
#define AIS_LEN 6
#define DEFAULT_BUFLEN 4096

/*
const char HorizontalLine = '-';
const char LeftUpper = '┌';
const char LeftLower = '└';
const char RightUpper = '┐';
const char RightLower = '┘';


const char HorizontalLine = '-';
const char updOWN = '|';
*/


int remainderp(char* id) {
    int sum = 0;
    int resultp;
    for (int i = 0; i < (AIS_LEN - 2); i++) {
        sum += (id[i] - '0');
    }
    //printf("%d\n", sum);
    if ((id[AIS_LEN - 2] - '0') == 0) {
        resultp = (sum % (9));
    }
    else {
        resultp = (sum % (id[AIS_LEN - 2] - '0'));
    }
    //printf("%d\n",result);
    return resultp;

}
void replacer(char* string) {
    for (int i = 0; i < strlen(string); i++) {
        if (string[i] == '\n') {
            string[i + 1] = '\0';
            break;
        }
    }
}
void decipher(char* str, HANDLE  hConsole, int start_x, int start_y) {
    int counter = 0;
    COORD point_receive = { start_x, start_y };
    SetConsoleCursorPosition(hConsole, point_receive);
    for (int i = 0; i < 148; i++) {
        if (i == 76) { 
            start_x = 79;
            start_y = start_y + 1;
            COORD point_receive = { start_x, start_y };
            SetConsoleCursorPosition(hConsole, point_receive);
            counter = 0;
        }
        if (str[i] == '\n') {
            str[i] = '\0';
        }

        printf("%c", str[i] ^ 55);
      
    }
    memset(str + 13, '\0', 8 * sizeof(char));

}
int isPrime(int number) {
    for (int i = 2; i <= number / 2; i++) {
        if (number % i == 0) {
            return 0;
        }
    }
    return 1;
}
void stringPrimes(char* str, HANDLE hConsole, int start_x, int start_y) {
    int prime_numbers[16]; //zatial 16
    int counter = 0;
    for (int i = 2; i < strlen(str); i++) {
        if (isPrime(i) == 1) {
            prime_numbers[counter] = i - 1; 
            counter += 1;
        }
        if (counter > 16) {
            printf("small array\n");
            break;
        }
    }
    for (int j = 0; j < counter; j++) {
        if (prime_numbers[j] < strlen(str)) {
            printf("%c", str[prime_numbers[j]]);
            }
        }
    }


int send_data(SOCKET ConnectSocket, const char* sendbuf, HANDLE hConsole, int start_x, int start_y, FILE* file) {
    int iResult = send(ConnectSocket, sendbuf, (int)strlen(sendbuf), 0);
    if (iResult == SOCKET_ERROR)
    {
        printf("send failed : % d\n", WSAGetLastError());
        closesocket(ConnectSocket);
        WSACleanup();
        return 1;
    }
    //printf("Bytes Sent : % ld\n", iResult);     //vypisanie poctu odoslanych dat
    fprintf(file, "Boris :");//subor
    fprintf(file, "%s\n", sendbuf);
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    printf("%s\n", sendbuf);
    SetConsoleTextAttribute(hConsole, 15);
    Sleep(100);
   

}
int recieve_data(SOCKET ConnectSocket, char* recvbuf, int recvbuflen, HANDLE  hConsole, int start_x, int start_y, int* lines, char* id, FILE* file, int *end) {
    int iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);     //funkcia na príjimanie
    *lines = (iResult / 76) + 1; //pocet riadkov
    int result_remp;
    if (iResult > 0) {
        //printf("Bytes Received : % d\n", iResult); //prisli validne data, vypis poctu
        replacer(recvbuf);
        fprintf(file, "Morpheus:");//subor
        fprintf(file, "%s\n", recvbuf);
        int counter = 0;
        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
        start_x = 79;
        start_y = 1 + start_y; //posuniem sa z riadku kde bol input na riadku kde je vypis
        //if (iResult == 405) {
           // result_remp = remainderp(id);
           // return result_remp;

        //}
        if (iResult == 148) {
            //start_y++;
            decipher(recvbuf, hConsole, start_x, start_y);
            lines = 2;
            start_y--;
            return lines;
        }

        COORD point_receive = { start_x, start_y };
        SetConsoleCursorPosition(hConsole, point_receive);
        for (int i = 0; i < iResult; i++)
        {
            if (recvbuf[i] == '\n')
            {
                recvbuf[i] = '\0';
            }
            if (counter == 76) {
                start_x = 79;
                start_y = start_y+1;
                COORD point_receive = { start_x, start_y };
                SetConsoleCursorPosition(hConsole, point_receive);
                counter = 0;
            }
            printf("%c", recvbuf[i]);
            Sleep(25);
            counter++;
        }
        printf("\n");
        SetConsoleTextAttribute(hConsole, 15);
        if (iResult == 23) {
            
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            start_x = 70 + 41 - 12;
            COORD point_primes = { start_x, start_y };
            SetConsoleCursorPosition(hConsole, point_primes);
            printf(" --> ");
             stringPrimes(recvbuf, hConsole, start_x, start_y);
            //snprintf(test, 4096, "%d", recvbuf); // Convert int to char
            *lines = 1;
            start_y++; //pridam riadok medzi vypismi
            start_x = 0;
            COORD point_receive = { start_x, start_y };
            SetConsoleCursorPosition(hConsole, point_receive);
            return 0;
        }

        if (iResult == 405) {
            char test[DEFAULT_BUFLEN];
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            int result_remp = remainderp(id);
            snprintf(test, 4096, "%d", result_remp); // Convert int to char
            send_data(ConnectSocket, test, hConsole, start_x, start_y, file);
            *lines = 13;
            start_y++; //pridam riadok medzi vypismi
            recieve_data(ConnectSocket, recvbuf, DEFAULT_BUFLEN, hConsole, start_x, start_y, &lines, id, file, &end);
            memset(test + 13, '\0', 8 * sizeof(char));
            
            lines = 4;
            COORD point_receive = { start_x, start_y };
            SetConsoleCursorPosition(hConsole, point_receive);
            return 0;
        }
        if (iResult == 329) {
            *end = 1;
            return end;
        }
        return &lines;
    }
    else if (iResult == 0) {
        printf("Connection closed\n");     //v tomto pripade server ukoncil komunikaciu
        return 0;
    }
    else {
        printf("recv failed with error : % d\n", WSAGetLastError());     //ina chyba
        return 0;
    }
}
int main() {
    //uvodne nastavovacky
    HANDLE  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    //ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);
    CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
    GetConsoleScreenBufferInfo(hConsole, &consoleInfo);
    int maxSizeC_X = consoleInfo.dwSize.X;
    SetConsoleOutputCP(CP_UTF8);
    int start_x = 0;
    int  start_y = 0;
    COORD point = { start_x, start_y };
    SetConsoleCursorPosition(hConsole, point);

    //SetConsoleTextAttribute(hConsole, 10);
    WSADATA wsaData;    //struktura WSADATA pre pracu s Winsock
    int iResult;
    int resultp;
    int resultc;

    // Initialize Winsock
    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);     //zakladna inicializacia
    if (iResult != 0)     //kontrola, ci nestala chyba
    {
        printf("WSAStartup failed : % d\n", iResult);
        return 1;
    }

    struct addrinfo* result = NULL, * ptr = NULL;     //struktura pre pracu s adresami
    struct addrinfo hints;

    ZeroMemory(&hints, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;     //pracujeme s protokolom TCP/IP

    // Resolve the server address and port
    iResult = getaddrinfo(IPSERVER, PORTSERVER, &hints, &result);
    if (iResult != 0)     //kontrola, ci nenastala chyba
    {
        printf("getaddrinfo failed : % d\n", iResult);
        WSACleanup();
        return 1;
    }
    else
        printf("getaddrinfo didn't fail...\n");

    //vytvorenie socketu a pripojenie sa

    SOCKET ConnectSocket = INVALID_SOCKET;

    // Attempt to connect to the first address returned by
    // the call to getaddrinfo
    ptr = result;

    // Create a SOCKET for connecting to server => pokus o vytvorenie socketu
    ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);

    if (ConnectSocket == INVALID_SOCKET)     //kontrola, ci nenastala chyba 
    {
        printf("Error at socket() : % ld\n", WSAGetLastError());
        freeaddrinfo(result);
        WSACleanup();
        return 1;
    }
    else {
       printf("Error at socket DIDN'T occur...\n");

    }

    // Connect to server. => pokus o pripojenie sa na server

    iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
    if (iResult == SOCKET_ERROR)     //kontrola, ci nenastala chyba
        printf("Not connected to server...\n");
    else
        printf("Connected to server!\n");

    if (iResult == SOCKET_ERROR)    //osetrenie chyboveho stavu
    {
        closesocket(ConnectSocket);
        ConnectSocket = INVALID_SOCKET;
        WSACleanup();
        return 1;
    }

    Sleep(250);

    //posielanie

    char sendbuf[4096];
    //strcpy(sendbuf, "\0");
    //sendbuf[0] = '\0';


    //prijimanie

    int recvbuflen = DEFAULT_BUFLEN;
    char recvbuf[4096];
    /*
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    printf("╔");
    
    int zaky_x = 0;
    int zaky_y = 40;
    COORD point_zaky = { zaky_x, zaky_y };
    
    SetConsoleCursorPosition(hConsole, point_zaky);
    printf("╚");
    SetConsoleCursorPosition(hConsole, point_zaky);
    zaky_x = 154;
    zaky_y = 40;
    SetConsoleCursorPosition(hConsole, point_zaky);
    printf("╝");
    
    zaky_x = 1;
    zaky_y = 40;
    SetConsoleCursorPosition(hConsole, point_zaky);
    for (int j = 0; j < 154; j++) {
        COORD point_zaky = { zaky_x, zaky_y };
        SetConsoleCursorPosition(hConsole, point_zaky);
        printf("%c", HorizontalLine);
        zaky_x++;
    }
    zaky_x = 154;
    zaky_y = 3;
    SetConsoleCursorPosition(hConsole, point_zaky);
    printf("%c", LeftLower);
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE);
    */

    //char test[] = "126799";
    char id[4096];
    int lines = 0;
    int rem = 3; //posun o 4 policka na zaciatku, potom sa tam uklada pocet riadkov z minuleho kola
    FILE* file;
    int end = 0;
    file = fopen("file.txt", "w");
    fprintf(file, "Boris Pekarčík \n");//printovanie do suboru
    int i = 0;
    //329 ta konec
    while (end != 1) {
        int start_x = 0;
        int  start_y = (lines + rem);
        rem = start_y; //dlzka predchadzajuceho
        COORD point_send = { start_x, start_y };
        SetConsoleCursorPosition(hConsole, point_send);
        HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);
        DWORD mode = 0;
        GetConsoleMode(hStdin, &mode);
        SetConsoleMode(hStdin, mode & (~ENABLE_ECHO_INPUT)); // Disable echoing
        fgets(sendbuf, 4096, stdin); // Get input
        if (i == 1) { //uloz ais id
            strcpy_s(id, 4096, sendbuf);
        }
        //if (i == 5) {
            //snprintf(sendbuf, 4096, "%d", result_remp); //int to char
        //}
        if (start_y > 36 || (lines + start_y) > 39) { //ak sme na konci
            system("cls");
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_RED |FOREGROUND_BLUE);
            printf("getaddrinfo didn't fail...\n");
            printf("Error at socket DIDN'T occur...\n");
            printf("Connected to server!\n");
            SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
            lines = 1;
            rem = 3;
            start_x = 0;
            start_y = (lines + rem);
            rem = start_y;
            COORD point_send = { start_x, start_y };
            SetConsoleCursorPosition(hConsole, point_send);
            SetConsoleMode(hStdin, mode); // Restore original console mode
            send_data(ConnectSocket, sendbuf, hConsole, start_x, start_y, file);
            lines = 0;
            start_y = start_y - 1;
            recieve_data(ConnectSocket, recvbuf, DEFAULT_BUFLEN, hConsole, start_x, start_y, &lines, id, file, &end);
            memset(sendbuf + 13, '\0', 8 * sizeof(char));
            rem++; //pridam riadok aby bola medzera medzi starym a novym vypisom
            continue;

        }
        SetConsoleMode(hStdin, mode); // Restore original console mode
        send_data(ConnectSocket, sendbuf, hConsole, start_x, start_y, file);
        lines = 0;
        recieve_data(ConnectSocket, recvbuf, DEFAULT_BUFLEN, hConsole, start_x, start_y, &lines, id, file, &end);
        memset(sendbuf + 13, '\0', 8 * sizeof(char));
        rem++; //pridam riadok aby bola medzera medzi starym a novym vypisom
        i++;


        if (end == 1) {
            break;
        }
    }
    




    closesocket(ConnectSocket);
    WSACleanup();
    return 0;
}
