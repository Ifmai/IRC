#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_PORT 3490 // Sunucunun dinlediği port
#define BUFFER_SIZE 1024 // Alıcı tampon boyutu

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    const char *server_ip = "127.0.0.1"; // Sunucunun IP adresi
    const char *message = "Merhaba Sunucu!";
    char buffer[BUFFER_SIZE];
    int numbytes;

    // Soket oluşturma
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // Sunucu adres yapısını hazırlama
    server_addr.sin_family = AF_INET; // IPv4
    server_addr.sin_port = htons(SERVER_PORT); // Ağ bayt sıralaması ile port numarası
    inet_pton(AF_INET, server_ip, &server_addr.sin_addr); // IP adresini binary formata çevir

    // Sunucuya bağlanma
    if (connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sockfd);
        exit(1);
    }

    std::cout << "Sunucuya bağlandı: " << server_ip << ":" << SERVER_PORT << std::endl;

    // Mesaj gönderme
    if (send(sockfd, message, strlen(message), 0) == -1) {
        perror("send");
        close(sockfd);
        exit(1);
    }

    std::cout << "Mesaj gönderildi: " << message << std::endl;

	
    // Sunucudan gelen mesajı alma
    if ((numbytes = recv(sockfd, buffer, BUFFER_SIZE - 1, 0)) == -1) {
        perror("recv");
        close(sockfd);
        exit(1);
    }

    buffer[numbytes] = '\0'; // Null-terminator ekleme
    std::cout << "Sunucudan gelen mesaj: " << buffer << std::endl;

    // Bağlantıyı kapatma
    close(sockfd);
    return 0;
}
