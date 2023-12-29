// n : power of k, omega[i] : (primitive kth root) ^ i
void fwt(int* a, int k, int type) {
  static int tmp[K];
  for (int i = 1; i < n; i *= k)
    for (int j = 0, len = i * k; j < n; j += len)
      for (int low = 0; low < i; low++) {
        for (int t = 0; t < k; t++)
          tmp[t] = a[j + t * i + low];
        for (int t = 0; t < k; t++){
          int x = j + t * i + low;
          a[x] = 0;
          for (int y = 0; y < k; y++)
            a[x] = int(a[x] + 1ll * tmp[y] * omega[(k + type) * t * y % k] % MOD);
        }
      }
  if (type == -1)
    for (int i = 0, invn = inv(n); i < n; i++)
      a[i] = int(1ll * a[i] * invn % MOD); }