cmake_minimum_required(VERSION 3.14)

if(NOT DEFINED PATCH_VERSION)
    execute_process(
        COMMAND git ls-remote --tags --refs --sort=-v:refname origin "v1.0.*"
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        OUTPUT_VARIABLE RELEASE_TAGS)
    string(REGEX MATCH "v1\\.0\\.([0-9]+)" RELEASE_TAG "${RELEASE_TAGS}")
    set(PATCH_VERSION ${CMAKE_MATCH_1})
endif()
set(PROJECT_VERSION_FULL 1.0.${PATCH_VERSION})

project(helloworld VERSION ${PROJECT_VERSION_FULL} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

configure_file(version.h.in version.h)

add_library(helloworld lib.cpp)
target_include_directories(helloworld PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_include_directories(helloworld PRIVATE "${CMAKE_CURRENT_BINARY_DIR}")

add_executable(helloworld_cli main.cpp)
target_link_libraries(helloworld_cli PRIVATE helloworld)

add_executable(test_version test_version.cpp)
target_link_libraries(test_version PRIVATE helloworld)

foreach(target helloworld helloworld_cli test_version)
    if(MSVC)
        target_compile_options(${target} PRIVATE /W4 /WX /utf-8)
    else()
        target_compile_options(${target} PRIVATE -Wall -Wextra -pedantic -Werror)
    endif()
endforeach()

enable_testing()
add_test(NAME test_version COMMAND test_version)

install(TARGETS helloworld_cli RUNTIME DESTINATION bin)

if(WIN32)
    set(CPACK_GENERATOR ZIP)
else()
    set(CPACK_GENERATOR DEB)
endif()
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT "irb259@gmail.com")

include(CPack)
