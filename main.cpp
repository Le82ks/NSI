#include "main.hpp"
using namespace std;
int main() {
                   // Start
    logo();        // logo () >>
                   // information >> IP >> MAC >> vendor >> status >> ADC .....
    {
        std::cout << "" << std::endl;

        std::cout << "[" << bg_navy << now_time() << reset <<  "]" << reset << " " << bg_yellow << "[info]" << reset << " " << "The examination might take some time... " << std::endl;
        this_thread::sleep_for(std::chrono::milliseconds(800));      /// milliseconds 0.8
        
        NSI::run_nsi_scan();
        NSI::scan_website();
        NSI::check_website();
        

    return 0;
    }
}