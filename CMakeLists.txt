cmake_minimum_required(VERSION 3.00)
project(product_management)

set(CMAKE_CXX_STANDARD 14)  # Jika C++17 tidak berfungsi, coba gunakan C++14
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(include)

set(CMAKE_TOOLCHAIN_FILE "C:/Users/LENOVO/vcpkg/scripts/buildsystems/vcpkg.cmake")

add_definitions(-D_WIN32_WINNT=0x0A00)

add_compile_options("/utf-8")

add_executable(product_management
    main.cpp
    src/product_controller.cpp
    src/product_model.cpp
)