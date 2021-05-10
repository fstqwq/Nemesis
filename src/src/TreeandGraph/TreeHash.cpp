ULL get(vector <ULL> ha) {
	sort(ha.begin(), ha.end());
	ULL ret = 0xdeadbeef;
	for (auto i : ha) {
		ret = ret * P + i;
		ret ^= ret << 17; }
	return ret * 997; }
