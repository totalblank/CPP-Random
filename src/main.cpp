#include <fmt/base.h>
#include <fmt/chrono.h>
// #include <ADT/binary_search_tree.hpp>
using namespace std;

int main() {

    auto now = std::chrono::system_clock::now();
    fmt::print("Date and time: {}\n", now);
    fmt::print("Time: {:%H:%M}\n", now);
    return 0;
}
