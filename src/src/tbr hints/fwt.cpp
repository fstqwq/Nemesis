void fwt(int* a, int k, int type){ // n should be a power of k, omega[i] : ith power of primitive kth root
    for (int i = 1; i < n; i *= k){
        for (int j = 0, len = i * k; j < n; j += len){
            for (int low = 0; low < i; low++){
                int tmp[k] = {0};
                for (int t = 0; t < k; t++)
                    tmp[t] = a[j + t * i + low];
                for (int t = 0; t < k; t++){
                    a[j + t * i + low] = 0;
                    for (int tt = 0; tt < k; tt++)
                        (a[j + t * i + low] += 1ll * tmp[tt] * omega[(type * t * tt % k + k) % k] % p) %= p;

                }
            }
        }
    }
    if (type == -1)
        for (int i = 0, invn = inv(n); i < n; i++) a[i] = 1ll * a[i] * invn % p;
}
