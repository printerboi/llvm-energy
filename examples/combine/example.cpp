#include <cstdint>
#include <iostream>

int mul_by_10(int x) {
    return (x << 3) + (x << 1);  // x*8 + x*2
}

int foo(int a, int b) {
    // Expression with redundant work
    int x = (a * 2) + (b * 2);
    return x;
}

int bar(int a, int b) {
    // Expression with shifts and multiplications
    int y = (a << 1) + (b << 1);
    return y;
}

int baz(int a, int b) {
    // More complex expression
    int z = (a * 4) + (a * 8);
    return z;
}

int main() {
    int a = 3, b = 5;

    int result1 = foo(a, b);
    int result2 = bar(a, b);
    int result3 = baz(a, b);
    int result4 = mul_by_10(a);

    std::cout << "foo: " << result1 << "\n";
    std::cout << "bar: " << result2 << "\n";
    std::cout << "baz: " << result3 << "\n";
    std::cout << "mul: " << result4 << "\n";

    return 0;
}
