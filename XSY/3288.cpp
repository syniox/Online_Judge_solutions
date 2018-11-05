#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=19;
const int mod=998244353;
int n,m,fir[N],f[1<<18][N],dp[1<<18][N];
struct edge{
	int to,nx;
}eg[N*N];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void add_edge(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

int get_f(const int s,const int x){
	if(f[s][x]) return f[s][x];
	f[s][x]=s;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(!(s&1<<(y-1))) f[s][x]|=get_f(s|(1<<(y-1)),y);
	}
	return f[s][x];
}

int dfs(const int s,const int x){
	if(~dp[s][x]) return dp[s][x];
	if(f[s][x]==s) return 1;
	int ans=0;
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to,st=1<<(y-1);
		if(!(s&st)){
			ans=(ans+(lint)dfs(s|st,y)*dfs(s|f[s|st][y],x))%mod;
		}
	}
	return dp[s][x]=ans;
}

inline int solve(){
	int ans=0;
	for(int i=1;i<=n;++i){
		twk(ans+=dfs(1<<(i-1),i));
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	memset(dp,-1,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		add_edge(x,y);
		add_edge(y,x);
	}
	for(int i=1;i<=n;++i){
		for(int j=1<<(i-1);j<1<<n;j=1<<(i-1)|(j+1)){
			get_f(j,i);
		}
	}
	printf("%d\n",solve());
	return 0;
}
