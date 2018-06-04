#include "Integer.h"
#include <iostream>
#include "Rational.h"
using namespace cosc326;

int main() {
    Integer i("15");
    Integer j("20");
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
    Integer a("-16");
    r += a;
    std::cout << "r + 5 is " << r << '\n';
    r = gcd(i, j);
    std::cout << "GCD: " << r << '\n';
    Rational rat(a, r);
    std::cout << rat;
}
