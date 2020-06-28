#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,m,mu[N],res[N],xval,val[N];//res %=phi
bool imp[N],vld[N],vis[N];
std::vector <int> buk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

namespace G{
	const int mod=::mod-1;
	int rt,cnt,ans,fir[N],dp[N][2];//是否經過重要點
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs(const int x){
		dp[x][imp[x]^1]=0,dp[x][imp[x]]=1;
		ans+=dp[x][1];
		vis[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(vis[y]||!vld[y]) continue;
			dfs(y);
			ans=(ans+(lint)dp[x][1]*dp[y][0])%mod;
			ans=(ans+(lint)dp[x][0]*dp[y][1])%mod;
			ans=(ans+(lint)dp[x][1]*dp[y][1])%mod;
			dp[x][0]+=dp[y][0],dp[x][1]+=dp[y][1];
			if(imp[x])
				dp[x][1]+=dp[y][0],dp[x][0]=0;
		}
	}

	int work(const int rt){
		ans=0,dfs(rt);
		return ans;
	}
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	static int cnp,prm[N];
	static bool npr[N];
	mu[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]) mu[prm[++cnp]=i]=-1;
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
			mu[i*prm[j]]=-mu[i];
		}
	}
}

int main(){
	init();
	n=nxi(),m=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1; i<=n; ++i){
		apx(xval,val[i]=nxi());
		buk[val[i]].push_back(i);
	}
	for(int i=1; i<=m; ++i){
		imp[nxi()]=1;
	}
	for(int i=2; i<=xval; ++i){
		std::vector <int> ::iterator it;
		for(int j=i*2; j<=xval; j+=i){
			for(it=buk[j].begin(); it!=buk[j].end(); ++it)
				buk[i].push_back(*it);
		}
		for(it=buk[i].begin(); it!=buk[i].end(); ++it)
			vld[*it]=1;
		for(it=buk[i].begin(); it!=buk[i].end(); ++it){
			if(!vis[*it]) res[i]=(res[i]+G::work(*it))%(mod-1);
		}
		//eprintf("%d: %d\n",i,res[i]);
		for(it=buk[i].begin(); it!=buk[i].end(); ++it)
			vld[*it]=vis[*it]=0;
	}
	int ans=1;
	for(int i=2; i<=xval; ++i){
		int r=0;
		for(int j=1; i*j<=xval; ++j)
			r=(r+mu[j]*res[i*j])%(mod-1);
		r=(r+mod-1)%(mod-1);
		ans=(lint)ans*fpow(i,r)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
