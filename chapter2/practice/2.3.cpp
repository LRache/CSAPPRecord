#include <iostream>
#include <limits.h>

bool uadd_ok(unsigned x, unsigned y) {
    unsigned sum = x + y;
    return x <= sum;
}

// 2.30
bool tadd_ok(int x, int y) {
    int sum = x + y;
    return !((x < 0 && y < 0 && sum > 0) || (x > 0 && y > 0 && sum < 0));
}

// 2.31
bool buggy_tadd_ok(int x, int y) {
    int sum = x + y;
    return (sum-x == y) && (sum - y == x); 
}

void test_tadd_ok() {
    int x = INT32_MAX;
    int y = 1;
    std::cout << std::boolalpha;
    std::cout << tadd_ok(x, y) << std::endl;
    std::cout << buggy_tadd_ok(x, y) << std::endl;
}

// 2.32
bool tsub_ok(int x, int y) {
    if (y == INT_MIN) return false;
    return tadd_ok(x, -y);
}

bool buggy_tsub_ok(int x, int y) {
    return tadd_ok(x, -y);
}

void test_tsub_ok() {
    int x = 1;
    int y = INT_MIN;
    std::cout << std::boolalpha;
    std::cout << tsub_ok(x, y) << std::endl;
    std::cout << buggy_tsub_ok(x, y) << std::endl;
}

int main() {
    test_tsub_ok();
    return 0;
}