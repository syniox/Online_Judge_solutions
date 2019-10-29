#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2335;
int n,mod,val[N],cnt[N];
int *plst[N],llst[N];

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

class _disc{
	public:
		int tot,mp[N];
		inline void add(const int v){
			mp[++tot]=v;
		}
		inline void build(){
			std::sort(mp+1,mp+tot+1);
			tot=std::unique(mp+1,mp+tot+1)-mp-1;
		}
		inline int ask(const int v){
			return std::lower_bound(mp+1,mp+tot+1,v)-mp;
		}
}dv,dm;

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi(),mod=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		if(val[i]%mod==0){
			--i,--n;
			continue;
		}
		dv.add(val[i]);
		dm.add(fpow(val[i],mod-2));
	}
	dv.build();
	dm.build();
	for(int i=1; i<=n; ++i){
		++cnt[dv.ask(val[i])];
	}
	for(int i=1; i<=dv.tot; ++i){
		++llst[dm.ask(fpow(dv.mp[i],mod-2))];
	}
	for(int i=1; i<=dm.tot; ++i){
		plst[i]=new int[llst[i]+1];
	}
	memset(llst,0,sizeof(llst));
	for(int i=1; i<=dv.tot; ++i){
		int p=dm.ask(fpow(dv.mp[i],mod-2));
		plst[p][++llst[p]]=dv.mp[i];
	}
	int ans=0;
	for(int i=1; i<=dv.tot; ++i){
		for(int j=i+(cnt[i]==1); j<=dv.tot; ++j){
			int res=(lint)dv.mp[i]*dv.mp[j]%mod,p=dm.ask(res);
			if(!res||dm.mp[p]!=res) continue;
			int tmp=std::lower_bound(plst[p]+1,plst[p]+llst[p]+1,dv.mp[j])-plst[p];
			ans+=(llst[p]-tmp+1)-(plst[p][tmp]==dv.mp[j]&&cnt[j]<=1+(i==j));
		}
	}
	printf("%d\n",ans);
	return 0;
}
