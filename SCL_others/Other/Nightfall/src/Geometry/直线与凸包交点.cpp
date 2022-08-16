// a 是顺时针凸包, i1 为 x 最小的点, j1 为 x 最大的点 需保证 j1 > i1
// n 是凸包上的点数, a 需复制多份或写循环数组类
int lowerBound(int le, int ri, const P & dir) {
	while (le < ri) {
		int mid((le + ri) / 2);
		if (sign((a[mid + 1] - a[mid]) * dir) <= 0) {
			le = mid + 1;
		} else ri = mid; }
	return le; }
int boundLower(int le, int ri, const P & s, const P & t) {
	while (le < ri) {
		int mid((le + ri + 1) / 2);
		if (sign((a[mid] - s) * (t - s)) <= 0) {
			le = mid;
		} else ri = mid - 1; }
	return le; }
void calc(P s, P t) {
	if(t < s) swap(t, s);
	int i3(lowerBound(i1, j1, t - s)); // 和上凸包的切点
	int j3(lowerBound(j1, i1 + n, s - t)); // 和下凸包的切点
	int i4(boundLower(i3, j3, s, t)); // 如果有交则是右侧的交点, 与 a[i4]~a[i4+1] 相交 要判断是否有交的话 就手动 check 一下
	int j4(boundLower(j3, i3 + n, t, s)); // 如果有交左侧的交点, 与 a[j4]~a[j4+1] 相交
    // 返回的下标不一定在 [0 ~ n-1] 内
}
