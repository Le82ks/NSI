#ifndef NSI_LIB_HPP
#define NSI_LIB_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cctype>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <net/if.h>
#include <netdb.h>
namespace NSI {
  
  inline std::string global_target_ip = "192.168.1.1";
  inline std::string global_interface = "wlan0";

  
  inline void set_target_ip(const std::string& ip) {
    global_target_ip = ip;
  }
  inline void set_network_interface(const std::string& iface) {
    global_interface = iface;
  }

  // 10 Functions

  inline std::string get_network_ip() {

    struct ifaddrs *ifaddr, *ifa;
    char host [NI_MAXHOST];
    std::string local_ip = "127.0.0.1";

    if (getifaddrs(&ifaddr) == -1) return local_ip;

    for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
        if(ifa->ifa_addr == NULL) continue;
        int family = ifa->ifa_addr->sa_family;

        if(family == AF_INET && std::string(ifa->ifa_name) != "lo") {
            int s = getnameinfo(ifa->ifa_addr, sizeof(struct sockaddr_in),
             host, NI_MAXHOST, NULL , 0 , NI_NUMERICHOST);
        
        if (s == 0) {
            local_ip = std::string(host);
            break;
        }
    }
}
freeifaddrs(ifaddr);
return local_ip;
}


inline std::string get_target_mac() {
      std::ifstream arp_file("/proc/net/arp");
      std::string line;

      if(arp_file.is_open()) {
          std::getline(arp_file, line);

          while (std::getline(arp_file, line)) {
              std::istringstream iss(line);
             std::string ip, hw_type, flags, mac, mask, dev;

              if(iss >> ip >> hw_type >> flags >> mac >> mask >> dev) {
                  if(ip == global_target_ip) {
                      arp_file.close();
                      return mac;
                }
            }
        }
        arp_file.close();
    }
    return "Not-Found-In-Cache";
}

inline std::string get_network_mac() {

  std::string path = "/sys/class/net/" + global_interface + "/address";
  std::ifstream mac_file(path);
  std::string mac = "00:00:00:00:00:00";

  if (mac_file.is_open()) {
    
    std::getline(mac_file,mac);
    mac_file.close();
    
  }
  return mac;
}

//Network name

