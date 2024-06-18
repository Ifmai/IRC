#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    struct sockaddr_in their_addr;
    int opt = 1;
    int addrlen = sizeof(address);
    char buffer[1024] = {0};

    // Soket oluştur
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Portu ve adresi ayarla
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
	 memset(&(address.sin_zero), '\0', 8); // Yapının geri kalanını sıfırlama


    // Soketi adrese bağla
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    // Dinlemeye başla
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    // Bağlantıyı kabul et


    std::vector<std::string> command_parts;
    while (true) {
		if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
    	    perror("accept");
        	exit(EXIT_FAILURE);
    	}
        printf("Yeni bağlantı kabul edildi: %s\n", inet_ntoa(their_addr.sin_addr));
        int valread = recv(new_socket, buffer, 1024, 0);
        if (valread <= 0) {
            break;
        }

        buffer[valread] = '\0';
        std::string part(buffer);

        // Boş dize alınırsa, komutu birleştir
        if (part == "\n") {
			std::cout << "AMIN EVLADI request : " << part << std::endl;
            std::string full_command;
            for (std::vector<std::string>::const_iterator it = command_parts.begin(); it != command_parts.end(); ++it) {
                full_command += *it;
            }
            std::cout << "Tam Komut: " << full_command << std::endl;
            command_parts.clear(); // Sonraki komut için temizle

            // İstemciye geri gönder (isteğe bağlı)
            std::string response = "Received command: " + full_command + "\n";
            send(new_socket, response.c_str(), response.size(), 0);
        } else {
            command_parts.push_back(part);
			std::cout << "request :" << part << std::endl;
        }
    }
    
    close(new_socket);
    close(server_fd);
    return 0;
}
