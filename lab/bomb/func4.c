#include <stdio.h>

int disa_func4(int arg1, int arg2, int arg3) {
    // rdi: arg1
    // rsi: arg2
    // rdx: arg3
    int v0 = (arg3 - arg2) / 2; // rax
    int v1 = v0 + arg2; // rcx
    if (v1 >= arg1) {
        if (v1 >= arg1) return 0;
        else return disa_func4(arg1, v1+1, arg3) * 2 + 1;
    } else {
        arg3 = v1 - 1;
        return disa_func4(arg1, arg2, arg3) * 2;
    }
}

int func4(int a, int b, int c) {
    int e = (b + c) / 2;
    if (a == e) return 0;
    else if (a <= e) return func4(a, e+1, c) * 2 + 1;
    else return func4(a, b, e-1) * 2;
}

int main() {
    int input1; // [rsp+8]
    int input2; // [rsp+12]
    scanf("%d %d", &input1, &input2);
    func4(input1, 0, 14);
    return 0;
}