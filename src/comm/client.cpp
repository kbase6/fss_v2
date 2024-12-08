#include "client.hpp"

namespace comm {

Client::Client(std::string host_address, int port) : host_address_(host_address), port_(port) {}

Client::~Client() { this->CloseSocket(); }

void Client::Setup() {
    this->client_fd_ = socket(PF_INET, SOCK_STREAM, 0);
    if (this->client_fd_ < 0) {
        exit(EXIT_FAILURE);
    }
}

void Client::CloseSocket() {
    close(this->client_fd_);
}

void Client::Start() {
    // Setup socket address structure
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(this->port_);
    server_address.sin_addr.s_addr = inet_addr(this->host_address_.c_str());

    // Connect to server
    int status = connect(this->client_fd_, (const sockaddr *)&server_address, sizeof(server_address));
    if (status < 0) {
        exit(EXIT_FAILURE);
    }
}

void Client::SendValue(uint32_t value) {
    // Send data
    bool is_sent = internal::SendData(this->client_fd_, reinterpret_cast<const char *>(&value), sizeof(value));
    if (!is_sent) {
        this->CloseSocket();
        exit(EXIT_FAILURE);
    }
    this->total_bytes_sent_ += sizeof(value);
}

void Client::RecvValue(uint32_t &value) {
    // Receive data
    bool is_received = internal::RecvData(this->client_fd_, reinterpret_cast<char *>(&value), sizeof(value));
    if (!is_received) {
        this->CloseSocket();
        exit(EXIT_FAILURE);
    }
}

std::string Client::GetHostAddress() {
    return this->host_address_;
}

int Client::GetPortNumber() {
    return this->port_;
}

uint32_t Client::GetTotalBytesSent() const {
    return this->total_bytes_sent_;
}

void Client::ClearTotalBytesSent() {
    this->total_bytes_sent_ = 0;
}

} // namespace comm
