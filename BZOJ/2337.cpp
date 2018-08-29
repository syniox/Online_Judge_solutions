#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
#include<cmath>
const int N=102,M=10002;
const double eps=1e-6;
int n,m,fir[N],dg[N];
double mg[N],mp[N][N];
struct edge{
	int to,wi,nx;
}eg[M<<1];

inline void add(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	++dg[a];
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void gauss(){
	for(int i=1;i<=n;++i){
		int j=i;
		while(j<=n&&fabs(mp[j][i])<eps) ++j;
		assert(j<=n);
		std::swap(mp[j],mp[i]);
		std::swap(mg[j],mg[i]);
		const double cur=mp[i][i];
		for(int k=1;k<=n;++k){
			if(k==i) continue;
			const double p=mp[k][i]/cur;
			for(int l=i;l<=n;++l){
				mp[k][l]-=mp[i][l]*p;
			}
			mg[k]-=mg[i]*p;
		}
	}
}

inline double solve(int bit){
	memset(mp,0,sizeof(mp));
	memset(mg,0,sizeof(mg));
	for(int x=1;x<n;++x){
		const double dgx=1.0/dg[x];
		mp[x][x]=-1;
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(eg[i].wi&(1<<bit)){
				mp[x][y]-=dgx;
				mg[x]-=dgx;
			}
			else{
				mp[x][y]+=dgx;
			}
		}
	}
	mp[n][n]=1;
	gauss();
	if(fabs(mp[1][1])<eps) return 0;
	return mg[1]/mp[1][1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	double ans=0;
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		if(a!=b) add(b,a,v);
	}
	for(int i=0;i<31;++i){
		ans+=solve(i)*(1<<i);
	}
	printf("%.3lf\n",ans);
	return 0;
}
