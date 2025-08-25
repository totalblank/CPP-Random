cmake_minimum_required(VERSION 3.16)
project(CPP_Random LANGUAGES CXX)

set(CMAKE_CXX_STANDARDS 20)
set(CMAKE_CXX_STANDARDS_REQUIRED ON)

# Define library targets
# add_library(mathlib SHARED src/mathlib.cpp)
# target_include_directories(mathlib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Define an executable target
add_executable(cpp_random src/main.cpp)

# Link the library into the executable
#target_link_libraries(cpp_random PRIVATE mathlib)
