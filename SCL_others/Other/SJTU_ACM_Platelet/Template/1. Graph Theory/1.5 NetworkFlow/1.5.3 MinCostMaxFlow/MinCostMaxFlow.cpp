typedef long long ans_type;
const int inf = 0x7fffffff;
struct Edge
{
	int from, to, w, c;
	Edge *next, *rev;
}*last[maxn], *prev[maxn], e[maxm], *ecnt = e;
int dis[maxn], s, t;
ans_type ans;
bool inq[maxn];
int q[maxn << 2];
inline void link(int a, int b, int w, int c)
{
	*++ecnt = (Edge) {a, b, w, c, last[a], ecnt + 1}; last[a] = ecnt;
	*++ecnt = (Edge) {b, a, 0, -c, last[b], ecnt - 1}; last[b] = ecnt;
}
inline bool spfa()
{
	memset(dis, 63, (t + 1) << 2);
	int head = 0, tail = 1;
	q[1] = s; inq[s] = 1; dis[s] = 0;
	while (head < tail)
	{
		int now = q[++head]; inq[now] = 0;
		for (Edge *iter = last[now]; iter; iter = iter -> next)
			if (iter -> w && iter -> c + dis[now] < dis[iter -> to])
			{
				dis[iter -> to] = iter -> c + dis[now];
				prev[iter -> to] = iter;
				if (!inq[iter -> to]) inq[q[++tail] = iter -> to] = 1;
			}
	}
	return dis[t] != 0x7f7f7f7f;
}
inline void mcmf()
{
	int x = inf;
	for (Edge *iter = prev[t]; iter; iter = prev[iter -> from])
		cmin(x, iter -> w);
	for (Edge *iter = prev[t]; iter; iter = prev[iter -> from])
	{
		ans += x * iter -> c;
		iter -> w -= x;
		iter -> rev -> w += x;
	}
}
