#include "lib.h"

#include <iostream>

static int failures = 0;

static void check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAILED: " << message << std::endl;
        ++failures;
    }
}

int main() {
    check(version_major() == 1, "major version must be 1");
    check(version_minor() == 0, "minor version must be 0");
    check(version_patch() > 0, "patch version must be positive");
    check(version() == "1.0." + std::to_string(version_patch()),
          "version string must have format 1.0.N");

    if (failures == 0) {
        std::cout << "All tests passed, version " << version() << std::endl;
    }
    return failures == 0 ? 0 : 1;
}
