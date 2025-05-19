cmake_minimum_required(VERSION 3.15)
project(MFT)

set(CMAKE_CXX_STANDARD 17)

# Add vcpkg dependencies
find_package(cpr CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

include_directories(include)

add_executable(MFT
    src/main.cpp
    src/angel_api.cpp
    src/strategy.cpp
    src/indicators.cpp
)

target_link_libraries(MFT
    cpr::cpr
    nlohmann_json::nlohmann_json
)
