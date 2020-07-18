#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=1e5+5;
const int B=460;
const int S=1e4+1;
const int mod=998244353;
int n,val[N],finv[N];
int pwb[B][S],pwx[B][S];

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int lpow(int x,int t){
	return (lint)pwb[x][t/S]*pwx[x][t%S]%mod;
}

namespace D{
	int cnt,v[N];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		sort(v+1,v+cnt+1);
		cnt=unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return lower_bound(v+1,v+cnt+1,x)-v;
	}
}

void get_pw(){
	for(int i=1; i<=D::cnt; ++i){
		pwx[i][0]=pwb[i][0]=1;
		for(int j=1; j<S; ++j){
			pwx[i][j]=(lint)pwx[i][j-1]*D::v[i]%mod;
		}
		pwb[i][1]=(lint)pwx[i][S-1]*D::v[i]%mod;
		for(int j=2; j<S; ++j){
			pwb[i][j]=(lint)pwb[i][j-1]*pwb[i][1]%mod;
		}
	}
}

namespace G{
	int cnt,fir[N],dgr[N],fa[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		fa[b]=a;
		++dgr[a];
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	int dfs(const int x,const int t){//t==1?
		static int cache[B][N];
		if(cache[t][x]) return cache[t][x];
		int ans;
		if(D::v[t]==1){
			ans=val[x]+1;
		}else{
			ans=(1-lpow(t,val[x]+1)+mod);
			ans=(lint)ans*finv[D::v[t]]%mod;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			ans=(lint)ans*dfs(eg[i].to,t)%mod;
		}
		cache[t][x]=ans;
		return ans;
	}
}

int main(){
	n=nxi();
	for(int i=2; i<=n; ++i){
		G::add(nxi(),i);
	}
	finv[0]=fpow(1,mod-2);
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		finv[i]=fpow(1-i+mod,mod-2);
		D::add(G::dgr[i]);
	}
	D::build();
	get_pw();
	for(int i=1; i<=n; ++i){
		printf("%d\n",G::dfs(i,D::ask(G::dgr[i])));
	}
	return 0;
}
