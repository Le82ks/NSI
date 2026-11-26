#include "website.hpp"

namespace NSI {
    inline void scan_website() {

        
        // start nmappppp
        FILE* pipe = popen ("nmap --open -P -F 80,443 192.168.1.1 2>/dev/null", "r");
        if (!pipe) return;

        char buffer[256];
        std::cout << "[" << bg_navy << now_time() << reset << "]" << " "  << bg_yellow << "[info]" << reset << " " << bg_blue << "[important]"  << reset  << " " << "The router protocols will now be displayed for your review (the tool may make mistakes, as it is not infallible)." << std::endl;
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::string line(buffer);
            /////////////////////////
            if (line.find("80") != std::string::npos) {
                std::cout << "[" << bold << bg_navy << now_time() << reset << "]" << " " << bg_white << "[Available]" << reset << " " << green << "http" << reset << bg_yellow <<  bold << "http://192.168.1.1" << std::endl;
            }
            {

            }
            if (line.find("443") != std::string::npos) {
                std::cout << "[" << bold << bg_navy << now_time() << reset << "]" << " " << bg_yellow  << "[info]" << reset << " " << bg_white << "[Available]" << reset << " " << green << bold <<  "https" << reset << " " << bg_yellow  <<bold << "https://192.168.1.1" << reset << std::endl;
            }
            
        }
        pclose(pipe);
        
    }

}