#include "check_website.hpp"

#include <iostream>

#include "color.hpp"

namespace NSI {
void check_website() {
    std::cout << blue << "[info] Automated vulnerability checks are disabled in this build."
              << reset << '\n';
}
}  // namespace NSI
