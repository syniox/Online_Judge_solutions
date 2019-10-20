#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e6+5;
const int mod=998244353;
int n,tot,mp[N<<1];
struct seg{
	int l,r;
	friend bool operator < (const seg &a,const seg &b){
		return a.l<b.l;
	}
}sg[N];

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

namespace T{
	int tick,tag[N<<1],tr[N<<1];
	inline void upd(const int x){
		if(tag[x]!=tick) tag[x]=tick,tr[x]=0;
	}
	inline void unset(){
		++tick;
	}
	inline int ask(int x){
		++x;
		lint ans=0;
		for(; x; x-=x&-x) upd(x),ans+=tr[x];
		return (int)(ans%mod);
	}
	inline void add(int x,int v){
		++x;
		for(; x<=tot+1; x+=x&-x){
			upd(x),tr[x]=(tr[x]+v)%mod;
		}
	}
}

namespace M{
	int tick,tag[N],val[N];
	inline void unset(){
		++tick;
	}
	inline int ask(const int x){
		return tag[x]==tick?val[x]:0;
	}
	inline void set(const int x,const int v){
		tag[x]=tick,val[x]=v;
	}
}

int main(){
#ifdef LOCAL
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		sg[i].l=nxi();
		sg[i].r=nxi();
		mp[(i<<1)-1]=sg[i].l;
		mp[(i<<1)]=sg[i].r;
	}
	std::sort(mp+1,mp+(n<<1)+1);
	tot=std::unique(mp+1,mp+(n<<1)+1)-mp-1;
	for(int i=1; i<=n; ++i){
		sg[i].l=std::lower_bound(mp+1,mp+tot+1,sg[i].l)-mp;
		sg[i].r=std::lower_bound(mp+1,mp+tot+1,sg[i].r)-mp;
	}
	std::sort(sg+1,sg+n+1);
	T::add(0,1);
	M::set(0,1);
	for(int i=1; i<=n; ++i){
		int res=T::ask(sg[i].l);
		if(sg[i].l<sg[i-1].r)
			M::unset(),T::unset();
		T::add(sg[i-1].r,res-M::ask(i-1));
		M::set(i-1,res);
	}
	int res=(T::ask(tot)+mod)%mod;
	printf("%d\n",(res<<1)%mod);
	return 0;
}

