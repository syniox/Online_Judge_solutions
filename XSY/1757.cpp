#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2,E=N<<1;
int n,vl[N],fir[N],dp[N][2],tf[N][2];
//0:in 1: back
struct edge{
	int to,wi,nx;
}eg[E];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline void add(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void upd(int dp1[N][2],const int x,int dp2[N][2],const int y,const int v){
	apx(dp1[x][0],dp1[x][0]+dp2[y][1]-(v<<1));
	apx(dp1[x][0],dp1[x][1]+dp2[y][0]-v);
	apx(dp1[x][1],dp1[x][1]+dp2[y][1]-(v<<1));
}

void init_dfs(int x,int fa){
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa){
			init_dfs(y,x);
			upd(dp,x,dp,y,eg[i].wi);
		}
	}
}

void dfs(int x,int fa){
	static int top,que[N],cf[N][2];
	top=0;
//	memcpy(cf[0],dp[x],sizeof(cf[0]));
	cf[0][0]=cf[0][1]=0;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa){
			que[++top]=i;
			memcpy(cf[top],cf[top-1],sizeof(cf[0]));
			upd(cf,top,dp,y,eg[i].wi);
		}
	}
	int t0=tf[x][0]+vl[x],t1=tf[x][1]+vl[x];
	for(int i=top;i;--i){
		const int p=que[i],y=eg[p].to;
		const int p0=std::max(t0+cf[i-1][1],t1+cf[i-1][0]);
		const int p1=t1+cf[i-1][1];
		tf[y][0]=std::max(0,p0-eg[p].wi);
		tf[y][1]=std::max(0,p1-(eg[p].wi<<1));

		apx(t0,t0+dp[y][1]-(eg[p].wi<<1));
		apx(t0,t1+dp[y][0]-eg[p].wi);
		apx(t1,t1+dp[y][1]-(eg[p].wi<<1));

		dp[y][0]=std::max(dp[y][1]+tf[y][0],dp[y][0]+tf[y][1]);
		dp[y][1]+=tf[y][1];
	}
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa) dfs(y,x);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		dp[i][0]=dp[i][1]=vl[i]=nxi();
	}
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	init_dfs(1,0);
	dfs(1,0);
	for(int i=1;i<=n;++i){
		printf("%d\n",std::max(dp[i][0],dp[i][1]));
	}
	return 0;
}
