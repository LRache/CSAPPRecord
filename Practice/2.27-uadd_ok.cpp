#include <iostream>

bool uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return x <= sum;
}

int main() {
    std::cout << sizeof(unsigned);
}