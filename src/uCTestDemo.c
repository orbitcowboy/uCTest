/*!
* \brief This file demonstrates how the test suite can be used.
*
* \author Dr. Martin Ettl
*/

#include "uCTest.h"

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

/* Functions and modules to be tested have to be included here:*/
/* For example: \c "#include" "MyModule.h" */

static bool TestCase1(void)
{
    UC_ASSERT_MSG("TestCase2: Detailed information ...", /*result=*/true);
    return true;
}

static bool TestCase2(void)
{
    UC_ASSERT_MSG("TestCase2: Detailed information ...", /*result=*/false);
    return true;
}

/* This global counter tracks the number of executed test functions.*/
uint32_t g_testFunctionCount = 0U;
bool g_errorDetected = false;

/* The purpose of this function is to register test cases that will be
 * executed. */
static bool RunTests(void)
{
    EXECUTE_TEST_CASE(TestCase1);
    EXECUTE_TEST_CASE(TestCase2);
    /* Register more test cases */
    return true;
}

int main(void)
{
    /* Execute all unit test cases. */
    if(RunTests() && NO_ERROR_DETECTED)
    {
        (void)printf("All test cases successfully passed.\n");
    }
    else
    {
        (void)printf("Error detected.\n");
    }
    /* Provide the number of executed functions as additional information. */
    (void)printf("Executed %" PRIu32" test functions.\n", g_testFunctionCount);

    return 0;
}
