#include "Integer.h"
#include <iostream>

using namespace cosc326;

int main() {
    Integer i("-5");
    Integer j("7");
    Integer r;
    r = i + j;
    std::cout << r  << '\n';
    r = i - j;
    std::cout << "- Should be -12: " << r.getIntegerAsString() << '\n';
    r = i * j;
    std::cout << "* Should be -35: " << r.getIntegerAsString() << '\n';
    r = i / j;
    std::cout << "/ Should be ~0.71429: " << r.getIntegerAsString() << '\n';
    r = i - j;

}
