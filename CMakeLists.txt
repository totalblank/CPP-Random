cmake_minimum_required(VERSION 3.16)
project(CPP_Random LANGUAGES CXX)

set(CMAKE_CXX_STANDARDS 20)
set(CMAKE_CXX_STANDARDS_REQUIRED ON)

# Define library targets
add_library(ADT
    INTERFACE
)
target_include_directories(ADT INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Executables / libs
add_executable(demo src/main.cpp)

# Link the header target so they inherit the include path
target_link_libraries(demo PRIVATE ADT)
