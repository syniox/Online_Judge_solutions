#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>
typedef long long lint;
const int N=2e5+5;
const int E=3e5+5;
int n,m,tot,val[N],ew[E],ev[E];
std::map <int,int> ebuk[N];

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

int get_eid(int x,int y){
	if(x>y) std::swap(x,y);
	return ebuk[x][y];
}

namespace T{
	int tgt,cnt=1,fir[N*2],*sbuk[N*2],*seid[N*2];
	lint lim,dp[N*2];
	bool vld;
	struct edge{
		int to,nx;
	}eg[N*4];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
		eg[++cnt]=(edge){a,fir[b]};
		fir[b]=cnt;
	}

	void dfs_eid(const int x,const int f){
		int cnt=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to!=f) ++cnt,dfs_eid(eg[i].to,x);
		}
		if(x<=n) return;
		int *buk=sbuk[x]=new int[cnt+1];
		int *eid=seid[x]=new int[cnt+1];
		cnt=0;
		for(int b=0,i=fir[x]; i; i=eg[i].nx){
			if(b) buk[++cnt]=eg[i].to;
			b|=eg[i].to==f;
		}
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to==f) break;
			buk[++cnt]=eg[i].to;
		}
		buk[0]=buk[cnt+1]=f;
		for(int i=0; i<=cnt; ++i){
			eid[i]=get_eid(buk[i],buk[i+1]);
		}
	}

	void dfs_ans(const int x,const int f){
		static lint la[N],ra[N];//此时断开最大深度
		static lint lx[N],rx[N];//连带到根最大深度
		static lint lp[N],rp[N];//区间内最大深度
		if(!vld) return;
		int *buk=sbuk[x],*eid=seid[x],cnt=0;
		for(int i=fir[x]; i; i=eg[i].nx){
			if(eg[i].to!=f) ++cnt,dfs_ans(eg[i].to,x);
		}
		if(x<=n){
			lint x1=0,x2=0;
			for(int i=fir[x]; i; i=eg[i].nx){
				if(eg[i].to==f) continue;
				lint tmp=dp[eg[i].to];
				if(tmp>x1) std::swap(x1,tmp);
				if(tmp>x2) std::swap(x2,tmp);
			}
			dp[x]=x1;
			vld&=x1+x2<=lim;
		}else if(cnt==1){
			dp[x]=dp[buk[1]]+ew[eid[1]];
		}else{
			//get lx rx
			memset(la,0,(cnt+2)*sizeof(lint));
			memset(lx,0,(cnt+2)*sizeof(lint));
			memset(lp,0,(cnt+2)*sizeof(lint));
			memset(ra,0,(cnt+2)*sizeof(lint));
			memset(rx,0,(cnt+2)*sizeof(lint));
			memset(rp,0,(cnt+2)*sizeof(lint));
			lint xcf=-1e15;
			for(int i=0; i<=cnt; ++i){
				lx[i+1]=la[i+1]=lx[i]+ew[eid[i]];
				lint tmp=dp[buk[i]]-lx[i];
				lx[i]+=dp[buk[i]];
				apx(lp[i],xcf+lx[i]);
				lp[i+1]=lp[i];
				if(i) apx(lx[i],lx[i-1]);
				la[i]+=ev[eid[i]]+val[buk[i]];
				apx(lp[i],xcf+la[i]);
				apx(la[i],lx[i]);
				apx(xcf,tmp);
			}
			xcf=-1e15;
			for(int i=cnt+1; i>=1; --i){
				rx[i-1]=ra[i-1]=rx[i]+ew[eid[i-1]];
				lint tmp=dp[buk[i]]-rx[i];
				rx[i]+=dp[buk[i]];
				apx(rp[i],xcf+rx[i]);
				rp[i-1]=rp[i];
				if(i<=cnt) apx(rx[i],rx[i+1]);
				ra[i]+=ev[eid[i-1]]+val[buk[i]];
				apx(rp[i],xcf+ra[i]);
				apx(ra[i],rx[i]);
				apx(xcf,tmp);
			}
			lint s=1e16;
			for(int i=0; i<=cnt; ++i){
				if(lp[i]>lim||rp[i+1]>lim||la[i]+ra[i+1]>lim) continue;
				apn(s,std::max(la[i],ra[i+1]));
			}
			dp[x]=s;
			if(s==1e16) vld=0;
		}
	}

	lint solve(){
		dfs_eid(1,0);
		lint l=1,r=2e14;
		while(l<r){
			lim=(l+r)>>1;
			vld=1;
			memset(dp,0,sizeof(dp));
			if(dfs_ans(1,0),vld) r=lim;
			else l=lim+1;
		}
		return l;
	}
}

namespace G{
	int cnt=1,fir[N],dfn[N],low[N];
	struct edge{
		int to,nx;
	}eg[E*2];
	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}
	void tarjan(const int x){
		static int cnd,top,stk[N];
		stk[++top]=x;
		low[x]=dfn[x]=++cnd;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!dfn[y]){ 
				tarjan(y);
				if(low[y]>=dfn[x]){
					++tot;
					for(;;){
						T::add(tot,stk[top]);
						if(stk[top--]==y) break;
					}
					T::add(tot,x);
				}
				apn(low[x],low[y]);
			}
			else apn(low[x],dfn[y]);
		}
	}
}

int main(){
	tot=n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i)
		val[i]=nxi();
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi(),w=nxi(),v=nxi();
		G::add(b,a),G::add(a,b);
		ebuk[std::min(a,b)][std::max(a,b)]=i;
		ew[i]=w,ev[i]=v;
	}
	G::tarjan(1);
	printf("%lld\n",T::solve());
	return 0;
}
