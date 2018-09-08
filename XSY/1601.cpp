#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2e5+2;
int n,dep[N<<1],dp[N<<1];

inline void xswp(int &x,int &y){
	if(x<y) std::swap(x,y);
}
inline void apn(int &x,int y){
	if(x>y) x=y;
}
inline void apx(int &x,int y){
	if(x<y) x=y;
}

inline char get_c(){
	static char buf[20000],*h,*t;
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

namespace G{
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<1];
	inline void init(){
		cnt=1;
		memset(fir,0,sizeof(fir));
	}
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void init_dfs(int x,int e){
		for(int i=fir[x];i;i=eg[i].nx){
			if((e^1)==i) continue;
			const int y=eg[i].to;
			init_dfs(y,i);
			apx(dp[e],dep[e]+dep[i]+1);
			apx(dp[e],dp[i]);
			apx(dep[e],dep[i]+1);
		}
	}
	void dfs(int x,int e){
		int d1=0,d2=0,d3=0,dp1=0,dp2=0;
		for(int i=fir[x];i;i=eg[i].nx){
			int v=dep[i]+1,f=dp[i];
			xswp(d1,v),xswp(d2,v),xswp(d3,v);
			xswp(dp1,f),xswp(dp2,f);
		}
		for(int i=fir[x];i;i=eg[i].nx){
			if((e^1)==i) continue;
			const int v=dep[i]+1;
			if(v==d1||v==d2) dp[i^1]=d1+d2+d3-v;
			else dp[i^1]=d1+d2;
			if(dp[i]==dp1) apx(dp[i^1],dp2);
			else apx(dp[i^1],dp1);
			dep[i^1]=(v==d1?d2:d1);
			dfs(eg[i].to,i);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		G::init();
		memset(dp,0,sizeof(dp));
		memset(dep,0,sizeof(dep));
		n=nxi();
		for(int i=1;i<n;++i){
			const int a=nxi(),b=nxi();
			G::add(a,b);
			G::add(b,a);
		}
		G::init_dfs(1,0);
		G::dfs(1,0);
		int ans=1e9;
		for(int i=1;i<n;++i){
			apn(ans,std::max((dp[i<<1]+1)>>1,(dp[i<<1|1]+1)>>1));
		}
		printf("%d\n",ans);
	}
	return 0;
}
