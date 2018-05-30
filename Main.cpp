#include "Integer.h"
#include <iostream>

using namespace cosc326;

int main() {
    Integer i("5");
    Integer j("7");
    Integer r;
    r = i + j;
    std::cout << r.getValue();

}
