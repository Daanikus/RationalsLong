#include "Integer.h"
#include <iostream>
#include "Rational.h"
using namespace cosc326;

int main() {
    /*Integer i("15");
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
    Integer n("15");
    Integer m("30");
    Rational mn(n, m);
    std::cout << rat << '\n';
    std::cout << mn;*/
    /*Integer an("-4");
    Integer ad("5");
    Integer bn("1");
    Integer bd("8");
    Rational p(an, ad);
    Rational q(bn, bd);
    Rational r;
    std::cout << "Testing with " << p << " and " << q << '\n';
    r = p + q;
    std::cout << "+ : " << r << '\n';
    r = p - q;
    std::cout << "- : " << r << '\n';
    r = p * q;
    std::cout << "* : " << r << '\n';
    r = p / q;
    std::cout << "/ : " << r << '\n';*/
    //Rational r("5622.1/34");
    Integer pos("1");
    Integer neg("-1");
    pos += neg;
    std::cout << pos << '\n';
    Rational one("1");
    Rational two = one + -one;
    Rational negone(pos, neg);
    std::cout << negone << '\n';
    std::cout << two;
}
