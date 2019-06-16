#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=8005;
const int M=57984;
const int mod=950009857;
const int W=7;
int n,m,val[N],*dp[N],ans[M<<1];
lint pans[M];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace P{
	const int L=262144;
	int wt[L];
	struct _init{
		_init(){
			int w=fpow(W,(mod-1)/L);
			wt[0]=1;
			for(int i=1; i<L; ++i){
				wt[i]=(lint)wt[i-1]*w%mod;
			}
		}
	}init;

	void ntt(int *v,const int len,const bool f){
		static int rev[L];
		assert((len&-len)==len);
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(v[i],v[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=L/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int k=0,w=0; k<i; ++k,w+=t){
					lint p=(lint)v[j+k+i]*wt[w];
					v[j+k+i]=(v[j+k]-p)%mod;
					v[j+k]=(v[j+k]+p)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			v[i]=(v[i]+mod)%mod;
		}
		if(f==0) return;
		std::reverse(v+1,v+len);
		int wgt=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			v[i]=(lint)v[i]*wgt%mod;
		}
	}

	void pls1(int *v,int pos,const int len){
		static int lst_len,buk[M];
		assert(len);
		if(pos==0){
			for(int i=0; i<len; ++i){
				v[i]=(v[i]+1)%mod;
			}
			return;
		}
		if(lst_len!=len){
			int t=fpow(W,(mod-1)/len);
			buk[0]=1;
			for(int i=1; i<len; ++i){
				buk[i]=(lint)buk[i-1]*t%mod;
			}
			lst_len=len;
		}
		for(int i=0,w=0; i<len; ++i,w=w+pos<len?w+pos:w+pos-len){
			v[i]=(v[i]+(lint)buk[w])%mod;
		}
	}

	void pcrs(int *a,int *b,int len,int *c=0){
		if(c==0) c=a;
		for(int i=0; i<len; ++i){
			c[i]=(lint)a[i]*b[i]%mod;
		}
	}

	void bstein(int *v,const int len){
		//DFT only
		static int a[L],b[L];
		assert((mod-1)%len==0);
		int san_l=1,w=fpow(W,(mod-1)/len>>1);
		while(san_l<len*3) san_l<<=1;
		memset(a,0,san_l*sizeof(int));
		memset(b,0,san_l*sizeof(int));
		b[0]=1,a[0]=v[0];
		for(int i=1; i<len; ++i){
			int res=fpow(w,(lint)i*i);
			a[i]=(lint)res*v[i]%mod;
			b[i]=b[san_l-i]=fpow(res,mod-2);
		}
		ntt(b,san_l,0);
		ntt(a,san_l,0);
		for(int i=0; i<san_l; ++i){
			a[i]=(lint)a[i]*b[i]%mod;
		}
		ntt(a,san_l,1);
		for(int i=0; i<len; ++i){
			v[i]=(lint)fpow(w,(lint)i*i)*a[i]%mod;
		}
	}

	void idft(int *v,const int len){
		bstein(v,len);
		std::reverse(v+1,v+len);
		int wgt=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			v[i]=(lint)v[i]*wgt%mod;
		}
	}
}

namespace G{
	int cnt,fir[N],fa[N],son[N],sz[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void dfs_son(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]) continue;
			fa[y]=x;
			dfs_son(y);
			if(sz[y]>sz[son[x]]) son[x]=y;
			sz[x]+=sz[y];
		}
	}

	void dfs_ans(const int x){
		static int tmp[M];
		if(!son[x]){
			dp[x]=new int[m];
			memset(dp[x],0,m*sizeof(int));
			P::pls1(dp[x],val[x],m);
			for(int i=0; i<m; ++i){
				pans[i]+=dp[x][i];
			}
			return;
		}
		dfs_ans(son[x]);
		memset(tmp,0,m*sizeof(int));
		P::pls1(tmp,val[x],m);
		dp[x]=dp[son[x]];
		dp[son[x]]=0;
		for(int i=0; i<m; ++i){
			dp[x][i]=(lint)(dp[x][i]+1)*tmp[i]%mod;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa[x]||y==son[x]) continue;
			dfs_ans(y);
			for(int j=0; j<m; ++j){
				dp[x][j]=(lint)dp[x][j]*(dp[y][j]+1)%mod;
			}
			delete[] dp[y];
			dp[y]=0;
		}
		for(int i=0; i<m; ++i){
			pans[i]+=dp[x][i];
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_son(1);
	G::dfs_ans(1);
	for(int i=0; i<m; ++i){
		ans[i]=pans[i]%mod;
	}
	P::idft(ans,m);
	for(int i=0; i<m; ++i){
		printf("%d ",ans[i]);
	}
	puts("");
	return 0;
}
