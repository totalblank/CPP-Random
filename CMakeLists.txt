cmake_minimum_required(VERSION 3.16)
project(CPP_Random LANGUAGES CXX)

set(CMAKE_CXX_STANDARDS 20)
set(CMAKE_CXX_STANDARDS_REQUIRED ON)

include(FetchContent)

# Fetch fmt
FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2   # pick a stable release
)
FetchContent_MakeAvailable(fmt)


# Define library targets
add_library(ADT
    INTERFACE
)
target_include_directories(ADT INTERFACE ${CMAKE_SOURCE_DIR}/include)

# Executables / libs
add_executable(demo src/main.cpp)

# Link the header target so they inherit the include path
target_link_libraries(demo PRIVATE ADT)
target_link_libraries(demo PRIVATE fmt::fmt)
