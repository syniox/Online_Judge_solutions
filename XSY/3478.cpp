#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=5e5+5;
int n,q,qx,qy;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace T{
	int x,v;
	struct node{
		lint mn,mx,s;
		inline void set(const int v){
			s=v;
			mn=std::min(0,v);
			mx=std::max(0,v);
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].s=tr[ls].s+tr[rs].s;
		tr[k].mn=std::min(tr[ls].mn,tr[ls].s+tr[rs].mn);
		tr[k].mx=std::max(tr[ls].mx,tr[ls].s+tr[rs].mx);
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].set(l&1?nxi():-nxi());
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].set(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	int ask_t(const int l,const int r,const int v){
		if(l==r){
			return std::max(0,std::min(qx+qy,v+(int)tr[idx(l,r)].s));
		}
		const int mid=(l+r)>>1;
		const int rs=idx(mid+1,r);
		if(tr[rs].mx-tr[rs].mn>qx+qy){
			return ask_t(mid+1,r,0);
		}
		lint res=ask_t(l,mid,v);
		apx(res,-tr[rs].mn);
		apn(res,-tr[rs].mx+qx+qy);
		return res+tr[rs].s;
	}

	inline void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	qx=nxi(),qy=nxi();
	T::build(1,n);
	for(int i=1; i<=q; ++i){
		const int op=nxi(),x=nxi();
		switch(op){
			case 1: qx=x; break;
			case 2: qy=x; break;
			case 3: T::mod(x,x&1?nxi():-nxi()); break;
		}
		printf("%d\n",T::ask_t(1,n,qx));
	}
	return 0;
}
