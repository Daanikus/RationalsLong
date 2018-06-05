#include "Integer.h"
#include <iostream>

using namespace cosc326;

int main() {
    Integer i("5");
    Integer j("7");
    Integer r;
    std::cout << "Tesing with inputs " << i << " and " << j << '\n';
    r = i + j;
    std::cout << "+ " << r << '\n';
    r = i - j;
    std::cout << "- " << r << '\n';
    r = i * j;
    std::cout << "* " << r << '\n';
    r = i / j;
    std::cout << "/ " << r << '\n';
    Integer a("5");
    r += a;
    std::cout << "r + 5 is " << r << '\n';
    
}
