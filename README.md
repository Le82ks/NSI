# NSI — Network Security Insight

NSI is a small Linux C++ utility for displaying local IPv4/interface information and entries already present in the system ARP cache.

## Build

Requirements: CMake 3.16+ and a C++17 compiler.

```sh
cmake -S . -B build
cmake --build build
./build/nsi
```

Alternatively, compile directly:

```sh
g++ -std=c++17 -Wall -Wextra -Wpedantic main.cpp logo.cpp port.cpp website.cpp check_website.cpp -o nsi
```

## Scope and safety

This version does not launch `nmap`, `nuclei`, shell commands, port probes, or vulnerability scans. It only reads local interface information and the local ARP cache. ARP cache entries are incomplete, so the displayed device count is not a complete inventory. Vendor identification is a small best-effort OUI hint, not a reliable database.

Use any active security assessment tools only against systems you own or have explicit permission to test.
