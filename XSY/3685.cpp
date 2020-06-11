#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cstdlib>
typedef long long lint;
const int N=5e5+5;
int n,m,val[N];

namespace utils{
#define eprintf(fmt,...) fprintf(stderr,fmt,__VA_ARGS__)
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
	int rt,cnt;
	struct node{
		int w,ls,rs,sz,v,tag;//w: 大根堆
		lint sum;
		void getpsh(const int t){
			v+=t,tag+=t;
			sum+=(lint)sz*t;
		}
	}tr[N];

	inline void upd(const int k){
		node *ls=tr+tr[k].ls,*rs=tr+tr[k].rs;
		tr[k].sz=ls->sz+rs->sz+1;
		tr[k].sum=tr[k].v+ls->sum+rs->sum;
	}
	inline void psh(const int k){
		int &t=tr[k].tag;
		if(!t) return;
		if(tr[k].ls) tr[tr[k].ls].getpsh(t);
		if(tr[k].rs) tr[tr[k].rs].getpsh(t);
		t=0;
	}
	inline int getm(int k,const bool f){
		for(int p=f?tr[k].rs:tr[k].ls; p; k=p,p=f?tr[k].rs:tr[k].ls)
			psh(k);
		return tr[k].v;
	}

	void build_t(int &k,const int l,const int r){
		for(int i=l; i<=r; ++i){
			if(tr[i].w>tr[k].w) k=i;
		}
		if(k>l) build_t(tr[k].ls,l,k-1);
		if(k<r) build_t(tr[k].rs,k+1,r);
		upd(k);
	}
	//<=v的在左
	void split_v(const int k,int &lh,int &rh,const int v){
		if(!k){
			lh=rh=0; return;
		}
		psh(k);
		if(tr[k].v<=v)
			lh=k,split_v(tr[k].rs,tr[k].rs,rh,v);
		else
			rh=k,split_v(tr[k].ls,lh,tr[k].ls,v);
		upd(k);
	}
	//总共还需多少在左边
	void split_s(const int k,int &lh,int &rh,const int sz){
		if(!k){
			lh=rh=0; return;
		}
		psh(k);
		if(tr[tr[k].ls].sz+1<=sz)
			lh=k,split_s(tr[k].rs,tr[k].rs,rh,sz-tr[tr[k].ls].sz-1);
		else
			rh=k,split_s(tr[k].ls,lh,tr[k].ls,sz);
		upd(k);
	}
	void merge(int &k,const int l,const int r){
		if(!l||!r){
			k=l+r; return;
		}
		if(tr[l].w>tr[r].w)
			psh(k=l),merge(tr[k].rs,tr[k].rs,r);
		else
			psh(k=r),merge(tr[k].ls,l,tr[k].ls);
		upd(k);
	}

	void build(){
		for(int i=1; i<=n; ++i){
			tr[i].w=rand();
			tr[i].v=tr[i].sum=val[i];
			tr[i].sz=1;
		}
		build_t(rt,1,n);
	}
	lint qry_and_set(const int q){
		int r1,r2,m1,m2;
		if(q==n){
			lint ans=tr[rt].sum;
			tr[rt].getpsh(-1);
			return ans;
		}
		split_s(rt,r1,r2,n-q);
		lint ans=tr[r2].sum;
		tr[r2].getpsh(-1);
		m1=getm(r1,1),m2=getm(r2,0);
		if(m1<=m2){
			merge(rt,r1,r2);
		}else{
			assert(m1==m2+1);
			int r3,r4;
			split_v(r1,r1,r3,m2);
			split_v(r2,r4,r2,m2);
			merge(r1,r1,r4);
			merge(r2,r3,r2);
			merge(rt,r1,r2);
		}
		return ans;
	}
}

int main(){
	srand(19260817);
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	std::sort(val+1,val+n+1);
	T::build();
	m=nxi();
	lint ans=0;
	while(m--){
		ans+=T::qry_and_set(nxi());
	}
	printf("%lld\n",ans);
	return 0;
}
