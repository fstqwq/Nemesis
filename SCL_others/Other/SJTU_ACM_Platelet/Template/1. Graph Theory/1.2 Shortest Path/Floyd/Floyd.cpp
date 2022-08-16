//
//  Title : Floyd for ShortestPath
//  Date:23.11.2015
//  Complexity:
//    Time:O(N^3)
//    Space:O(N^2)
//  Test:YZOJ-1318
/*
    已知一幅图G，求任意两点间最短路径 
    算法实现：Floyd
	优点：代码短，理解快
	缺点：复杂度 
*/
#include<cstdio>
#define R register
#define maxn 23333333
#define min(a,b) ((a)<(b)?(a):(b))

namespace ct
{
    int map[110][110];
	 int n,m;
    inline void scan()
    {	
    	scanf("%d%d",&n,&m);
		R int i,a,b,v;
    	for (i=1;i<=m;i++)
	    {
		  scanf("%d%d%d",&a,&b,&v);
		  map[a][b]=v;map[b][a]=v;
	    }
	}	
	inline void print()	
	{
		R int i,j;
		for (i=1;i<=n;i++)
		  {
		  	 for (j=1;j<=n;j++)
		  	   printf("%d ",map[i][j]);
		  	puts("");
		  }		    
	}
	inline void fill()
	{
		R int i,j;
		for (i=1;i<=n;i++)
		  for (j=1;j<=n;j++)
		    map[i][j]=!map[i][j]?i!=j?maxn:0:map[i][j];
	}	
	inline void floyd()
	{
		R int i,j,k;
		for (k=1;k<=n;k++)//k在外面！！！重要！！！ 
		  for (i=1;i<=n;i++)
		    for (j=1;j<=n;j++)		    
		      {
		      	map[i][j]=min(map[i][k]+map[k][j],map[i][j]);
				map[j][i]=min(map[j][k]+map[k][i],map[j][i]);
			  }
	}
	inline void Main()
	{
	    scan();
	    fill();			
		floyd();
		print();							
	}
}

int main()
{
	ct::Main();
	return 0;
}
