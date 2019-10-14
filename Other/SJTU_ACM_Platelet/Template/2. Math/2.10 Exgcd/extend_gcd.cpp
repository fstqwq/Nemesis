// return gcd(a, b)
// ax+by=gcd(a,b)
template <typename T>
T extend_gcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    T res = extend_gcd(b, a % b, x, y);
    T t = y;
    y = x - a / b * y;
    x = t;
    return res;
}

// return minimal positive integer x so that ax+by=c
// or -1 if such x does not exist
template <typename T>
inline T solve_equ(T a, T b, T c) {
    T x, y, d;
    d = extend_gcd(a, b, x, y);
    if (c % d)
        return -1;
    T t = c / d;
    x *= t;
    y *= t;
    T k = b / d;
    x = (x % k + k) % k;
    return x;
}
// return minimal positive integer x so that ax==b(mod p)
// or -1 if such x does not exist
template <typename T>
inline T solve(T a, T b, T p) {
    a = (a % p + p) % p;
    b = (b % p + p) % p;
    return solve_equ(a, p, b);
}

// Test "local test" passed
#include <cstdio>
int main() {
    int x, y, res = extend_gcd(16, 36, x, y);
    printf("%d %d %d\n", res, x, y);
    printf("%d\n", solve_equ(16, 36, 1));
    printf("%d\n", solve_equ(16, 36, 100));
    printf("%d\n", solve(16, 100, 36));
    return 0;
}
