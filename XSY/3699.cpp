#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
#include <bitset>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int ans,n,m,ty;
int cnp,prm[N],buk[N],fp[N];//fp: 最小能被整除的质数

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
	int cnt,fir[N];
	struct edge{
		int to,nx;
	}eg[N<<2];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
}

namespace S{
	using namespace G;
	int curgcd,cnd,cnf,bel[N],dfn[N],low[N],dep[N];
	bool vis[N];
	void init(){
		static bool npr[N];
		for(int i=2; i<=n; ++i){
			if(!npr[i]) fp[prm[++cnp]=i]=i;
			for(int j=1; j<=cnp&&i*prm[j]<=n; ++j){
				npr[i*prm[j]]=1;
				fp[i*prm[j]]=prm[j];
				if(i%prm[j]==0) break;
			}
		}
	}
	void applylcm(const int x){
		for(int i=x; i>1; ){
			int cnt=1;
			for(; fp[i]==fp[i/fp[i]]; ++cnt,i/=fp[i]);
			apx(buk[fp[i]],cnt);
			i/=fp[i];
		}
	}
	void tarjan(const int x){
		static int top,stk[N];
		low[x]=dfn[x]=++cnd;
		stk[++top]=x;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(bel[y]) continue;
			if(!dfn[y]) tarjan(y);
			apn(low[x],low[y]);
		}
		if(dfn[x]!=low[x]) return;
		++cnf;
		for(int j=stk[top--]; ; j=stk[top--]){
			bel[j]=cnf;
			if(j==x) break;
		}
	}
	void dfs_cir(const int x){
		dfn[x]=low[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(bel[y]!=bel[x]) continue;
			if(dfn[y]){
				if(dfn[y]<dfn[x]){
					apn(low[x],low[y]);//dfn or low?
					curgcd=gcd(curgcd,abs(dep[x]-dep[y]+1));
				}
				if(dfn[y]>dfn[x])
					curgcd=gcd(curgcd,abs(dep[y]-dep[x]-1));
				continue;
			}
			dep[y]=dep[x]+1;
			dfs_cir(y);
			apn(low[x],low[y]);
		}
	}
	void main(){
		init();
		for(int i=1; i<=n; ++i){
			if(!bel[i]) tarjan(i);
		}
		memset(dfn,0,sizeof(dfn));
		cnd=0;
		for(int i=1; i<=n; ++i){
			if(vis[bel[i]]) continue;
			vis[bel[i]]=1;
			curgcd=0,dfs_cir(i);
			if(curgcd) applylcm(curgcd);
			if(curgcd) eprintf("%d: %d\n",i,curgcd);
		}
		ans=1;
		for(int i=2; i<=n; ++i){
			for(int j=buk[i]; j--;) ans=(lint)ans*i%mod;
		}
	}
}

namespace B{
	using namespace G;
	const int N=205;
	struct mtrx{
		std::bitset <N> v[N];
		inline void init(){
			for(int i=0; i<n; ++i) v[i][i]=1;
		}
		friend bool operator == (const mtrx &a,const mtrx &b){
			for(int i=0; i<n; ++i){
				if(a.v[i]!=b.v[i]) return 0;
			}
			return 1;
		}
		friend mtrx operator * (const mtrx &a,const mtrx &b){
			mtrx c;
			memset(c.v,0,sizeof(c.v));
			for(int i=0; i<n; ++i){
				for(int j=0; j<n; ++j){
					if(a.v[i][j]) c.v[i]|=b.v[j];
				}
			}
			return c;
		}
	}base[50],nxt,cur;

	template <class T> inline T fpow(T x,int t){
		T ans;
		ans.init();
		for(; t; x=x*x,t>>=1){
			if(t&1) ans=ans*x;
		}
		return ans;
	}

	void main(){
		for(int x=1; x<=n; ++x){
			for(int i=fir[x]; i; i=eg[i].nx)
				base[0].v[x-1][eg[i].to-1]=1;
		}
		mtrx nxt=base[0];
		for(int i=2; i<=n; ++i){
			if(!buk[i]) continue;
			int f=1;
			for(; buk[i]--; f*=i);
			nxt=fpow(nxt,f);
		}
		int cnt=0;
		for(; ; ++cnt){
			if(base[cnt]*nxt==base[cnt]) break;
			base[cnt+1]=base[cnt]*base[cnt];
		}
		if(cnt==0){
			printf("1 %d\n",ans);
			return;
		}
		cur=base[--cnt];
		lint res=1ll<<cnt;
		for(--cnt; ~cnt; --cnt){
			mtrx tmp=cur*base[cnt];
			if(!(tmp*nxt==tmp)) res+=1ll<<cnt,cur=tmp;
		}
		printf("%lld %d\n",(res+1)%mod,ans);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi(),ty=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
	}
	S::main();
	if(!ty) printf("%d\n",ans);
	else B::main();
	return 0;
}
