# uCTest

uCTest is a lightweight unit testing framework for C. It provides a set of macros that can be used to implement unit test cases with almost zero overhead.

## Features

- Simple and easy-to-use macros for defining test cases and assertions
- Customizable printf function for emitting test messages
- Option to stop test execution after the first error (fail-fast mode) or continue with all test cases
- Detailed test result output, including error detection and test function count

## Getting Started and Execute a Demo

### With G++

```bash
mkdir build
cd build
cmake ..
make
```

### With Clang

```bash
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ ..
make
```

### Activate Sanitizers with:

```bash
mkdir build
cd build
cmake -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DENABLE_SANITIZERS=ON..
make
```

## Demo Code

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
$ cmake ..  -DUSE_PRINTF=ON && make && ./uCTestDemo 
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


## Compiler-specific Options

The provided CMakeLists.txt file includes compiler-specific options for GNU/Clang and Microsoft Visual Studio.

For GNU/Clang compilers, you can enable sanitizers and warning flags by setting the appropriate options in the CMakeLists.txt file.

For Microsoft Visual Studio, warning flags are enabled by default.

Feel free to modify the CMakeLists.txt file according to your specific requirements.

Customizing printf Function

The uCTest framework allows you to customize the printf function used for emitting test messages. By default, the UC_PRINTF_FUNCTION macro is defined as (void)printf. However, you can change it to your own printf function by modifying the CMakeLists.txt file and setting the USE_PRINTF option to ON.

Contributing
Contributions to uCTest are welcome! If you find any issues or have suggestions for improvements, please open an issue or submit a pull request on the GitHub repository.