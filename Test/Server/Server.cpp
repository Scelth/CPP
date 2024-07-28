#include <iostream>
#include <fstream>
#include <thread>
#include <vector>
#include <mutex>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Server {
public:
    Server(int port) : port_(port), server_fd_(0), is_running_(true) {
        std::ofstream ofs("log.txt", std::ofstream::out);
        ofs.close();
    }

    void run() {
        setupServer();

        while (is_running_) {
            int new_socket;
            struct sockaddr_in address;
            int addrlen = sizeof(address);

            if ((new_socket = accept(server_fd_, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
                std::cerr << "Accept failed\n";
                continue;
            }

            std::thread(&Server::handleClient, this, new_socket).detach();
        }

        close(server_fd_);
    }

private:
    int port_;
    int server_fd_;
    bool is_running_;
    std::mutex log_mutex_;

    void setupServer() {
        struct sockaddr_in address;
        int opt = 1;

        if ((server_fd_ = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
            std::cerr << "Socket failed\n";
            exit(EXIT_FAILURE);
        }

        if (setsockopt(server_fd_, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
            std::cerr << "Setsockopt failed\n";
            exit(EXIT_FAILURE);
        }

        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(port_);

        if (bind(server_fd_, (struct sockaddr*)&address, sizeof(address)) < 0) {
            std::cerr << "Bind failed\n";
            exit(EXIT_FAILURE);
        }

        if (listen(server_fd_, 3) < 0) {
            std::cerr << "Listen failed\n";
            exit(EXIT_FAILURE);
        }
    }

    void handleClient(int socket) {
        char buffer[1024] = { 0 };
        int valread = read(socket, buffer, 1024);
        if (valread > 0) {
            std::string message(buffer, valread);
            logMessage(message);
        }
        close(socket);
    }

    void logMessage(const std::string& message) {
        std::lock_guard<std::mutex> guard(log_mutex_);
        std::ofstream log_file("log.txt", std::ios_base::app);
        log_file << message << std::endl;
    }
};

int main(int argc, char const* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <port>\n";
        return -1;
    }

    int port = std::stoi(argv[1]);

    Server server(port);
    server.run();

    return 0;
}
