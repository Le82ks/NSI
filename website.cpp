#include "website.hpp"

#include <iostream>

#include "color.hpp"

namespace NSI {
void scan_website() {
    std::cout << blue << "[info] No website or port probe was performed. "
              << "Configure an authorized assessment workflow separately."
              << reset << '\n';
}
}  // namespace NSI
