// a[0..1]: 逆时针凸包.结果不是严格凸包
for (int i = 0; i < 2; i++) a[i].push_back(a[i].front()); 
int i[2] = {0, 0},
  len[2] = {(int)a[0].size() - 1, (int)a[1].size() - 1};
vector<point> mnk;
mnk.push_back(a[0][0] + a[1][0]);
do { // 输入不严格时（如（n <= 2）共线）会死循环，需特判 
	int d = sgn(det(a[1][i[1] + 1] - a[1][i[1]],
                   a[0][i[0] + 1] - a[0][i[0]])) >= 0;
	mnk.push_back(a[d][i[d] + 1] - a[d][i[d]] + mnk.back());
	i[d] = (i[d] + 1) % len[d];
} while(i[0] || i[1]);
