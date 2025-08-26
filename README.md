In CMake, a target is just a buildable unit (executable, static lib, shared lib, or interface lib).
An INTERFACE library:

- Doesn’t produce an actual .a/.so/.exe.
- Exists only to carry usage requirements (include paths, compiler options, macros).
- Any target that links it automatically inherits those requirements.


So here, your header-only ADTs live in include/, and the INTERFACE target adt_headers tells CMake
“everything that uses me should also add ${CMAKE_SOURCE_DIR}/include to its include search paths.”

---

🔹Project layout

myproj/
├─ CMakeLists.txt
├─ include/
│  └─ ADT/
│     └─ binary_search_tree.hpp
└─ src/
   ├─ main.cpp
   └─ other.cpp

---

🔹 `CMakeLists.txt` explained

cmake_minimum_required(VERSION 3.16)
project(myproj LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# (1) Define the INTERFACE target
add_library(adt_headers INTERFACE)

# (2) Tell CMake what this target provides
target_include_directories(adt_headers INTERFACE
  ${CMAKE_SOURCE_DIR}/include
)

# (3) Define your executables
add_executable(app src/main.cpp)
add_executable(other src/other.cpp)

# (4) Link them against adt_headers
target_link_libraries(app   PRIVATE adt_headers)
target_link_libraries(other PRIVATE adt_headers)

---

🔸 Step (1) → add_library(adt_headers INTERFACE)

Creates a “dummy” library target called adt_headers. It won’t build to a .so or .a, but you can attach include paths, compile features, etc. to it.

🔸 Step (2) → target_include_directories(... INTERFACE …)

Says:

Any target that links to adt_headers should have ${CMAKE_SOURCE_DIR}/include added to its include path.

So clang/g++/clangd will know to look in include/ whenever you write #include <ADT/...>.


🔸 Step (3) → add_executable(app …)

Defines actual binaries (app, other) that will consume your ADTs.

🔸 Step (4) → target_link_libraries(app PRIVATE adt_headers)

Links app against the header-only target, which means:

app now sees all headers inside include/.

clangd sees that path in compile_commands.json.

If you later add compile flags or macros to adt_headers, app gets them automatically.



---

🔹 4. In practice

src/main.cpp

#include <ADT/binary_search_tree.hpp>
int main() {
    ADT::BinarySearchTree<int> t;
}

Build:

cmake -S . -B build -G Ninja -DCMAKE_EXPORT_COMPILE_COMMANDS=ON
cmake --build build

For clangd:

ln -sf build/compile_commands.json .

→ Open Neovim, clangd now resolves <ADT/binary_search_tree.hpp> anywhere.


---

🔹 5. Why is this better than include_directories()?

Target-scoped: Only the targets that link adt_headers get the headers.

Explicit dependencies: You can see exactly what each target needs.

Composability: If later you add another header lib (graph_headers), you just link both.

clangd works perfectly because everything flows into compile_commands.json.



---

✅ In short:

- Put headers in include/.

- Make an INTERFACE target that carries the include path.

- Link it wherever you need headers.

- clangd + CMake take care of the rest.

