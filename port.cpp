#include "port.hpp"

#include <iostream>

#include "color.hpp"

namespace NSI {
void run_nsi_scan() {
    std::cout << yellow << "[info] Active port scanning is intentionally disabled. "
              << "Only scan systems you own or are explicitly authorized to test."
              << reset << '\n';
}
}  // namespace NSI
