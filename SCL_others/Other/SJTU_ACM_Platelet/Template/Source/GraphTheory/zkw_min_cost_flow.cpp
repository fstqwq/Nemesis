int aug(int no, int res)
{
	if(no == ED)return mincost += 1ll * pil * res, res;
	v[no] = 1;
	int flow = 0;
	for(int i = son[no]; i != -1; i = edge[i].next)
		if(edge[i].f && !v[edge[i].y] && !edge[i].c)
		{
			int d = aug(edge[i].y, min(res, edge[i].f));
			edge[i].f -= d, edge[i ^ 1].f += d, flow += d, res -= d;
			if(!res)return flow;
		}
	return flow;
}

bool modlabel()
{
	long long d = 0x3f3f3f3f3f3f3f3fll;
	for(int i = 1; i <= cnt; i++)
		if(v[i])
		{
			for(int j = son[i]; j != -1; j = edge[j].next)
				if(edge[j].f && !v[edge[j].y] && edge[j].c < d)d = edge[j].c;
		}
	if(d == 0x3f3f3f3f3f3f3f3fll)return 0;
	for(int i = 1; i <= cnt; i++)
		if(v[i])
		{
			for(int j = son[i]; j != -1; j = edge[j].next)
				edge[j].c -= d, edge[j ^ 1].c += d;
		}
	pil += d;
	return 1;
}

void minimum_cost_flow_zkw()
{
	pil = 0;
	int nowans = 0;
	nowf = 0;
	do{
		do{
			for(int i = 1; i <= cnt; i++)
				v[i] = 0;
			nowans = aug(ST, inf);
			nowf += nowans;
		}while(nowans);
	}while(modlabel());
}
