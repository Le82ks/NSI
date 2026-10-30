
void nsi_room_port () {

#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <mutex>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

std::mutex cout_mutex;

void scan_port_range(const std::string& target_ip, int start_port, int end_port) {
    for (int port = start_port; port <= end_port; ++port) {
        int sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) continue;

        struct timeval timeout;
        timeout.tv_sec = 0;
        timeout.tv_usec = 200000;  
        setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
        setsockopt(sock, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

        sockaddr_in server_addr{};
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(port);
        inet_pton(AF_INET, target_ip.c_str(), &server_addr.sin_addr);

        int result = connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));
        
        if (result == 0) {
            std::lock_guard<std::mutex> lock(cout_mutex);
            std::cout << "[OPEN] Port " << port << "/tcp detected active.\n";
            
            if (port == 21) std::cout << "       └── [WARN: FTP service detected]\n";
            else if (port == 23) std::cout << "       └── [CRITICAL: Telnet plaintext protocol]\n";
            else if (port == 80 || port == 8080) std::cout << "       └── [INFO: HTTP web service]\n";
            else if (port == 443) std::cout << "       └── [SECURE: HTTPS encrypted traffic]\n";
            else if (port == 3306) std::cout << "       └── [WARN: MySQL Database port exposed]\n";
        }
        
        close(sock);
    }
}

void nsi_room_port() {
    std::string target_ip = "127.0.0.1"; 
    int total_ports = 65535;
    int num_threads = 100; 
    int ports_per_thread = total_ports / num_threads;

    std::cout << "\n[+] Initializing Full Port Scan (1 - 65535) via NSI Engine...\n";
    std::cout << "[*] Target: " << target_ip << "\n";
    std::cout << "[*] Threads active: " << num_threads << " | Please wait...\n";
    std::cout << "------------------------------------------------------------\n";

    std::vector<std::thread> threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * ports_per_thread + 1;
        int end = (i == num_threads - 1) ? total_ports : (start + ports_per_thread - 1);
        threads.emplace_back(scan_port_range, target_ip, start, end);
    }

    for (auto& th : threads) {
        th.join();
    }

    std::cout << "------------------------------------------------------------\n";
    std::cout << "[+] Full port scan completed successfully without external tools.\n\n";
}
