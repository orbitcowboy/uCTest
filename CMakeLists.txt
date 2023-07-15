cmake_minimum_required(VERSION 3.0)
project(uCTest)

# Set the C++ standard to C++11 (or higher if needed)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add include directory
include_directories(include)

# Add source files
set(SOURCES
    src/uCTestDemo.c
)

# Create an executable from the source files
add_executable(uCTestDemo ${SOURCES})

# Compiler-specific options
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    # Enable sanitizers
    option(ENABLE_SANITIZERS "Enable sanitizers" OFF)
    if(ENABLE_SANITIZERS)
        set(SANITIZER_FLAGS "-fsanitize=address,undefined")
        set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${SANITIZER_FLAGS}")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZER_FLAGS}")
    endif()

    # Enable all warning flags
    set(WARNING_FLAGS "-Wall -Wextra -Wpedantic")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")

    # Define USE_PRINTF option
    option(USE_PRINTF "Use printf function" OFF)
    if(USE_PRINTF)
        add_definitions("-DUSE_PRINTF")
    endif()    
endif()

# Microsoft Visual Studio-specific options
if(MSVC)
    # Enable all warning flags
    set(WARNING_FLAGS "/W4")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WARNING_FLAGS}")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WARNING_FLAGS}")
endif()
