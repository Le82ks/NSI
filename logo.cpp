#include "logo.hpp"

#include <iostream>

#include "color.hpp"
#include "nsi_lib.hpp"

void logo() {
    std::cout << green << "[*] Starting NSI..." << reset << '\n'
              << "***************************************************\n"
              << "*                       NSI                       *\n"
              << "*            Network Security Insight             *\n"
              << "***************************************************\n"
              << "[info] Local network information and ARP-cache view.\n"
              << "[info] Active port and vulnerability scans are not run by this build.\n\n";

    std::cout << bg_red << bold << "[Local IP]" << reset << ' ' << NSI::get_network_ip()
              << "    " << bg_red << "[Interface MAC]" << reset << ' '
              << NSI::get_network_mac() << '\n'
              << bg_red << "[ARP entries]" << reset << ' ' << NSI::get_active_device_count()
              << "    " << bg_red << "[Configured target]" << reset << ' '
              << NSI::global_target_ip << '\n'
              << bg_red << "[Target MAC]" << reset << ' ' << NSI::get_target_mac()
              << "    " << bg_red << "[Vendor estimate]" << reset << ' '
              << NSI::get_target_vendor() << "\n\n";
}
