#define COMM_CLIENT_H_
#define COMM_CLIENT_H_

#include "internal/comm_configure.hpp"

namespace {

class Client {
public:
    Client(std::string host_address, int port, bool debug);

    ~Client();

    void Setup();

    void CloseSocket();

    void Start();

    void SendValue(uint32_t value);

    void RecvValue(uint32_t &value);

    // TODO: SendVector, RecvVector, SendArray, RecvArray

    std::string GetHostAddress();

    int GetPortNumber();

    uint32_t GetTotalBytesSent() const;

    void ClearTotalBytesSent();
private:
    std::string host_address_;
    int         port_;
    int         client_fd_;
    uint32_t    total_bytes_sent_;
};

} // namespace comm

#endif // COMM_CLIENT_H_
