#ifndef COMM_SERVER_H_
#define COMM_SERVER_H_

#include "internal/comm_configure.hpp"


namespace comm {

class Server {
public:

    Server(const int port, const bool debug);

    ~Server();

    void Setup();

    void CloseSocket();

    void Start();

    void SendValue(uint32_t value);

    void RecvValue(uint32_t &value);

    void SendVector(std::vector<uint32_t> &vector);

    int GetPortNumber() const;

    uint32_t GetTotalBytesSent() const;

    void ClearTotalBytesSent();

private:
    int      port_;             /**< The port number used for the server. */
    int      server_fd_;        /**< File descriptor for the server socket. */
    int      client_fd_;        /**< File descriptor for the client socket. */
    uint32_t total_bytes_sent_; /**< Total number of bytes sent to the client. */
};

}    // namespace comm

#endif    // COMM_SERVER_H_
