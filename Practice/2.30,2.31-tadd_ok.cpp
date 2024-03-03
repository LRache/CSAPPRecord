bool tadd_ok(int x, int y) {
    int sum = x + y;
    return !((x < 0 && y < 0 && sum > 0) || (x > 0 && y > 0 && sum < 0));
}

bool buggy_tadd_ok(int x, int y) {
    int sum = x + y;
    return (sum-x == y) && (sum - y == x); 
}