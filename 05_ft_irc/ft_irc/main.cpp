#include "include/irce.hpp"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Uso: " << argv[0] << " <puerto> <password>" << std::endl;
        return 1;
    }

    int port = std::atoi(argv[1]);
    if (port <= 1023 || port > 65535) {
        std::cerr << "Puerto inválido" << std::endl;
        return 1;
    }

    std::string password = argv[2];
    irce server(password);
    server.run(port);

    return 0;
}