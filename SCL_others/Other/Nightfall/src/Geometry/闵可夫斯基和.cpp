// cv[0..1] 为两个顺时针凸包, 其中起点等于终点, 求出的闵可夫斯基和不一定是严格凸包
int i[2] = {0, 0}, len[2] = {(int)cv[0].size() - 1, (int)cv[1].size() - 1};
vector<point> mnk;
mnk.push_back(cv[0][0] + cv[1][0]);
do {
	int d = (det(cv[0][i[0] + 1] - cv[0][i[0]], cv[1][i[1] + 1] - cv[1][i[1]]) >= 0);
	mnk.push_back(cv[d][i[d] + 1] - cv[d][i[d]] + mnk.back());
	i[d] = (i[d] + 1) % len[d];
} while(i[0] || i[1]);