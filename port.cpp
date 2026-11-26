#include "port.hpp"

namespace NSI {
    inline void run_nsi_scan() {
        std::cout << "[" << bg_navy << now_time() << reset <<  "]" << reset << " " << bg_yellow << "[info]" << reset << " " << "The tool has begun executing the commands." << std::endl;
        // start nmap
        FILE* pipe = popen ("nmap --open -sV -sS -F --script vuln 192.168.1.1 2>/dev/null", "r");
        if (!pipe) return;
        
        char buffer[256];
        
        while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
            std::string line(buffer);
            if (line.find("vulners") != std::string::npos &&  line.find("CVE")  !=  std::string::npos) {
                std::cout << "[" << bg_navy << now_time() << reset << "]" << " " << bg_yellow << "[info]" << reset <<  " " << bg_red << "[VULNERABLE]" << " " << reset << red << line << reset;

            } 

            if (line.find("open") != std::string::npos) {
                std::cout << "[" << bg_navy << now_time() << reset << "]" << " " << bg_yellow << "[info]" << reset << " " << bg_green << "[OpenPort]" << reset << " " << line;
            } 
            
        }
        pclose(pipe);
    }
}