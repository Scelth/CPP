#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

class Client {
public:
    Client(const std::string& name, int port, int period)
        : name_(name), port_(port), period_(period) {}

    void run() {
        while (true) {
            sendMessage();
            std::this_thread::sleep_for(std::chrono::seconds(period_));
        }
    }

private:
    std::string name_;
    int port_;
    int period_;

    std::string getCurrentTime() {
        auto now = std::chrono::system_clock::now();
        auto in_time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::stringstream ss;
        ss << std::put_time(std::localtime(&in_time_t), "[%Y-%m-%d %H:%M:%S");
        ss << "." << std::setfill('0') << std::setw(3) << ms.count() << "] ";
        return ss.str();
    }

    void sendMessage() {
        int sock = 0;
        struct sockaddr_in serv_addr;
        std::string message = getCurrentTime() + name_;

        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
            std::cerr << "Socket creation error\n";
            return;
        }

        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(port_);

        if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
            std::cerr << "Invalid address/ Address not supported\n";
            return;
        }

        if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
            std::cerr << "Connection Failed\n";
            return;
        }

        send(sock, message.c_str(), message.length(), 0);
        close(sock);
    }
};

int main(int argc, char const* argv[]) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <client_name> <server_port> <period>\n";
        return -1;
    }

    std::string name = argv[1];
    int port = std::stoi(argv[2]);
    int period = std::stoi(argv[3]);

    Client client(name, port, period);
    client.run();

    return 0;
}
