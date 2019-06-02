#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=51;
const int mod=1e9+7;
int n,m,q,fac[N<<2],ifac[N<<2];

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

int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

inline void init_C(){
	const int N=::N<<2;
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	assert(x<201);
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int polya(const int x){
	lint ans=0;
	for(int i=1; i<=x; ++i){
		ans+=fpow(q,gcd(x,i));
	}
	ans%=mod;
	return (lint)ans*fpow(x,mod-2)%mod;
}

namespace G{
	int cnt,ans=1,cscc,con_e,fir[N],bel[N],dfn[N];
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	void tarjan(const int x,const int fa){
		static int cnd,top,low[N],stk[N];
		stk[++top]=x;
		dfn[x]=low[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(y==fa) continue;
			if(dfn[y]){
				apn(low[x],dfn[y]);
				continue;
			}
			tarjan(y,x);
			if(low[y]<dfn[x]){
				apn(low[x],low[y]);
				continue;
			}
			++cscc;
			int cnt_p=1,cnt_e=0;
			for(int i=top; stk[i]!=x; --i){
				bel[stk[i]]=cscc;
			}
			bel[x]=cscc;
			//printf("%d ",x);
			for(int j=stk[top--]; ; j=stk[top--]){
				//printf("%d ",j);
				++cnt_p;
				for(int k=fir[j]; k; k=eg[k].nx){
					int l=eg[k].to;
					//printf("%d->%d: %d\n",j,l,(l>j||l==x)&&bel[l]==bel[j]);
					cnt_e+=(l>j||l==x)&&bel[l]==bel[j];
				}
				if(j==y) break;
			}
			/*
			puts("");
			printf("cnt_p: %d,cnt_e: %d\n",cnt_p,cnt_e);
			*/
			if(cnt_p>cnt_e){
				assert(cnt_e<=1);
				ans=(lint)ans*fpow(q,cnt_e)%mod;
			}
			else if(cnt_p==cnt_e){
				ans=(lint)ans*polya(cnt_e)%mod;
			}
			else if(cnt_p<cnt_e){
				ans=(lint)ans*C(cnt_e+q-1,q-1)%mod;
			}
			else assert(0);
			bel[x]=0;
			//puts("---");
		}
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	init_C();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	for(int i=1; i<=n; ++i){
		if(!G::dfn[i]) G::tarjan(i,0);
	}
	printf("%d\n",G::ans);
	return 0;
}
