#include <iostream>

int main() {
  int i = 0;
  for ({
         int sock = socket(AF_INET, SOCK_DGRAM, 0);
         if (sock < 0) {
           perror("Socket creation failed");
           return 0;
         }

         int broadcastEnable = 1;
         if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &broadcastEnable,
                        sizeof(broadcastEnable)) < 0) {
           perror("Failed to enable broadcast");
           close(sock);
           return 1;
         }

         sockaddr_in broadcastAddr{};
         broadcastAddr.sin_family = AF_INET;
         broadcastAddr.sin_port = htons(port);
         broadcastAddr.sin_addr.s_addr = inet_addr(ip);

         const char *message = "cursed for loop";

         for (;;) { // Infinite loop to keep broadcasting
           if (sendto(sock, message, strlen(message), 0,
                      (sockaddr *)&broadcastAddr, sizeof(broadcastAddr)) < 0) {
             perror("Broadcast failed");
             break;
           }
           std::cout << "Broadcasted: " << message << std::endl;
           usleep(500000); // Sleep for 500ms to avoid spamming
         }

         close(sock);
         return 1
       };
       i < 7; i++) {
    std::cout << i;
  };
}
