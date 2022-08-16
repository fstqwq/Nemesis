#include <cstdint>
#include <utility>

const int64_t MOD = 1000000007;

int64_t modPow(int64_t a, int64_t exp) {
    static int64_t ans;
    ans = 1;
    while (exp) {
        if (exp & 1)
            (ans *= a) %= MOD;
        (a *= a) %= MOD;
        exp >>= 1;
    }
    return ans;
}

int64_t inverse(int64_t a) {
    return modPow(a, MOD - 2);
}

template <typename T>
int64_t gauss_determinant(T a, int n) {
    bool negative = false;
    for (int i = 1; i <= n; i++) {
        if (a[i][i] == 0) {
            bool flag = true;
            for (int j = i + 1; j <= n && flag; j++)
                if (a[j][i] != 0) {
                    for (int k = i; k <= n; k++)
                        std::swap(a[i][k], a[j][k]);
                    negative = !negative;
                    flag = false;
                }
            if (flag)
                return 0;
        }

        for (int j = i + 1; j <= n; j++) {
            if (a[j][i] == 0)
                continue;
            int64_t co = a[j][i] * inverse(a[i][i]) % MOD;
            for (int k = i; k <= n; k++)
                (a[j][k] -= a[i][k] * co) %= MOD;
        }
    }

    int64_t ans = negative ? -1 : 1;
    for (int i = 1; i <= n; i++)
        (ans *= a[i][i]) %= MOD;
    if (ans < 0)
        ans += MOD;

    return ans;
}

// Test "hdu 5852" passed
int main() {
    return 0;
}
