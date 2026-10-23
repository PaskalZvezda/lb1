#include "lib.h"

#include "version.h"

int version_major() {
    return PROJECT_VERSION_MAJOR;
}

int version_minor() {
    return PROJECT_VERSION_MINOR;
}

int version_patch() {
    return PROJECT_VERSION_PATCH;
}

std::string version() {
    return std::to_string(version_major()) + "." +
           std::to_string(version_minor()) + "." +
           std::to_string(version_patch());
}
