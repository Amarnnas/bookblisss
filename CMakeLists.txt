cmake_minimum_required(VERSION 3.10)
project(SalesManagementSystem)

# Set C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the executable
add_executable(sales_system main.cpp)

# For Windows, you might want to add console subsystem
if(WIN32)
    set_target_properties(sales_system PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
endif()

# Add compile options for better compatibility
if(MSVC)
    target_compile_options(sales_system PRIVATE /W4)
else()
    target_compile_options(sales_system PRIVATE -Wall -Wextra -Wpedantic)
endif()

# Set output directory
set_target_properties(sales_system PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)