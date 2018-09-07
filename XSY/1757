#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,dg[N],fir[N],ans[N],dp[N][2];
//0:in 1: back
struct edge{
	int to,wi,nx;
}eg[N];

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
	apx(dp1[x][0],dp1[x][0]+dp2[y][1]+(v<<1));
	apx(dp1[x][0],dp1[x][1]+dp2[y][0]+v);
	apx(dp1[x][1],dp1[x][1]+dp2[y][1]+(v<<1));
}

void init_dfs(int x,int fa){
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa){
			++dg[x];
			init_dfs(y,x);
			upd(dp,x,dp,y,eg[i].wi);
		}
	}
}

void dfs(int x,int fa){
	static int top,que[N],cf[N][2];
	ans[x]=std::max(dp[x][0],dp[x][1]);
	memcpy(cf[0],dp[x],sizeof(cf[0]));
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa){
			que[++top]=y;
			memcpy(cf[top],cf[top-1],sizeof(dp[0]));
			upd(cf,top,dp,y,eg[i].wi);
		}
	}
	for(int i=top;i;--i){
		int t0=dp[x][0],t1=dp[x][1];
		const int y=eg[i].to;
	}
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa) dfs(y,x);
	}
}

int main(){
	n=nxi();
	for(int i=1;i<=n;++i){
		dp[i][0]=dp[i][1]=nxi();
	}
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	init_dfs(1,0);
	dfs(1,0);
	for(int i=1;i<=n;++i){
		printf("%d\n",ans[i]);
	}
	return 0;
}
