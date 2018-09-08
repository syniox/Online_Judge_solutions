#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e6+2;
const lint mod=2333333333333333;
int n,fir[N];
lint ans,dp[N<<1],dep[N<<1];
struct edge{
	int to,wi,nx;
}eg[N<<1];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void add(int a,int b,int v){
	static int cnt=1;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

void init_dfs(int x,int e){
	int fa=eg[e^1].to;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y!=fa){
			init_dfs(y,i);
			apx(dp[e],dp[i]);
			apx(dp[e],dep[e]+dep[i]+eg[i].wi);
			apx(dep[e],dep[i]+eg[i].wi);
		}
	}
}

template <class T> inline void xswp(T &x,T &y){
	if(x<y) std::swap(x,y);
}

void dfs(int x,int fa){
	lint d1=0,d2=0,d3=0,dp1=0,dp2=0;
	for(int i=fir[x];i;i=eg[i].nx){
		lint v=dep[i]+eg[i].wi,f=dp[i];
		xswp(d1,v);
		xswp(d2,v);
		xswp(d3,v);
		xswp(dp1,f);
		xswp(dp2,f);
	}
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		if(y!=fa){
			const lint v=dep[i]+eg[i].wi;
			lint tp;
			if(v==d1||v==d2) tp=d1+d2+d3-v;
			else tp=d1+d2;
			apx(dp[i^1],tp);
			if(dp[i]==dp1) apx(dp[i^1],dp2);
			else apx(dp[i^1],dp1);
			if(v==d1) apx(dep[i^1],d2);
			else apx(dep[i^1],d1);
			dfs(y,x);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<n;++i){
		const int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	init_dfs(1,0);
	dfs(1,0);
	lint ans=0;
	for(int i=1;i<n;++i){
		lint x=dp[i<<1],y=dp[i<<1|1];
		xswp(x,y);
		ans=(ans+x*23333+y*2333+(lint)i*i*233+i*23+2)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
