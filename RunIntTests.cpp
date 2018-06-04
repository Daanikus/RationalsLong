#include <iostream>
#include <sstream>
#include "Integer.h"

using namespace cosc326;

/**
 * This tests the given Integer against a string representation of it. We also include some additional information to
 * assist with debugging.
 *
 * NOTE: this requries the stream operators to be defined for this test to work.
 *
 * @param i The integer to test
 * @param val The expected value
 * @param op The operation being performed, or some tag to help identify which test
 * @param fn The function where the test was being performed
 * @return true if the integer is the same as the expected value
 */
bool checkVal(const Integer &i, std::string val, std::string op, std::string fn) {

    std::stringstream sstr;
    sstr << i;

    std::string str;
    sstr >> str;

    if (str != val) {
        std::cerr << "ERR: " << fn << " " << op << " have '" << str << "', expect '" << val << "'" << std::endl;
        return false;
    }
    return true;
}


/**
 *
 * This tests the given Integer against another Integer instance. We also include some additional information to
 * assist with debugging.
 *
 * NOTE: this requries the != operator to be defined for this test to work.
 *
 * @param i The integer to test
 * @param val The expected value
 * @param op The operation being performed, or some tag to help identify which test
 * @param fn The function where the test was being performed
 * @return true if the integer is the same as the expected value
 */
bool checkVal(const Integer &i, const Integer &j, std::string op, std::string fn) {
    if (i != j) {
        std::cerr << "ERR: " << fn << " " << op << " have '" << i << "', expect '" << j << "'" << std::endl;
        return false;
    }
    return true;
}

/**
 * These tests use the streaming operators to check for equality.
 *
 * @return true if all these tests pass
 */
bool simpleTestsInteger(){

    bool success = true;

    Integer zero = Integer("0");
    Integer zero_default = Integer();
    Integer zero_copy = Integer(zero);
    Integer one = Integer("1");
    Integer one_copy = Integer(one);

    Integer negative_one = Integer("-1");
    Integer negative_one_copy = Integer(negative_one);
    Integer negative_one_unary = Integer(-one);


    /*
     * Some of you may not have seen the __func__ thing before. It's a macro that gets replaced with the name of
     * the current function. In this function it'll be the string "simpleTestsInteger".
     */

    success &= checkVal(zero, zero_default, "str-constructor2", __func__);
    success &= checkVal(zero_copy, zero_default, "copy-constructor2", __func__);

    success &= checkVal(one_copy, one,  "str-constructor2", __func__);
    success &= checkVal(negative_one, -one,  "unary-", __func__);
    success &= checkVal(+negative_one, one,  "unary+", __func__);
    success &= checkVal(negative_one_unary, -one,  "copy unary-", __func__);

    return success;
}

/**
 * These tests use the streaming operators to check for equality.
 *
 * @return true if all these tests pass
 */
bool simpleTestsStream(){
    bool success = true;

    Integer zero = Integer("0");
    Integer zero_default = Integer();
    Integer zero_copy = Integer(zero);

    Integer one = Integer("1");
    Integer one_copy = Integer(one);

    Integer negative_one = Integer("-1");
    Integer negative_one_copy = Integer(negative_one);
    Integer negative_one_unary = Integer(-one);


    success &= checkVal(zero, "0", "str-constuctor", __func__);
    success &= checkVal(zero_default, "0", "default-constructor", __func__);
    success &= checkVal(zero_copy, "0", "copy-constructor", __func__);

    success &= checkVal(one, "1", "str-constructor", __func__);
    success &= checkVal(one_copy, "1", "copy-constructor", __func__);

    success &= checkVal(negative_one, "-1", "str-constructor", __func__);
    success &= checkVal(+negative_one, "1", "unary+", __func__);
    success &= checkVal(negative_one_unary, "-1", "copy-constructor", __func__);

    return success;
}


/**
 * These tests use the streaming operators to check for equality.
 * This tests the numerical operators and NOT compound operators.
 *
 *
 * @return true if all the tests pass
 */
