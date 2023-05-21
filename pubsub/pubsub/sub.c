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
    struct sockaddr_in servaddr;
    char sendline[MAXLINE], recvline[MAXLINE];
    FILE *fp;
    long int sz;
    char *ip_addr = NULL;
    int port = 0;
    char *file_name = NULL;
    int opt;

    while ((opt = getopt(argc, argv, "h:p:f:")) != -1) {
        switch (opt) {
        case 'h':
            ip_addr = optarg;
            break;
        case 'p':
            port = atoi(optarg);
            break;
        case 'f':
            file_name = optarg;
            break;
        default:
            fprintf(stderr, "Usage: %s [-h IP_address] [-p port] [-f file_name]\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Kiểm tra đầu vào
    if (ip_addr == NULL || port == 0 || file_name == NULL) {
        fprintf(stderr, "IP address, port, and file name are required.\n");
        exit(EXIT_FAILURE);
    }

    // Tạo socket UDP
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        error("Could not create socket");
    }

    // Khởi tạo địa chỉ server
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(port);
    if (inet_pton(AF_INET, ip_addr, &servaddr.sin_addr) <= 0) {
        error("inet_pton error");
    }

    // Mở file để đọc
    fp = fopen(file_name, "rb");
    if (fp == NULL) {
        error("Could not open file");
    }

    // Tính kích thước file
    fseek(fp, 0L, SEEK_END);
    sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    // Gửi kích thước file đến server
    sprintf(sendline, "%ld", sz);
    if (sendto(sockfd, sendline, strlen(sendline), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        error("Error sending size");
    }

    // Đọc từng phần của file và gửi đến server
    int remaining_data = sz;
    while (remaining_data > 0) {
        int bytes_read = fread(sendline, sizeof(char), MAXLINE, fp);
        if (bytes_read < 0) {
            error("Error reading file");
        }
        remaining_data -= bytes_read;
        if (sendto(sockfd, sendline, bytes_read, 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
            error("Error sending file");
        }
    }

    // Đóng file và socket
    fclose(fp);
    close(sockfd);

    return 0;
}
