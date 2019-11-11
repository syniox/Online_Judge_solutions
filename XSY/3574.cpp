#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,val[N];

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

namespace D{
	int cnt,v[N<<1];
	inline void insert(const int x){
		v[++cnt]=x;
	}
	inline void build(){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+cnt+1,x)-v;
	}
}

namespace T{
	int x,y,v;
	struct node{
		int s,dlt,min,ncnt;
		inline void getpsh(const int d){
			dlt+=d,min+=d;
			s=min==-1?ncnt:0;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	
	void psh(const int l,const int r){
		int &d=tr[idx(l,r)].dlt,mid=(l+r)>>1;
		if(l==r||!d) return;
		tr[idx(l,mid)].getpsh(d);
		tr[idx(mid+1,r)].getpsh(d);
		d=0;
	}

	void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		node &k=tr[idx(l,r)],ls=tr[idx(l,mid)],rs=tr[idx(mid+1,r)];
		k.min=std::min(ls.min,rs.min);
		k.ncnt=0;
		if(ls.min==k.min) k.ncnt+=ls.ncnt;
		if(rs.min==k.min) k.ncnt+=rs.ncnt;
		k.s=ls.s+rs.s;
	}

	void build(const int l,const int r){
		tr[idx(l,r)].ncnt=r-l+1;
		if(l==r) return;
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getpsh(v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	inline void add(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,n);
	}

	inline int ask(){
		return tr[idx(1,n)].s;
	}
}

lint solve(){
	static int st_n[N],st_x[N],lst[N];//朝向
	int top_n=0,top_x=0;
	lint ans=0;
	for(int i=1; i<=n; ++i){
		for(; top_n&&val[st_n[top_n]]>=val[i]; --top_n){
			T::add(st_n[top_n-1]+1,st_n[top_n],val[st_n[top_n]]-val[i]);
		}
		st_n[++top_n]=i;
		for(; top_x&&val[st_x[top_x]]<=val[i]; --top_x){
			T::add(st_x[top_x-1]+1,st_x[top_x],val[i]-val[st_x[top_x]]);
		}
		st_x[++top_x]=i;
		T::add(lst[val[i]]+1,i,-1);
		lst[val[i]]=i;
		ans+=T::ask();
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		D::insert(val[i]=nxi());
		D::insert(val[i]+1);
	}
	T::build(1,n);
	D::build();
	for(int i=1; i<=n; ++i){
		val[i]=D::ask(val[i]);
	}
	printf("%lld\n",solve());
	return 0;
}
