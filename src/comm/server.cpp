#include "server.hpp"

namespace comm {

Server::Server(const int port, const bool debug)
    : port_(port), debug_(debug) {
}

Server::~Server() {
    this->CloseSocket();
}

void Server::Setup() {
    // Create socket
    this->server_fd_ = socket(PF_INET, SOCK_STREAM, 0);
    if (this->server_fd_ < 0) {
        std::perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Setup socket address structure
    sockaddr_in server_address;
    memset(&server_address, 0, sizeof(server_address));
    server_address.sin_family      = AF_INET;
    server_address.sin_port        = htons(this->port_);
    server_address.sin_addr.s_addr = INADDR_ANY;

    // Set socket to immediately reuse port when the application closes
    const int opt = 1;
    if (setsockopt(this->server_fd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0) {
        utils::Logger::FatalLog(LOCATION, "Failed to set socket option");
        exit(EXIT_FAILURE);
    }

    // Call bind to associate the socket with our local address and port
    if (bind(this->server_fd_, (const struct sockaddr *)&server_address, sizeof(server_address)) < 0) {
        utils::Logger::FatalLog(LOCATION, "Failed to bind socket");
        exit(EXIT_FAILURE);
    }

    // Convert the socket to listen for incoming connections
    if (listen(this->server_fd_, 3) < 0) {
        utils::Logger::FatalLog(LOCATION, "Failed to listen on socket");
        exit(EXIT_FAILURE);
    }
    utils::Logger::TraceLog(LOCATION, "Server listening on port " + std::to_string(this->port_) + "...", this->debug_);
}

void Server::CloseSocket() {
    close(this->server_fd_);
    close(this->client_fd_);
}

void Server::Start() {
    // Setup client
    sockaddr_in client_address;
    socklen_t   client_length = sizeof(client_address);

    // Accept clients
    this->client_fd_ = accept(this->server_fd_, (struct sockaddr *)&client_address, &client_length);
    if (client_fd_ < 0) {
        utils::Logger::FatalLog(LOCATION, "Failed to accept client");
        exit(EXIT_FAILURE);
    }
    utils::Logger::TraceLog(LOCATION, "Client connected", this->debug_);
}

void Server::SendValue(uint32_t value) {
    // Send data
    bool is_sent = internal::SendData(this->client_fd_, reinterpret_cast<const char *>(&value), sizeof(value));
    if (!is_sent) {
        utils::Logger::FatalLog(LOCATION, "Failed to send uint32_t data");
        this->CloseSocket();
        exit(EXIT_FAILURE);
    }
    this->total_bytes_sent_ += sizeof(value);
    utils::Logger::TraceLog(LOCATION, "Sent data: " + std::to_string(value), this->debug_);
}

void Server::RecvValue(uint32_t &value) {
    // Receive data
    bool is_received = internal::RecvData(this->client_fd_, reinterpret_cast<char *>(&value), sizeof(value));
    if (!is_received) {
        utils::Logger::FatalLog(LOCATION, "Failed to receive uint32_t data");
        this->CloseSocket();
        exit(EXIT_FAILURE);
    }
    utils::Logger::TraceLog(LOCATION, "Received data: " + std::to_string(value), this->debug_);
}

int Server::GetPortNumber() const {
    return this->port_;
}

uint32_t Server::GetTotalBytesSent() const {
    return this->total_bytes_sent_;
}

void Server::ClearTotalBytesSent() {
    this->total_bytes_sent_ = 0;
}

}    // namespace comm
