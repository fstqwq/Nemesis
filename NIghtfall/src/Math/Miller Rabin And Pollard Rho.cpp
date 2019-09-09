// Miller Rabin : bool miller_rabin::solve (const LL &) : tests whether a certain integer is prime.
typedef long long LL; struct miller_rabin {
int BASE[12] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
bool check (const LL &prime, const LL &base) {
	LL number = prime - 1;
	for (; ~number & 1; number >>= 1);
	LL result = llfpm (base, number, prime);
	for (; number != prime - 1 && result != 1 && result != prime - 1; number <<= 1)
		result = mul_mod (result, result, prime);
	return result == prime - 1 || (number & 1) == 1; }
bool solve (const LL &number) { // is prime
	if (number < 2) return false;
	if (number < 4) return true;
	if (~number & 1) return false;
	for (int i = 0; i < 12 && BASE[i] < number; ++i)
		if (!check (number, BASE[i])) return false;
	return true; } };
miller_rabin is_prime; const LL threshold = 13E9;
LL factorize (LL number, LL seed) {
	LL x = rand() % (number - 1) + 1, y = x;
	for (int head = 1, tail = 2; ; ) {
		x = mul_mod (x, x, number); x = (x + seed) % number;
		if (x == y) return number;
		LL answer = gcd (abs (x - y), number);
		if (answer > 1 && answer < number) return answer;
		if (++head == tail) { y = x; tail <<= 1; } } }
void search (LL number, std::vector<LL> &divisor) {
	if (number <= 1) return;
	if (is_prime.solve (number)) divisor.push_back (number);
	else {
		LL factor = number;
		for (; factor >= number; factor = factorize (number, rand () % (number - 1) + 1));
		search (number / factor, divisor);
		search (factor, divisor); } }