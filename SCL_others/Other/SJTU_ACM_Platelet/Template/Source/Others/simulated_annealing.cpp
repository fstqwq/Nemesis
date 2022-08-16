db ans_x, fans;
inline double rand01() {return rand() / 2147483647.0;}
inline double randp() {return (rand() & 1 ? 1 : -1) * rand01();}
inline double f(double x)
{
	/*
		write your function here.
	*/
	if (maxx < fans) {fans = maxx; ans_x = x;}
	return maxx;
}
int main()
{
	srand(time(NULL) + clock());
	db x = 0, fnow = f(x);
	fans = 1e30;
	for (db T = 1e4; T > 1e-4; T *= 0.997)
	{
		db nx = x + randp() * T, fnext = f(nx);
		db delta = fnext - fnow;
		if (delta < 1e-9 || exp(-delta / T) > rand01())
		{
			x = nx;
			fnow = fnext;
		}
	}
	return 0;
}
