/* fast_fourier transform */
/*
 * Set $N to be at least ${(n+m)*2}
 * Call fft_main($a, $b, $n, $m) where $n and $m stand for the number of terms of the
 *     two polynomials, while $a and $b represent the two polynomials 0-based, to
 *     get the 0-based result polynomial.
 * Reset $a and $b from 0 to at least ${(n+m)*2} to prevent undefined behavior
 *     caused by multiple test cases.
 */
#include <cmath>
#include <utility>
namespace fast_fourier_transform {
    struct comp {
        double r, i;
        explicit comp(double r = 0.0, double i = 0.0) : r(r), i(i) {}
        inline friend comp operator +(comp a, comp b) {
            return comp(a.r + b.r, a.i + b.i);
        }
        inline friend comp operator -(comp a, comp b) {
            return comp(a.r - b.r, a.i - b.i);
        }
        inline friend comp operator *(comp a, comp b) {
            return comp(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
        }
        inline friend comp operator /(comp a, double b) {
            return comp(a.r / b, a.i / b);
        }
    };
    const double pi = acos(-1);
    const int N = 5e5 + 10;
    int rev[N];
    inline void fft(comp *p, int n, int idft) {
        for (int i = 0; i < n; i++)
            if (i < rev[i])
                std::swap(p[i], p[rev[i]]);
        for (int j = 1; j < n; j <<= 1) {
            static comp wn1, w, t0, t1;
            wn1 = comp(cos(pi / j), idft * sin(pi / j));
            for (int i = 0; i < n; i += j << 1) {
                w = comp(1, 0);
                for (int k = 0; k < j; k++) {
                    t0 = p[i + k];
                    t1 = w * p[i + j + k];
                    p[i + k] = t0 + t1;
                    p[i + j + k] = t0 - t1;
                    w = w * wn1;
                }
            }
        }
        if (idft == -1) {
            for (int i = 0; i < n; i++)
                p[i] = p[i] / n;
        }
    }
    template <typename T>
    inline T* fft_main(T *a, T *b, int n, int m) {
        static T res[N];
        static int nn, len;
        static comp aa[N], bb[N];
        len = 0;
        for (nn = 1; nn < m + n; nn <<= 1)
            len++;
        for (int i = 0; i < nn; i++) {
            aa[i] = comp(a[i], 0);
            bb[i] = comp(b[i], 0);
        }
        rev[0] = 0;
        for (int i = 1; i < nn; i++)
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (len - 1));
        fft(aa, nn, 1);
        fft(bb, nn, 1);
        for (int i = 0; i < nn; i++)
            aa[i] = aa[i] * bb[i];
        fft(aa, nn, -1);
        for (int i = 0; i < nn; i++)
            res[i] = aa[i].r + 0.5;
        return res;
    }
}

// Test "loj108"
#include <cstdio>
const int N = 4e5 + 10;
int main() {
    static int n, m, a[N], b[N], *ans;
    scanf("%d%d", &n, &m);
    for (int i = 0; i <= n; i++)
        scanf("%d", a + i);
    for (int i = 0; i <= m; i++)
        scanf("%d", b + i);
    ans = fast_fourier_transform::fft_main(a, b, n + 1, m + 1);
    printf("%d", ans[0]);
    for (int i = 1; i <= n + m; i++)
        printf(" %d", ans[i]);
    putchar('\n');
    return 0;
}
