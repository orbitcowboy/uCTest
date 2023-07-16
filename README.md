# uCTest

uCTest is a lightweight unit testing framework for C. It provides a set of macros that can be used to implement unit test cases with almost zero overhead.

## Features

- Simple and easy-to-use macros for defining test cases and assertions
- Customizable printf function for emitting test messages
- Option to stop test execution after the first error (fail-fast mode) or continue with all test cases
- Detailed test result output, including error detection and test function count

## Getting Started

### Add to your CMake project

Via [`CPM`](https://github.com/cpm-cmake/CPM.cmake):

```cmake
# Add
CPMAddPackage("gh:orbitcowboy/uCTest#master")

# Use
add_executable(my_test_executable test.cpp)
target_link_libraries(my_test_executable PRIVATE orbitcowboy::uCTest)
```

Via FetchContent:

```cmake
# Add
include(FetchContent)
FetchContent_Declare(uCTest GIT_REPOSITORY https://github.com/orbitcowboy/uCTest.git GIT_TAG master)
FetchContent_MakeAvailable(uCTest)

# Use
add_executable(my_test_executable test.cpp)
target_link_libraries(my_test_executable PRIVATE orbitcowboy::uCTest)
```

Via git submodules:

```bash
git submodule add https://github.com/orbitcowboy/uCTest.git
```

```cmake
# Add
add_subdirectory(uCTest)

# Use
add_executable(my_test_executable test.cpp)
target_link_libraries(my_test_executable PRIVATE uCTest)
```

### Demo Code

Here's an example of how to use uCTest in your code:

```c
#include "uCTest.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

// Define your test cases using the provided macros
static bool TestCase1(void)
{
    UC_ASSERT_MSG("TestCase1: Detailed information ...", /*result=*/true);
    return true;
}

static bool TestCase2(void)
{
    UC_ASSERT_MSG("TestCase2: Detailed information ...", /*result=*/false);
    return true;
}

// This global counter tracks the number of executed test functions.
uint32_t g_testFunctionCount = 0U;
bool g_errorDetected = false;

// The purpose of this function is to register test cases that will be executed.
static bool RunTests(void)
{
    EXECUTE_TEST_CASE(TestCase1);
    EXECUTE_TEST_CASE(TestCase2);
    // Register more test cases
    return true;
}

int main(void)
{
    // Execute all unit test cases.
    if (RunTests() && NO_ERROR_DETECTED)
    {
        printf("All test cases successfully passed.\n");
    }
    else
    {
        printf("Error detected.\n");
    }
    // Provide the number of executed functions as additional information.
    printf("Executed %" PRIu32 " test functions.\n", g_testFunctionCount);

    return 0;
}
```

### Demo output

```bash
$ mkdir build && cd build && cmake .. -DUSE_PRINTF=ON && make && ./uCTestDemo 
-- Configuring done
-- Generating done
-- Build files have been written to: uCTest/build
[100%] Built target uCTestDemo
TestCase2: Detailed information ... [OK]
TestCase1       [OK]
TestCase2: Detailed information ... [NOK]
TestCase2       [OK]
Error detected.
Executed 2 test functions.
```

## API Reference

### Global variables

These variables should be set globally in your test suite:

```c
// A global counter, which counts the number of executed test cases.
uint32_t g_testFunctionCount = 0U;
// A global variable, which indicates that an error is detected. 
bool g_errorDetected = false;
```

### Macros

#### `EXECUTE_TEST_CASE(UNIT_TEST_FUNCTION)`

This macro supposed to be used within the function `RunTests()`. It accepts the function name of the unit test function to be executed. In case an error is detected within the executed unit test, the macro returns Boolean false. Otherwise it proceeds and the next test case can be started.

- `UNIT_TEST_FUNCTION` - The function name of the unit test function

#### `NO_ERROR_DETECTED`

This macro can be used to verify, if errors where detected during executing some test cases. This only makes sense in combination with `UC_FAIL_FAST` set. Because, in case `UC_FAIL_FAST` is set, the test execution stops directly after detecting the first error.

#### `UC_ASSERT_MSG(MESSAGE, TEST_RESULT)`

This macro is used to emit a message and its result.

- `MESSAGE` - The message to be printed in case the test case fails
- `TEST_RESULT` - In case the test result is true, [OK] is printed

In case the test case is false, [NOK] is printed.

### CMake Options

These flags can be enabled or disabled to change the behaviour of parts of the uCTest build.

These options would normally be configured by either:

- Supplying an option in the form `-DNAME_OF_OPTION=ON/OFF` to the initial CMake configuration call, or
- Calling `set(NAME_OF_OPTION ON/OFF)` before including uCTest in your project via `add_subdirectory`

#### `ENABLE_SANITIZERS(default=OFF)`

Enable [Memory Sanitizer](https://clang.llvm.org/docs/MemorySanitizer.html). Works only with gcc & clang on Unix.

#### `UC_FAIL_FAST(default=OFF)`

In case this option is set to `ON`, the execution of the test cases is stopped directly after the first error is detected. In case it is set to `OFF`, the execution is proceeded until all test cases are executed.

#### `USE_PRINTF(default=ON)`

Use `printf()` function to print test execution log.

#### `BUILD_DEMO(default=OFF)`

Build the demo project.

## Working on this project locally

### Configure, build & execute example

```bash
cmake --workflow --preset full
```

### With G++

```bash
cmake --preset default
cmake --build --preset default
ctest --preset default
```

### With Clang

```bash
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ --preset default
cmake --build --preset default
ctest --preset default
```

### Activate Sanitizers

```bash
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DENABLE_SANITIZERS=ON --preset default
cmake --build --preset default
ctest --preset default
```
