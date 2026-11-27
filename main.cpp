#include "main.hpp"

int main() {
    logo();
    NSI::run_nsi_scan();
    NSI::scan_website();
    NSI::check_website();
    return 0;
}
