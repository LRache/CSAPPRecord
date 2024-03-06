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

// 2.36
bool tmult_ok(int a, int b) {
    int64_t t = a * (int64_t)b;
    return t < INT32_MAX || t > INT32_MIN;
}

// 2.42
int div16(int x) {
    int t = x >> 32;
    return (x+ (t & 0b1111)) >> 4;
}

void test_div16() {
    std::cout << std::boolalpha;
    std::cout << (div16(100) == (100 / 16)) << std::endl;
    std::cout << (div16(-100) == (-100) / 16) << std::endl;
}

int main() {
    test_div16();
    return 0;
}