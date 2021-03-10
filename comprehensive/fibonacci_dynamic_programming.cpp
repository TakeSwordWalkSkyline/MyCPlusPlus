#include "stdio.h"
#include "iostream"

int fibonacci(int n) {
    if (n <= 1) return n;
    int f1 = 0, f2 = 1, fn = 1;
    for (int i = 2; i <= n; i++) {
        fn = f1 + f2;
        f1 = f2;
        f2 = fn;
    }
    return fn;
}

int main() {
    printf("input a integers number:\n");
    int n = 0;
    std::cin >> n;
    printf("%d th fibonacci number is %d\n", n, fibonacci(n));
}
