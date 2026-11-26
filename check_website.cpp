#include "check_website.hpp"

namespace NSI {
    inline void check_website() {
        
        FILE* pipe = popen("nuclei -target 192.168.1.1 -severity low,medium,high,critical 2>/dev/null", "r");
        if (!pipe) {
            std::cout << "[!] Error launching nuclei scan.\n";
            return;
        }

        char buffer[1024];
        
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::string line(buffer);
            
            if (line.find("CVE") != std::string::npos || line.find("high") != std::string::npos || line.find("critical") != std::string::npos) {
                std::cout << reset << "[" << bg_navy << now_time() << reset << "]" <<  " " << bg_yellow << "[info]" << reset << " " << bg_blue << "[website]" << reset << " " << bg_red << "[VULNERABLE]" << reset << line;

            } else {
                std::cout << reset << "[" << bg_navy <<  now_time() << reset << "]" <<  " " << bg_yellow << "[info]" << reset << " " << bg_blue << "[website]" << reset << " " <<  line; 

            }
        }
        
        pclose(pipe);
    }

    
}