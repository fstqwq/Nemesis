int SubsetSum(vector <int> &a, int t) {
  int B = *max_element(a.begin(), a.end());
  int n = (int) a.size(), s = 0, i = 0;
  while (i < n && s + a[i] <= t) s += a[i ++];
  if (i == n) return s;
  vector <int> f(2 * B + 1, -1), pre (B + 1, -1);
  f[s - (t - B)] = i;
  for ( ; i < n; i++) {
    s += a[i];
    for (int d = 0; d <= B; d++) pre[d] = max(0, f[d + B]);
    for (int d = B; d >= 0; d--)
      f[d + a[i]] = max(f[d + a[i]], f[d]);
    for (int d = 2 * B; d > B; --d)
      for (int j = pre[d - B]; j < f[d]; j++)
        f[d - a[j]] = max(f[d - a[j]], j); }
  for (i = 0; i <= B; i++) if (f[B - i] >= 0) return t - i;}