#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include "color.hpp"
#include "../src/nsi_lib.hpp"

using namespace std;



void logo() {
    std::cout << green << "[*]" << reset << "Starting NSI... " << std::endl;
    system("clear");
    {

        std::cout <<  "***************************************************"  << std::endl;
        std::cout <<  "*                       *                         *"  << std::endl;
        std::cout <<  "*                      NSI                        *"  << std::endl;
        std::cout <<  "*            Network Security Insight             *"  << std::endl;
        std::cout <<  "*                      ---                        *"  << std::endl;
        std::cout <<  "*       Dev.Basil      and       All Team         *"  << std::endl;
        std::cout <<  "*    2026 ============================= 1448      *"  << std::endl;
        std::cout <<  "***************************************************"  << std::endl;

        this_thread::sleep_for(std::chrono::milliseconds(300));
    }
    std::cout << green << "[info]" << reset << "NSI: A minimalist, header-only C++ network security utility." << reset << std::endl;
    this_thread::sleep_for(std::chrono::milliseconds(300));
    std::cout << "Engineered for Arch Linux using raw POSIX sockets and low-level calls." << std::endl;
    this_thread::sleep_for(std::chrono::milliseconds(200));
    std::cout << "Built for high-performance port scanning and intelligent parsing." << std::endl;
    
    std::cout << bg_yellow << "[info]" << reset << " " << "The code now starts scanning the router's website" << std::endl;
    {
        NSI::set_target_ip("192.168.1.1");
        NSI::set_network_interface("wlan0");
    }
    this_thread::sleep_for(std::chrono::milliseconds(700));
    {
        std::cout << "" << std::endl;

        cout << " " <<  endl;
        this_thread::sleep_for(std::chrono::milliseconds(900)); // milliseconds 0.7

        std::cout << bg_red << bold << "[IP]" << reset << " " << green << NSI::global_target_ip << reset << "           " << bg_red << "[MAC]" << reset << " " << green << NSI::get_network_mac() << reset << std::endl;
        std::cout << bg_red << bold << "[ADC]" << reset << " " << green << NSI::get_active_device_count() << reset << "                    " <<  bg_red << "[vendor]" << reset << " " << green << NSI::get_target_vendor() << std::endl;
        std::cout << bg_red << bold << "[Status]" << reset << " " << green << "Online" <<  reset << "            " << bg_red << "[Type]"  << reset << " " << green  << "Router" << reset << std::endl;
        std::cout << "====================================================" << std::endl;
        std::cout << red << "[*]" << reset << "information" << std::endl;
        std::cout << " " << std::endl;


    }
}
