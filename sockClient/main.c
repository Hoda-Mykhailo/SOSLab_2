#include <stdio.h>
#include <winsock2.h>
#include <time.h>


long long currentTimeMicroseconds() {
    struct timespec currentTime;
    clock_gettime(CLOCK_REALTIME, &currentTime);

    // Calculate time in milliseconds
    long long milliseconds = (currentTime.tv_sec * 1000000LL) + (currentTime.tv_nsec / 1000LL);
    return milliseconds;
}

int main() {
    WSADATA WSAData;
    SOCKET server;
    SOCKADDR_IN addr;

    WSAStartup(MAKEWORD(2, 0), &WSAData);
    server = socket(AF_INET, SOCK_STREAM, 0);

    u_long mode = 1;  // 1 to enable non-blocking socket
    ioctlsocket(server, FIONBIO, &mode);

    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);

    long long timeMicros = currentTimeMicroseconds();

    connect(server, (SOCKADDR *) &addr, sizeof(addr));

    printf("Connected to server! Connection took %lld microseconds\n", currentTimeMicroseconds() - timeMicros);

    timeMicros = currentTimeMicroseconds();

    char buffer[2048];
    FILE *fd = fopen("C:\\Users\\USER\\CLionProjects\\socketsClient\\sockets_test.txt", "r");
    size_t error;
    do {
        error = fread(buffer, 1, sizeof(buffer), fd);
        send(server, buffer, sizeof(buffer), 0);
    } while (error != 0);
    memset(buffer, 0, sizeof(buffer));
    buffer[0] = '\n';
    send(server, buffer, sizeof(buffer), 0);
    printf("Message sent! It took %lld microseconds\n", currentTimeMicroseconds() - timeMicros);

    timeMicros = currentTimeMicroseconds();
    closesocket(server);
    WSACleanup();
    printf("Socket closed. It took %lld microseconds", currentTimeMicroseconds() - timeMicros);
}