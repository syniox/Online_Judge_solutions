#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=131072;
const int mod=998244353;
int n,q,ans,fac[N],ifac[N];

namespace utils{
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

inline void init(){
	fac[0]=1;
	for(int i=1; i<=q; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[q]=fpow(fac[q],mod-2)%mod;
	for(int i=q; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

namespace P{
	const int W=3;
	int wt[N];
	struct _init{
		_init(){
			wt[0]=1;
			int t=fpow(W,(mod-1)/N);
			for(int i=1; i<N; ++i){
				wt[i]=(lint)wt[i-1]*t%mod;
			}
		}
	}_init_;

	void ntt(int *v,const int len,bool f){
		static int rev[N];
		for(int i=0; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1)*(len>>1);
			if(i<rev[i]) std::swap(v[i],v[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=N/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int w=0,k=0; k<i; ++k,w+=t){
					lint p1=v[j+k],p2=(lint)v[j+k+i]*wt[w];
					v[j+k]=(p1+p2)%mod;
					v[j+k+i]=(p1-p2)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			v[i]=(v[i]+mod)%mod;
		}
		if(f==0) return;
		std::reverse(v+1,v+len);
		int t=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			v[i]=(lint)v[i]*t%mod;
		}
	}

	int* rm_mul(int *&a,const int la,int *&b,const int lb){
		static int p1[N],p2[N];
		int len=la+lb+1,*c=new int[len];
		while(len!=(len&-len)) len+=(len&-len);
		memset(p1,0,len*sizeof(p1[0]));
		memset(p2,0,len*sizeof(p2[0]));
		memcpy(p1,a,(la+1)*sizeof(p1[0]));
		memcpy(p2,b,(lb+1)*sizeof(p2[0]));
		delete[] a,delete[] b;
		a=b=0;
		ntt(p1,len,0);
		ntt(p2,len,0);
		for(int i=0; i<len; ++i){
			p1[i]=(lint)p1[i]*p2[i]%mod;
		}
		ntt(p1,len,1);
		memcpy(c,p1,(la+lb+1)*sizeof(c[0]));
		return c;
	}
}

namespace G{
	int cnt=1,fir[N],sz[N<<1],dp[N<<1],sdp[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	inline bool cmp_sz(const int a,const int b){
		return sz[a]<sz[b];
	}
	void apl(int *v,const int n,const int sz){
		for(int i=n; i; --i)
			v[i]=(v[i]+(lint)v[i-1]*sz)%mod;
	}
	void div(int *v,const int n,const int sz){
		for(int i=1; i<=n; ++i)
			v[i]=(v[i]-(lint)v[i-1]*sz)%mod;
	}

	void dfs_dp(const int x,const int e){
		static int buk[N],*pol[N];
		sz[e]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(i!=(e^1)) dfs_dp(y,i),sz[e]+=sz[i];
		}
		sz[e^1]=n-sz[e];
		int top=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			buk[top++]=i;
			int x=top-1;
			if(pol[x]) delete[] pol[x];
			pol[x]=new int[2];
			pol[x][0]=1,pol[x][1]=sz[i];
		}
		for(int i=1; i<top; i<<=1){
			for(int j=0; j<top; j+=i<<1){
				if(j+i<top)
					pol[j]=P::rm_mul(pol[j],i,pol[j+i],std::min(i,top-j-i));
			}
		}
		assert(pol[0]);
		std::sort(buk,buk+top,cmp_sz);
		for(int res=0,i=0; i<top; ++i){
			if(i==0||sz[buk[i]]!=sz[buk[i-1]]){
				if(i) apl(pol[0],top,sz[buk[i-1]]);
				div(pol[0],top,sz[buk[i]]);
				res=0;
				for(int j=0; j<=std::min(q,top); ++j){
					res=(res+(lint)fac[q]*ifac[q-j]%mod*pol[0][j])%mod;
				}
				res=(res+mod)%mod;
			}
			dp[buk[i]^1]=res;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) sdp[x]=((lint)sdp[x]+dp[i]+sdp[eg[i].to])%mod;
		}
	}

	void dfs_ans1(const int x,const int e){
		//无祖先后代关系
		static int wgt;
		if(e) ans=(ans+(lint)wgt*dp[e])%mod;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i==(e^1)) continue;
			int y=eg[i].to,dlt=((lint)sdp[x]-sdp[y]-dp[i])%mod;
			wgt=(wgt+dlt)%mod;
			dfs_ans1(y,i);
			wgt=(wgt-dlt)%mod;
		}
	}

	void dfs_ans2(const int x,const int e){
		//祖先后代关系
		static int wgt;
		if(e){
			wgt=(wgt+dp[e^1])%mod;
			ans=(ans+(lint)wgt*dp[e])%mod;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(i!=(e^1)) dfs_ans2(eg[i].to,i);
		}
		wgt=(wgt-dp[e^1])%mod;
	}
}

int main(){
	n=nxi(),q=nxi();
	if(q==1){
		printf("%lld\n",(lint)n*(n-1)%mod*fpow(2,mod-2)%mod);
		return 0;
	}
	init();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_dp(1,0);
	G::dfs_ans1(1,0);
	ans=(lint)ans*ifac[2]%mod;//inv2
	G::dfs_ans2(1,0);
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
