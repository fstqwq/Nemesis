struct event
{
	int x, y, id, opt, ans;
} t[maxn], q[maxn];
void cdq(int left, int right)
{
	if (left == right) return ;
	int mid = left + right >> 1;
	cdq(left, mid);
	cdq(mid + 1, right);
	//分成若干个子问题
	++now;
	for (int i = left, j = mid + 1; j <= right; ++j)
	{
		for (; i <= mid && q[i].x <= q[j].x; ++i)
			if (!q[i].opt)
				add(q[i].y, q[i].ans);
		//考虑前面的修改操作对后面的询问的影响
		if (q[j].opt)
			q[j].ans += query(q[j].y);
	}
	int i, j, k = 0;
	//以下相当于归并排序
	for (i = left, j = mid + 1; i <= mid && j <= right; )
	{
		if (q[i].x <= q[j].x)
			t[k++] = q[i++];
		else
			t[k++] = q[j++];
	}
	for (; i <= mid; )
		t[k++] = q[i++];
	for (; j <= right; )
		t[k++] = q[j++];
	for (int i = 0; i < k; ++i)
		q[left + i] = t[i];
}
