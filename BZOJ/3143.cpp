#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
const int N=502;
const double eps=1e-6;
int n,m,dg[N],fir[N];
double cm[N*N],mp[N][N];
struct edge{
	int to,nx;
}eg[N*N<<1];

inline void add(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
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
		if(j>n) return;
		std::swap(mp[j],mp[i]);
		const double cur=mp[i][i];
		for(int k=1;k<=n;++k){
			if(k==i) continue;
			const double p=mp[k][i]/cur;
			for(int l=0;l<=n;++l){
				mp[k][l]-=mp[i][l]*p;
			}
		}
/*		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				printf("%.3lf ",mp[i][j]);
			}
			printf(" -> %.3lf\n",mp[i][0]);
		}
		puts("---");*/
	}
}

inline void get_men(){
	for(int x=1;x<n;++x){
		const double dgx=1.0/dg[x];
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			mp[y][x]+=dgx;
		}
		mp[x][x]-=1;
	}
	memset(mp[n],0,sizeof(mp[n]));
	mp[1][0]=-1;
	mp[n][n]=1;
	gauss();
	for(int i=1;i<=n;++i){
		mp[i][i]=mp[i][0]/mp[i][i];
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	double ans=0;
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi();
		add(a,b);
		add(b,a);
	}
	get_men();
	for(int x=1;x<n;++x){
		const double cur=mp[x][x];
//		printf("%.3lf ",cur);
		for(int i=fir[x];i;i=eg[i].nx){
			cm[(i+1)>>1]+=cur/dg[x];
		}
	}
//	printf("%.3lf\n",mp[n][n]);
	std::sort(cm+1,cm+m+1);
	for(int i=m;i;--i){
//		printf("%lf ",cm[i]);
		ans+=i*cm[m-i+1];
	}
	printf("%.3lf\n",ans);
	return 0;
}
