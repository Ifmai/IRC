#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MYPORT 3490 // Dinlenecek port numarası
#define BACKLOG 10 // Bekleme kuyruğu uzunluğu
#define BUFFER_SIZE 1024 // Alıcı tampon boyutu

int main() {
    int sockfd, new_fd;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr;
    socklen_t sin_size;
    int yes = 1;
    char buffer[BUFFER_SIZE];
    const char *response = "Merhaba İstemci!";

    // Soket oluşturma
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    // SO_REUSEADDR seçeneğini ayarlama
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
        perror("setsockopt");
        exit(1);
    }

    // Adres yapısını hazırlama
    my_addr.sin_family = AF_INET; // IPv4
    my_addr.sin_port = htons(MYPORT); // Ağ bayt sıralaması ile port numarası
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY); // Herhangi bir yerel IP adresi
    memset(&(my_addr.sin_zero), '\0', 8); // Yapının geri kalanını sıfırlama

    // Soketi IP adresine ve porta bağlama
    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(1);
    }

    // Soketi dinleme moduna geçirme
    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        close(sockfd);
        exit(1);
    }

    printf("Soket başarıyla oluşturuldu ve dinleniyor...\n");

    // Bağlantıları kabul etme döngüsü
    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size);
        if (new_fd == -1) {
            perror("accept");
            continue;
        }

        printf("Yeni bağlantı kabul edildi: %s\n", inet_ntoa(their_addr.sin_addr));

        // İstemciden gelen mesajı alma
        int numbytes = recv(new_fd, buffer, BUFFER_SIZE - 1, 0);
        if (numbytes == -1) {
            perror("recv");
            close(new_fd);
            continue;
        }
        buffer[numbytes] = '\0'; // Null-terminator ekleme
        printf("İstemciden gelen mesaj: %s\n", buffer);

        // İstemciye yanıt gönderme
        if (send(new_fd, response, strlen(response), 0) == -1) {
            perror("send");
        }

        // Bağlantıyı kapatma
        close(new_fd);
    }

    close(sockfd); // Ana soketi kapatma
    return 0;
}
