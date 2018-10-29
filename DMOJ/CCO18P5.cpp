#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e6+5;
int n,m,q,hx[N];
struct node{
	int v,pos;
	bool operator < (const node &b) const {
		return v==b.v?pos<b.pos:v<b.v;
	}
};

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,v;
	struct tree{
		int s;
		node v;//return left one if have same value
	}tr[N<<1];
	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		const int k=idx(l,r),ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].v=std::max(tr[ls].v,tr[rs].v);
		tr[k].s=std::max(tr[ls].s,tr[rs].s);
	}
	void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k].v=(node){hx[l],l};
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}
	void mod_v_t(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k].v.v=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_v_t(l,mid);
		else mod_v_t(mid+1,r);
		upd(l,r);
	}
	void mod_s_t(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k].s=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_s_t(l,mid);
		else mod_s_t(mid+1,r);
		upd(l,r);
	}
	node ask_v_t(const int l,const int r){
		const int k=idx(l,r);
		if(l>=x&&r<=y) return tr[k].v;
		const int mid=(l+r)>>1;
		node ans=(node){(int)-1e9,0};
		if(x<=mid) apx(ans,ask_v_t(l,mid));
		if(y>mid) apx(ans,ask_v_t(mid+1,r));
		return ans;
	}
	inline void mod_s(const int x,const int v){
		T::x=x,T::v=v;
		mod_s_t(1,n);
	}
	inline void mod_v(const int x,const int v){
		T::x=x,T::v=v;
		mod_v_t(1,n);
	}
	inline node ask_v(const int x,const int y){
		if(x>y) return (node){(int)-1e8,0};
		T::x=x,T::y=y;
		return ask_v_t(1,n);
	}
}

inline node get_v(const int x){
	const node max_l=T::ask_v(std::max(x-m+1,1),x-1);
	const node max_r=T::ask_v(x+1,std::min(x+m-1,n));
	return std::max(max_l,max_r);
}

inline void upd(const node &x){
	if(x.pos){
		const node v=get_v(x.pos);
		if(v<x) T::mod_s(x.pos,x.v+v.v);
		else T::mod_s(x.pos,-1e8);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	T::build(1,n);
	for(int i=1;i<=n;++i){
		const node max_v=get_v(i);
		if(max_v<(node){hx[i],i}){
			T::tr[T::idx(i,i)].s=hx[i]+max_v.v;
		}
		else T::tr[T::idx(i,i)].s=-1e8;
	}
	T::build(1,n);
	printf("%d\n",T::tr[T::idx(1,n)].s);//not debugging!
	while(q--){
		const int x=nxi(),v=nxi();
		hx[x]=v;
		T::mod_v(x,v);
		const node ls=T::ask_v(std::max(x-m+1,1),x-1);
		const node rs=T::ask_v(x+1,std::min(x+m-1,n));
		upd(ls),upd(rs);
		upd((node){hx[x],x});
		printf("%d\n",T::tr[T::idx(1,n)].s);
	}
	return 0;
}