inline std::string get_target_vendor () {
  std::string mac = get_target_mac();
  if(mac.length() < 8) return "Unknown Vendor";

  std::string oui = "";
  for(int i = 0; i < 8; i++) {
    oui += static_cast<char>(tolower(static_cast<unsigned char>(mac[i])));
  }
  if (oui.find("00:11:22") == 0 || oui.find("00:00:0c") == 0 || oui.find("00:1a:2f") == 0) return "Cisco Systems";
        if (oui.find("48:d5:39") == 0 || oui.find("00:e0:fc") == 0 || oui.find("28:6e:d4") == 0 || oui.find("88:53:2e") == 0) return "Huawei Technologies";
        if (oui.find("f4:ec:38") == 0 || oui.find("e8:de:27") == 0 || oui.find("50:3f:2d") == 0 || oui.find("14:eb:b6") == 0) return "TP-Link Technologies";
        if (oui.find("60:32:b1") == 0 || oui.find("c0:25:a5") == 0 || oui.find("84:16:f9") == 0 || oui.find("b8:27:eb") == 0) return "Netgear / Raspberry Pi";
        if (oui.find("b4:75:0e") == 0 || oui.find("1c:3b:f3") == 0 || oui.find("30:b5:c2") == 0) return "ASUSTeK Computer / ASUS Routers";
        if (oui.find("24:de:c6") == 0 || oui.find("98:da:c4") == 0 || oui.find("70:4f:57") == 0) return "TP-Link / Archer Router";
        if (oui.find("00:1d:7e") == 0 || oui.find("00:24:fe") == 0) return "D-Link Systems";
        if (oui.find("00:25:9c") == 0 || oui.find("c8:3a:35") == 0) return "Netgear Inc";
        if (oui.find("00:04:ed") == 0 || oui.find("00:22:75") == 0) return "Zyxel Communications";
        if (oui.find("00:1f:9f") == 0 || oui.find("64:16:8f") == 0) return "Buffalo Inc";
        if (oui.find("00:26:ed") == 0 || oui.find("5c:3f:a3") == 0) return "MikroTikls (MikroTik)";
        if (oui.find("00:0c:42") == 0 || oui.find("64:d1:54") == 0) return "MikroTik RouterOS";
        if (oui.find("00:24:6c") == 0 || oui.find("e0:28:61") == 0) return "Ubiquiti Networks";
        if (oui.find("74:ac:b9") == 0 || oui.find("80:2a:a8") == 0) return "Ubiquiti UniFi";
        if (oui.find("00:50:56") == 0 || oui.find("00:0c:29") == 0 || oui.find("00:05:69") == 0) return "VMware Virtualization";
        if (oui.find("52:54:00") == 0) return "QEMU / KVM Virtual Machine";

        if (oui.find("00:17:88") == 0 || oui.find("34:c0:59") == 0 || oui.find("78:4f:43") == 0 || oui.find("ac:bc:32") == 0) return "Apple Inc";
        if (oui.find("00:03:93") == 0 || oui.find("18:65:90") == 0 || oui.find("bc:67:78") == 0) return "Apple iPhone / Mac";
        if (oui.find("00:1f:3b") == 0 || oui.find("38:f8:86") == 0 || oui.find("9c:da:be") == 0) return "Samsung Electronics";
        if (oui.find("00:21:43") == 0 || oui.find("5c:51:88") == 0 || oui.find("cc:fa:00") == 0) return "Samsung Mobile";
        if (oui.find("64:bc:58") == 0 || oui.find("74:5c:89") == 0 || oui.find("f8:a4:5f") == 0) return "Xiaomi Communications";
        if (oui.find("28:6d:cd") == 0 || oui.find("84:78:8b") == 0 || oui.find("c0:ee:fb") == 0) return "Xiaomi / Redmi";
        if (oui.find("50:81:40") == 0 || oui.find("68:9a:87") == 0 || oui.find("ac:f3:8d") == 0) return "OnePlus Technology";
        if (oui.find("40:4d:7f") == 0 || oui.find("54:8d:5a") == 0 || oui.find("c8:d7:19") == 0) return "Oppo Mobile";
        if (oui.find("b0:f8:93") == 0 || oui.find("e0:75:7d") == 0 || oui.find("f4:8c:eb") == 0) return "Vivo Mobile";
        if (oui.find("00:23:7d") == 0 || oui.find("38:0a:94") == 0 || oui.find("60:fa:cd") == 0) return "Motorola Mobility";
        if (oui.find("00:24:d7") == 0 || oui.find("34:23:ba") == 0 || oui.find("74:da:da") == 0) return "HTC Corporation";
        if (oui.find("00:1d:0f") == 0 || oui.find("24:df:6a") == 0) return "Sony Mobile / Xperia";
        if (oui.find("00:09:bf") == 0 || oui.find("00:1e:10") == 0) return "Nintendo Co Ltd";
        if (oui.find("28:0d:fc") == 0 || oui.find("f8:d0:bd") == 0) return "Sony Interactive Entertainment (PlayStation)";
        if (oui.find("7c:ed:8d") == 0 || oui.find("b8:81:98") == 0) return "Microsoft Xbox";

        if (oui.find("00:1e:68") == 0 || oui.find("3c:97:0e") == 0 || oui.find("b0:83:fe") == 0) return "Dell Inc";
        if (oui.find("6c:2b:59") == 0 || oui.find("f0:1d:bc") == 0 || oui.find("a4:bb:6d") == 0) return "Dell Technologies";
        if (oui.find("00:14:5e") == 0 || oui.find("9c:8e:99") == 0 || oui.find("b4:96:91") == 0) return "Hewlett Packard (HP)";
        if (oui.find("00:11:0a") == 0 || oui.find("3c:d9:2b") == 0 || oui.find("f8:bc:12") == 0) return "Hewlett Packard Enterprise";
        if (oui.find("00:21:5e") == 0 || oui.find("68:f7:28") == 0 || oui.find("f8:28:19") == 0) return "Lenovo";
        if (oui.find("00:22:6b") == 0 || oui.find("10:65:30") == 0 || oui.find("b8:ee:65") == 0) return "Quanta / Lenovo Laptop";
        if (oui.find("00:1f:29") == 0 || oui.find("50:7b:9d") == 0 || oui.find("70:5a:0f") == 0) return "Intel Corporate";
        if (oui.find("00:25:64") == 0 || oui.find("28:f1:0e") == 0) return "Intel Wireless";
        if (oui.find("00:15:17") == 0 || oui.find("00:26:55") == 0) return "Hon Hai Precision (Foxconn)";
        if (oui.find("2c:4d:54") == 0 || oui.find("60:45:cb") == 0) return "ASUSTeK Computer Inc";
        if (oui.find("00:23:54") == 0 || oui.find("00:26:2d") == 0) return "Gigabyte Technology";
        if (oui.find("00:07:e9") == 0 || oui.find("00:1b:21") == 0) return "Intel Corporate / Desktop";

        if (oui.find("68:54:5a") == 0 || oui.find("70:ee:50") == 0) return "Google Nest / Home";
        if (oui.find("00:1a:11") == 0 || oui.find("f4:f5:e8") == 0) return "Google Inc";
        if (oui.find("68:37:e9") == 0 || oui.find("ac:63:be") == 0) return "Amazon Technologies (Echo / Fire)";
        if (oui.find("00:fc:8b") == 0 || oui.find("50:dc:e7") == 0) return "Amazon Echo Dot";
        if (oui.find("b8:27:eb") == 0 || oui.find("dc:a6:32") == 0) return "Raspberry Pi Foundation";
        if (oui.find("00:12:17") == 0 || oui.find("00:18:31") == 0) return "Cisco Systems / Linksys";
        if (oui.find("00:24:81") == 0 || oui.find("cc:2d:b9") == 0) return "Synology Inc (NAS)";
        if (oui.find("00:11:32") == 0 || oui.find("00:11:32") == 0) return "QNAP Systems (NAS)";
        if (oui.find("00:23:cd") == 0 || oui.find("c0:56:27") == 0) return "Dahua Technology (Cameras)";
        if (oui.find("24:5a:4c") == 0 || oui.find("64:9e:f3") == 0) return "Hangzhou Hikvision (Cameras)";

        if (oui.find("00:01:80") == 0) return "Samsung Electro-Mechanics";
        if (oui.find("00:02:c7") == 0) return "Azkoyen S.A.";
        if (oui.find("00:04:20") == 0) return "PCS Computer Systems";
        if (oui.find("00:05:5d") == 0) return "D-Link Corporation";
        if (oui.find("00:08:74") == 0) return "Dell Computer Corp";
        if (oui.find("00:0d:60") == 0) return "Pegatron Corporation";
        if (oui.find("00:12:3f") == 0) return "Telsey S.p.A.";
        if (oui.find("00:15:af") == 0) return "Gemtek Technology";
        if (oui.find("00:18:4d") == 0) return "Askey Computer Corp";
        if (oui.find("00:1b:2f") == 0) return "Danfoss A/S";
        if (oui.find("00:22:3f") == 0) return "Sagem Communications";
        if (oui.find("00:25:86") == 0) return "Arris Group Inc (Modem/Router)";
        if (oui.find("00:26:b9") ==0) return "Technicolor";
        if (oui.find("7c:4f:b5") == 0) return "TP-Link Corporation";
        if (oui.find("90:9f:33") == 0) return "Liteon Technology";
        if (oui.find("cc:2d:e0") == 0) return "Intel Corporate";

        if(global_target_ip == "192.168.1.1" || global_target_ip == "192.168.0.1") {
          return "Default Network Gateway / Router";
        }

        return "Unknown / Generic Manufacturer (" + oui + ")";
}

inline int get_active_device_count() {
  std::ifstream arp_file ("/proc/net/arp");
  std::string line;
  int active_count = 0;

  if (arp_file.is_open()) {
    std::getline(arp_file, line);
    while (std::getline(arp_file, line)) {
      std::istringstream iss (line);
      std::string ip , hw_type , flags, mac, mask, dev;

      if (iss >> ip >> hw_type >> flags >> mac >> mask >> dev ) {

        if (mac != "00:00:00:00:00:00" && mac != "Not_found_in_cache") {
          active_count++;
        }
      }
    }
    arp_file.close();
  }
  return active_count;
}


}

#endif