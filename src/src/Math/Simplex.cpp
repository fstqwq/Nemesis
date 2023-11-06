const LD eps = 1e-9, INF = 1e9; const int N = 105;
namespace Simplex {
int n, m, id[N], tp[N]; LD a[N][N];
void pivot(int r, int c) {
	swap(id[r + n], id[c]);
	LD t = -a[r][c]; a[r][c] = -1; 
	for (int i = 0; i <= n; i++) a[r][i] /= t;
	for (int i = 0; i <= m; i++) if (a[i][c] && r != i) {
		t = a[i][c]; a[i][c] = 0; 
		for (int j = 0; j <= n; j++) a[i][j] += t*a[r][j];}}
bool solve() {
	for (int i = 1; i <= n; i++) id[i] = i;
	for ( ; ; ) {
		int i = 0, j = 0; LD w = -eps;
		for (int k = 1; k <= m; k++)
			if (a[k][0] < w || (a[k][0] < -eps && rand() & 1))
				w = a[i = k][0]; 
		if (!i) break;
		for (int k = 1; k <= n; k++)
			if (a[i][k] > eps) {j = k; break;} 
		if (!j) { printf("Infeasible"); return 0;}
		pivot(i, j);}
	for ( ; ; ) {
		int i = 0, j = 0; LD w = eps, t;
		for (int k = 1; k <= n; k++)
			if (a[0][k] > w) w = a[0][j = k]; 
		if (!j) break;
		w = INF;
		for (int k = 1; k <= m; k++)
			if (a[k][j] < -eps && (t = -a[k][0]/a[k][j]) < w)
				w = t, i = k; 
		if (!i) { printf("Unbounded"); return 0;}
		pivot(i, j);}
	return 1;}
LD ans() {return a[0][0];}
void output() {
	for (int i = n + 1; i <= n + m; i++) tp[id[i]] = i - n;
	for (int i = 1; i <=n; i++) printf("%.9lf ", tp[i] ? a[tp[i]][0] : 0);}
}using namespace Simplex;
int main() { int K; read(n); read(m); read(K);
for (int i = 1; i <= n; i++) {LD x; scanf("%lf", &x); a[0][i] = x;}
for (int i = 1; i <= m; i++) {LD x;
	for (int j = 1; j <= n; j++) scanf("%lf", &x), a[i][j] = -x; 
	scanf("%lf", &x); a[i][0] = x;}
if (solve()) { printf("%.9lf\n", (LD)ans()); if (K) output();}}
// 标准型: maximize $\bf c^Tx$, subject to $\bf Ax\leq b$ and $\bf x\geq 0$
// 对偶型: minimize $\bf b^Ty$, subject to $\bf A^Tx\geq c$ and $\bf y\geq 0$
