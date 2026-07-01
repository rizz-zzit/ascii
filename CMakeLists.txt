# 1. Set the minimum version of CMake required
cmake_minimum_required(VERSION 3.10)

# 2. Name your project
project(TerminalImageRenderer)

# 3. Require modern C++ standard (C++11 or newer for std::max)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 4. Find the OpenCV library on your system
find_package(OpenCV REQUIRED)

# 5. Tell CMake where your header files live (the current directory)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# 6. Define your executable and list all source files (.cpp only, no .h files here)
# UPDATED: Added asciiConverter.cpp to the compilation pool
add_executable(image_app main.cpp image.cpp asciiConverter.cpp)

# 7. Link your executable with the OpenCV binary libraries
target_link_libraries(image_app ${OpenCV_LIBS})
