#pragma once

#include <arpa/inet.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <netdb.h>
#include <sys/socket.h>

#include <cctype>
#include <fstream>
#include <sstream>
#include <string>

namespace NSI {

inline std::string global_target_ip = "192.168.1.1";
inline std::string global_interface;

inline bool set_target_ip(const std::string& ip) {
    in_addr parsed{};
    if (inet_pton(AF_INET, ip.c_str(), &parsed) != 1) {
        return false;
    }
    global_target_ip = ip;
    return true;
}

inline bool set_network_interface(const std::string& iface) {
    if (iface.empty() || iface.size() >= IFNAMSIZ || if_nametoindex(iface.c_str()) == 0) {
        return false;
    }
    for (const unsigned char ch : iface) {
        if (!(std::isalnum(ch) || ch == '_' || ch == '-' || ch == '.')) {
            return false;
        }
    }
    global_interface = iface;
    return true;
}

inline std::string get_network_ip() {
    ifaddrs* interfaces = nullptr;
    if (getifaddrs(&interfaces) != 0) {
        return "Unavailable";
    }

    std::string result = "Unavailable";
    for (const ifaddrs* item = interfaces; item != nullptr; item = item->ifa_next) {
        if (item->ifa_addr == nullptr || item->ifa_addr->sa_family != AF_INET ||
            item->ifa_name == nullptr || std::string(item->ifa_name) == "lo") {
            continue;
        }
        if (!global_interface.empty() && global_interface != item->ifa_name) {
            continue;
        }
        char address[INET_ADDRSTRLEN]{};
        const auto* ipv4 = reinterpret_cast<const sockaddr_in*>(item->ifa_addr);
        if (inet_ntop(AF_INET, &ipv4->sin_addr, address, sizeof(address)) != nullptr) {
            result = address;
            if (global_interface.empty()) {
                global_interface = item->ifa_name;
            }
            break;
        }
    }
    freeifaddrs(interfaces);
    return result;
}

inline std::string get_target_mac() {
    std::ifstream arp_file("/proc/net/arp");
    std::string line;
    std::getline(arp_file, line);  // Skip the table header.
    while (std::getline(arp_file, line)) {
        std::istringstream row(line);
        std::string ip, hardware_type, flags, mac, mask, device;
        if (row >> ip >> hardware_type >> flags >> mac >> mask >> device && ip == global_target_ip) {
            return mac;
        }
    }
    return "Not in ARP cache";
}

inline std::string get_network_mac() {
    if (global_interface.empty()) {
        (void)get_network_ip();  // Discover a usable interface if possible.
    }
    if (global_interface.empty()) {
        return "Unavailable";
    }
    std::ifstream mac_file("/sys/class/net/" + global_interface + "/address");
    std::string mac;
    return std::getline(mac_file, mac) ? mac : "Unavailable";
}

inline std::string get_target_vendor() {
    const std::string mac = get_target_mac();
    if (mac.size() < 8 || mac == "Not in ARP cache") {
        return "Unknown (target not present in ARP cache)";
    }
    const std::string oui = mac.substr(0, 8);
    if (oui == "00:1a:2f" || oui == "00:00:0c") return "Cisco (OUI match)";
    if (oui == "f4:ec:38" || oui == "50:3f:2d") return "TP-Link (OUI match)";
    if (oui == "00:1d:7e" || oui == "00:24:fe") return "D-Link (OUI match)";
    return "Unknown (OUI database not included)";
}

inline int get_active_device_count() {
    std::ifstream arp_file("/proc/net/arp");
    std::string line;
    std::getline(arp_file, line);  // Skip the table header.
    int count = 0;
    while (std::getline(arp_file, line)) {
        std::istringstream row(line);
        std::string ip, hardware_type, flags, mac, mask, device;
        if (!(row >> ip >> hardware_type >> flags >> mac >> mask >> device)) {
            continue;
        }
        unsigned int flag_value = 0;
        std::istringstream parsed_flags(flags);
        parsed_flags >> std::hex >> flag_value;
        if (parsed_flags && (flag_value & 0x2U) != 0U && mac != "00:00:00:00:00:00") {
            ++count;
        }
    }
    return count;
}

}  // namespace NSI
