Val work(LL P, LL R, LL Q, LL n, Val VU, Val VR) {
//(Px+R)/Q, 1<=x<=i, 经过整点先U再R
	if(!(((i128)n * P + R) / Q)) return ksm(VR, n);
	if(P>=Q) return work(P%Q,R,Q,n, VU, ksm(VU, P/Q) * VR);
	Val res; swap(VU,VR);
	res = ksm(VU, (Q-R-1)/P)*VR;
	LL m = ((i128)n * P + R) / Q;
	res = res * work(Q, (Q-R-1)%P, P, m-1, VU, VR);
	return res * ksm(VU, n - ((i128)m*Q - R - 1) / P); }