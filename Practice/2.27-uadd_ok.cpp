#include <iostream>

bool uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return x <= sum;
}

bool tadd_ok(int x, int y) {
    int sum = x + y;
    return !((x < 0 && y < 0 && sum > 0) || (x > 0 && y > 0 && sum < 0));
}

int main() {
    std::cout << sizeof(unsigned);
}