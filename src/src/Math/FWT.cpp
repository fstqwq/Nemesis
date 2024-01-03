/*      FWT         IFWT
And:|  1  1  |   |  1 -1  |
    |  0  1  |   |  0  1  |
Or: |  1  0  |   |  1  0  |
    |  1  1  |   | -1  1  |
Xor:|  1  1  |   | 0.5  0.5|
    |  1 -1  |   | 0.5 -0.5|
IFWT的矩阵时FWT的逆, 对于任意运算 $\oplus$，满足FWT的矩阵需要：
$C[i][j] \times C[i][k] = C[i][j \oplus k]$
对于不存在FWT矩阵的运算: 通过映射01变成另外一个可行的运算。*/
const LL AND[2][2] = {{1, 1}, {0, 1}};
const LL iAND[2][2] = {{1, M-1}, {0, 1}};
const LL OR[2][2] = {{1, 0}, {1, 1}};
const LL iOR[2][2] = {{1, 0}, {M-1, 1}};
const LL XOR[2][2] = {{1, 1}, {1, M-1}};
const LL i2 = (M+1)/2, iXOR[2][2] = {{i2, i2}, {i2, M-i2}};
void FWT(LL *f, const LL C[2][2], int n) {
  for (int t = 1; t < n; t <<= 1) {
    for (int l = 0; l < n; l += t + t) {
      for (int i = 0; i < t; i++) {
        LL x = f[l + i], y = f[l + t + i];
        f[l + i]     = (C[0][0] * x + C[0][1] * y) % M;
        f[l + t + i] = (C[1][0] * x + C[1][1] * y) % M;
      } } } }