bool numericalTests(){
    bool success = true;

    Integer one = Integer("1");

    Integer two = one + one;
    success &= checkVal(two, "2",  "add", __func__);

    Integer zero = one + -one;
    success &= checkVal(zero, "0",  "add-negative", __func__);

    Integer three = one + two;
    success &= checkVal(three, "3",  "add", __func__);
    success &= checkVal(three - one, "2",  "subtract", __func__);
    success &= checkVal(three * two, "6",  "times", __func__);
    success &= checkVal((three * two)/two, "3",  "divide", __func__);

    success &= checkVal(one + zero, "1",  "add", __func__);
    success &= checkVal(three + zero, "3",  "add", __func__);
    success &= checkVal(three - one + zero , "2",  "subtract-add", __func__);
    success &= checkVal(three * two + zero, "6",  "multiplication", __func__);
    success &= checkVal((three * two)/two + zero, "3",  "divide", __func__);

    success &= checkVal(one - zero, "1",  "subtract", __func__);
    success &= checkVal(three - zero, "3",  "subtract", __func__);
    success &= checkVal(three - one - zero , "2",  "subtract-multi", __func__);
    success &= checkVal(three * two - zero, "6",  "multiplication", __func__);
    success &= checkVal((three * two)/two - zero, "3",  "multiplication-divide-subtract", __func__);

    success &= checkVal(one * zero, "0",  "multiplication", __func__);
    success &= checkVal(three * zero, "0",  "multiplication", __func__);
    success &= checkVal(three - one * zero , "3",  "subtraction-multiplication", __func__);
    success &= checkVal(three * two * zero, "0",  "multiplication-multiplication", __func__);
    success &= checkVal((three * two)/two * zero, "0",  "multiplication-divide-multiplication", __func__);

    // I'm not going to divide by zero

    return success;
}

/**
 * These tests use the streaming operators to check for equality.
 * This tests the compound numerical operators.
 *
 * @return true if all the tests pass.
 */
bool assignmentTests(){
    bool success = true;

    Integer one = Integer("1");

    // at this point, two is actually one, so we can add one to it as our first test ;)
    Integer two = Integer(one);
    Integer four, five;

    two += one;
    success &= checkVal(two, "2",  "assign-plus", __func__);

    two -= one;
    success &= checkVal(two, "1",  "assign-minus", __func__);

    two *= one;
    success &= checkVal(two, "1",  "assign-times", __func__);

    two /= one;
    success &= checkVal(two, "1",  "asign-divide", __func__);

    // reset our integers
    one = Integer("1");
    two = Integer("2");

    // start performing the checks
    four = Integer("4");
    four += one;
    success &= checkVal(four, "5",  "assign-plus", __func__);

    four = Integer("4");
    four *= two;
    success &= checkVal(four, "8",  "assign-times", __func__);

    four = Integer("4");
    four /= two;
    success &= checkVal(four, "2",  "assign_divide", __func__);

    four = Integer("4");
    four %= two;
    success &= checkVal(four, "0",  "assign-mod", __func__);

    five = Integer("5");
    five %= two;
    success &= checkVal(five, "1",  "assign-mod", __func__);

    return success;
}

/**
 *
 * Checks the logical operators. Note that I'm not using the checkVal function here.
 *
 * @return true if all the tests pass
 */
bool logicTests(){
    bool success = true;

    Integer one = Integer("1");
    Integer two = Integer("2");
    Integer two_copy = Integer(two);

    success &= one < two;
    success &= one <= two;
    success &= !(one > two);
    success &= !(one >= two);
    success &= !(one == two);
    success &= one != two;

    success &= !(two_copy < two);
    success &= two_copy <= two;
    success &= !(two_copy > two);
    success &= two_copy >= two;
    success &= two_copy == two;
    success &= !(two_copy != two);

    return success;
}


/**
 *
 * Checks large numerical operations
 *
 * @return true if all the tests pass
 */
bool largeNumericTests(){

#warning "largeTests unimplemented"

    return false;
}


/**
 * This runs the test and displays the name of the test and wether it passed or failed.
 *
 * @param func The name of the function that performs the tests
 * @param name The name of the test
 * @return true if fn returns true
 */
bool runTest(bool (*func)(), std::string name){

    bool result = (*func)();

    std::cout << name << "\t\t\t";
    if(result){
        std::cout << "[PASS]";
    }else{
        std::cout << "[FAIL]";
    }
    std::cout << std::endl;

    return result;
}

/**
 *
 * The main function. Add any more additional functions etc. here.
 *
 */
int main(void){

    bool success = true;

    // the first argument is the *name* of the function to call above
    success &= runTest(simpleTestsStream,   "Simple Tests (stream)");
    success &= runTest(simpleTestsInteger,  "Simple Tests (int)   ");
    success &= runTest(numericalTests,      "Numerical Tests      ");
    success &= runTest(assignmentTests,     "Assignment Tests     ");
    success &= runTest(logicTests,          "Logic Tests          ");
    success &= runTest(largeNumericTests,   "Large Numerical Tests");

    if(success){
        std::cout << "All tests pass!" << std::endl;
    }

    return EXIT_SUCCESS;
}

