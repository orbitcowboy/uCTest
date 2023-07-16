/*!
* \file uCTest.h
* \brief This header file contains a set of macros that can be used for
*  building a uCTest-suite.
*
* \author Dr. Martin Ettl
*/

/** \addtogroup uCTest uCTest
*  @{
*/

#ifndef UC_TEST_H_INCLUDED
#define UC_TEST_H_INCLUDED

#include <stdbool.h>
#include <inttypes.h>

#ifdef __cplusplus
extern "C" {
#endif

/** \brief The macros within this testsuite use this replacement for printf.
In order to adapt a customized printf function, just change the right side of this
preprocessor define.*/
#if USE_PRINTF
#define UC_PRINTF_FUNCTION (void)printf
#else
#define UC_PRINTF_FUNCTION(...)
#endif

/** \brief In case this macro is set to true, the execution of the test cases is stopped
directly after the first error is detected. In case it is set to false, the execution
is proceeded until all test cases are executed. */
#if UC_FAIL_FAST
#define _UC_FAIL_FAST true
#else
#define _UC_FAIL_FAST false
#endif

/** \brief This helper macro is needed to concatenate strings during the
* preprocessor is running.
*
* @param[in] STRING1 The string at the left side.
* @param[in] STRING2 The string at the right side.
*/
#define CONCAT_STRINGS(STRING1, STRING2) (STRING1 " " STRING2)

/** \brief This macro is used to emit a message and its result.
*
* @param[in] MESSAGE The message to be printed in case the test case fails.
* @param[in] TEST_RESULT In case the test result is true, [OK] is printed.
*            In case the test case is false, [NOK] is printed.
*/
#define UC_ASSERT_MSG(MESSAGE, TEST_RESULT)\
    do {\
        UC_PRINTF_FUNCTION(MESSAGE);\
        if((TEST_RESULT))\
        {\
            UC_PRINTF_FUNCTION(" [OK]\r\n");\
        }\
        else\
        {\
            UC_PRINTF_FUNCTION(" [NOK]\r\n");\
            g_errorDetected = true;\
            if(_UC_FAIL_FAST)\
            {\
                return !g_errorDetected;\
            }\
        }\
    } while(0)


/** \brief This macro is used within the function RunTests(). It accepts
* the function name of the unit test function to be executed.
* In case an error is detected within the executed unit test, the macro returns
* Boolean false. Otherwise it proceeds and the next test case can be started.
*
* @param[in] UNIT_TEST_FUNCTION The function name of the unit test function.
*/
#define EXECUTE_TEST_CASE(UNIT_TEST_FUNCTION)\
    do {\
        ++g_testFunctionCount;\
        if(!(UNIT_TEST_FUNCTION)())\
        {\
            UC_PRINTF_FUNCTION((#UNIT_TEST_FUNCTION));\
            UC_PRINTF_FUNCTION("\t[NOK]\r\n");\
            return false;\
        }\
        UC_PRINTF_FUNCTION((#UNIT_TEST_FUNCTION));\
        UC_PRINTF_FUNCTION("\t[OK]\r\n");\
    } while(0)

/** \brief This macro can be used to verify, if errors where detected during
executing some test cases. This only makes sense in combination with MMT_STOP_ON_ERROR = false set.
Because, in case MMT_STOP_ON_ERROR = true is set, the test execution stops directly after
detecting the first error. */
#define NO_ERROR_DETECTED (!g_errorDetected)

/** \brief A global counter, which counts the number of executed test cases. */
extern uint32_t g_testFunctionCount;
/** \brief A global variable, which indicates that an error is detected. */
extern bool g_errorDetected;

#ifdef __cplusplus
}
#endif

#endif /* UC_TEST_H_INCLUDED */

/** @}*/

