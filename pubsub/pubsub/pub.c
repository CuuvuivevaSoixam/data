#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <getopt.h>

#define MAXLINE 1024

void error(char *msg) {
    perror(msg);
    exit(1);
}

int main(int argc, char **argv) {
    int sockfd, n;
    int port;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    char buffer[MAXLINE];
    FILE *fp;
    long int sz;
    int opt;
    
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
        case 'p':
            port = atoi(optarg);
            break;
        default:
            fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }
    
    // Tạo socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error("Could not create socket");
    }

    // Khởi tạo địa chỉ server
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(port);

    // Ràng buộc địa chỉ với socket
    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        error("Bind failed");
    }

    // Nhận kích thước file từ client
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
    if (n < 0) {
        error("Error receiving size");
    }
    buffer[n] = '\0';
    sz = atoi(buffer);

    // Tạo file mới để lưu trữ dữ liệu nhận được
    fp = fopen("received.txt", "wb");
    if (fp == NULL) {
        error("Could not create file");
    }

    // Nhận từng phần của file từ client và ghi vào file vừa tạo
    int remaining_data = sz;
    while (remaining_data > 0) {
        len = sizeof(cliaddr);
        n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
        if (n < 0) {
            error("Error receiving file");
        }
        fwrite(buffer, sizeof(char), n, fp);
        remaining_data -= n;
    }

    // Đóng file và socket
    fclose(fp);
    close(sockfd);

    return 0;
}
