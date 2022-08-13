mt19937 rng(123);
#define rand() LL(rng() & LLONG_MAX)
const int BASE[] = {2, 7, 61};//int(7,3e9)
//{2,325,9375,28178,450775,9780504,1795265022}LL(37)
struct miller_rabin {
bool check (const LL &M, const LL &base) {
	LL a = M - 1;
	while (~a & 1) a >>= 1;
	LL w = power (base, a, M); // power should use mul
	for (; a != M - 1 && w != 1 && w != M - 1; a <<= 1)
		w = mul (w, w, M);
	return w == M - 1 || (a & 1) == 1; }
bool solve (const LL &a) {//$O((3 \text{ or } 7) \cdot \log n \cdot \mathrm{mul})$
	if (a < 4) return a > 1;
	if (~a & 1) return false;
	for (int i = 0; i < sizeof(BASE)/4 && BASE[i] < a; ++i)
		if (!check (a, BASE[i])) return false;
	return true; } };
miller_rabin is_prime;
LL get_factor (LL a, LL seed) {//$O(n ^ {1/4} \cdot \log n \cdot \mathrm{mul})$
	LL x = rand () % (a - 1) + 1, y = x;
	for (int head = 1, tail = 2; ; ) {
		x = mul (x, x, a); x = (x + seed) % a;
		if (x == y) return a;
		LL ans = gcd (abs (x - y), a);
		if (ans > 1 && ans < a) return ans;
		if (++head == tail) { y = x; tail <<= 1; } } }
void factor (LL a, vector<LL> &d) {
	if (a <= 1) return;
	if (is_prime.solve (a)) d.push_back (a);
	else {
		LL f = a;
		for (; f >= a; f = get_factor (a, rand() % (a - 1) + 1));
		factor (a / f, d);
		factor (f, d); } }
