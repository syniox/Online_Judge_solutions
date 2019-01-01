#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cassert>
const int N=2e5+2;
typedef long long lint;
int n,m,q,val[N];
lint ans[N];
struct query{
	int l,r,v,id;
	friend bool cmp_q_v(const query &a,const query &b){
		return a.v<b.v;
	}
}qry[N];
struct zero_pt{
	int pos,v;
	friend bool cmp_z_v(const zero_pt &a,const zero_pt &b){
		return a.v<b.v;
	}
}pt0[N];

bool cmp_q_v(const query &a,const query &b);
bool cmp_z_v(const zero_pt &a,const zero_pt &b);

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,v,tick,tag[N],lk[N];
	struct node{
		int f,min,max;
		lint s;
		inline void get_psh(int v,int l,int r){
			f=v,s=(r-l+1)*(lint)f;
			min=max=v;
		}
		inline bool same(){
			return min==max;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		int k=idx(l,r),ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].s=tr[ls].s+tr[rs].s;
		tr[k].min=std::min(tr[ls].min,tr[rs].min);
		tr[k].max=std::max(tr[ls].max,tr[rs].max);
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(l==r||!tr[k].f) return;
		tr[idx(l,mid)].get_psh(tr[k].f,l,mid);
		tr[idx(mid+1,r)].get_psh(tr[k].f,mid+1,r);
		tr[k].f=0;
	}

	void build(const int l,const int r){
		tr[idx(l,r)]=(node){0,n+1,n+1,(lint)(r-l+1)*(n+1)};
		if(l==r) return;
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
	}

	void mod_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y){
			if(tr[idx(l,r)].min>v){
				tr[idx(l,r)].get_psh(v,l,r);
				return;
			}
			if(tr[idx(l,r)].max<v) return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	lint ask_s_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y) return tr[idx(l,r)].s;
		lint ans=0,mid=(l+r)>>1;
		if(x<=mid) ans+=ask_s_t(l,mid);
		if(y>mid) ans+=ask_s_t(mid+1,r);
		return ans;
	}

	inline void mod(const int l,const int r,const int v){
		assert(l<=r);
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n);
	}

	inline lint ask_s(const int l,const int r){
		if(l>r) return 0;
		T::x=l,T::y=r;
		return ask_s_t(1,n);
	}

	inline int get_lk(const int x){
		if(x>n) return n+1;
		if(tag[x]==tick) return lk[x];
		tag[x]=tick;
		return lk[x]=ask_s(x,x);
	}

	inline void calc(const int l,const int r){
		int k=idx(l,r),to=tr[k].min+1;
		tr[k].f=get_lk(to);
		tr[k].min=tr[k].max=tr[k].f;
		tr[k].s=(lint)(r-l+1)*tr[k].f;
	}

	void rebuild(const int l,const int r){
		if(l==1&&r==n) ++tick;
		if(l!=r) psh(l,r);
		if(tr[idx(l,r)].same()){
			calc(l,r);
			return;
		}
		const int mid=(l+r)>>1;
		rebuild(l,mid);
		rebuild(mid+1,r);
		upd(l,r);
	}
}

inline lint get_s(const int x,const int y){
	int l=x-1,r=y,mid;
	while(l!=r){
		mid=(l+r+1)>>1;
		if(T::ask_s(mid,mid)<=y) l=mid;
		else r=mid-1;
	}
	if(l<x) return 0;
	return (lint)(l-x+1)*(y+1)-T::ask_s(x,l);
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		pt0[i]=(zero_pt){i,val[i]};
	}
	for(int i=1; i<=q; ++i){
		qry[i].id=i;
		qry[i].l=nxi(),qry[i].r=nxi(),qry[i].v=nxi();
	}
	std::sort(qry+1,qry+q+1,cmp_q_v);
	std::sort(pt0+1,pt0+n+1,cmp_z_v);
	T::build(1,n);
	for(int i=1,j=1,k=1; i<=q; ++i){
		for(; j<=qry[i].v; ++j){
			T::rebuild(1,n);
			for(; k<=n&&pt0[k].v<=j; ++k){
				T::mod(1,pt0[k].pos,pt0[k].pos);
			}
		}
		ans[qry[i].id]=get_s(qry[i].l,qry[i].r);
	}
	for(int i=1; i<=q; ++i){
		printf("%lld\n",ans[i]);
	}
	return 0;
}
