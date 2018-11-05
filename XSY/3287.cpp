#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e7+5;
const int mod=998244353;
int n,dp[N],sz[N],fir[N],que[N];
struct edge{
	int to,nx;
}eg[N];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline void add_edge(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void get_queue(){
	int hd=1,tl=2;
	que[hd]=1;
	while(hd!=tl){
		const int x=que[hd++];
		for(int i=fir[x];i;i=eg[i].nx){
			que[tl++]=eg[i].to;
		}
	}
}

inline void solve(){
	for(int i=n;i;--i){
		sz[i]=1;
		for(int j=fir[i];j;j=eg[j].nx){
			sz[i]+=sz[eg[j].to];
			twk(dp[i]+=dp[eg[j].to]);
		}
		twk(dp[i]+=qpow(sz[i],mod-2));
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=2;i<=n;++i){
		add_edge(nxi(),i);
	}
	get_queue();
	solve();
	printf("%d\n",dp[1]);
	return 0;
}
