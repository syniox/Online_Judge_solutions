#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
int n,q,val[N];

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,##__VA_ARGS__)
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

namespace D{
	int cnt,v[N];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
	}
}

namespace G{
	int cnt=1,tgt,fir[N];
	int sz[N<<1],dp[N<<1],ans;
	//dp[i]: 在i指向的子树中在val>=tgt的情况下可以走的点数
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs1(const int x,const int e){
		int vld_s=0,mx=0;
		sz[e]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) dfs1(eg[i].to,i),sz[e]+=sz[i];
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			if(dp[i]==sz[i]){
				vld_s+=dp[i];
			}else{
				apx(mx,dp[i]);
			}
		}
		sz[e^1]=n-sz[e];
		dp[e]=val[x]>=tgt?vld_s+mx+1:0;
	}
	void dfs2(const int x,const int e){
		int vld_s=0,x1=0,x2=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(dp[i]==sz[i]){
				vld_s+=dp[i];
			}else{
				int tmp=dp[i];
				if(tmp>x1) std::swap(x1,tmp);
				if(tmp>x2) std::swap(x2,tmp);
			}
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(val[x]<tgt){
				dp[i^1]=0;
			}else{
				if(dp[i]==sz[i]){
					dp[i^1]=vld_s-dp[i]+x1+1;
				}else{
					dp[i^1]=vld_s+(dp[i]==x1?x2:x1)+1;
				}
			}
		}
		if(val[x]>=tgt)
			apx(ans,vld_s+x1+1);
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) dfs2(eg[i].to,i);
		}
	}

	bool jdg(const int tgt){
		G::tgt=tgt,ans=0;
		dfs1(1,0);
		dfs2(1,0);
		return ans>=q;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		D::add(val[i]);
	}
	D::build();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	{
		using namespace D;
		int l=1,r=cnt,mid;
		while(l!=r){
			mid=(l+r+1)>>1;
			if(G::jdg(v[mid])) l=mid;
			else r=mid-1;
		}
		printf("%d\n",v[l]);
	}
	return 0;
}
