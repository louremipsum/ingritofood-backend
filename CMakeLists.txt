cmake_minimum_required(VERSION 3.15)
project(backend VERSION 0.1.0)


INCLUDE_DIRECTORIES(
    C:/src/vcpkg/installed/x64-windows/include
)

LINK_DIRECTORIES(
    C:/src/vcpkg/installed/x64-windows/lib
)
include_directories(backend PRIVATE .)

find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)


add_executable(backend  server.cpp http_tcpServer.cpp)


target_link_libraries(backend PRIVATE nlohmann_json::nlohmann_json wsock32 ws2_32)

# target_link_libraries(backend PRIVATE nlohmann_json::nlohmann_json)
target_link_libraries(backend PRIVATE cpr::cpr)

