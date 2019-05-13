#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n,q;

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=fgetc(fd));
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return f?-x:x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

template <class T1,class T2> inline T1 div_dwn(const T1 x,const T2 y){
	if(x>=0) return x/y;
	return (x-(y-1))/y;
}

namespace T{
	int x,y,v;
	struct node{
		int min,max,delta;
		lint sum;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void get_v(const int l,const int r,const int v){
		const int k=idx(l,r);
		tr[k].sum+=(lint)(r-l+1)*v;
		tr[k].min+=v;
		tr[k].max+=v;
		tr[k].delta+=v;
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].sum=tr[ls].sum+tr[rs].sum;
		tr[k].max=std::max(tr[ls].max,tr[rs].max);
		tr[k].min=std::min(tr[ls].min,tr[rs].min);
	}

	inline void psh(const int l,const int r){
		assert(l<r);
		int &d=tr[idx(l,r)].delta;
		if(!d) return;
		const int mid=(l+r)>>1;
		get_v(l,mid,d);
		get_v(mid+1,r,d);
		d=0;
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		if(l==r){
			tr[k].sum=tr[k].min=tr[k].max=nxi();
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			get_v(l,r,v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	void div_t(const int l,const int r){
		const int k=idx(l,r);
		if(l>=x&&r<=y){
			int nxt_min=div_dwn(tr[k].min,v);
			int nxt_max=div_dwn(tr[k].max,v);
			if(tr[k].min-nxt_min==tr[k].max-nxt_max){
				get_v(l,r,nxt_min-tr[k].min);
				return;
			}
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) div_t(l,mid);
		if(y>mid) div_t(mid+1,r);
		upd(l,r);
	}

	int qmin_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].min;
		psh(l,r);
		const int mid=(l+r)>>1;
		int ans=2e9;
		if(x<=mid) apn(ans,qmin_t(l,mid));
		if(y>mid) apn(ans,qmin_t(mid+1,r));
		return ans;
	}

	lint qsum_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].sum;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=qsum_t(l,mid);
		if(y>mid) ans+=qsum_t(mid+1,r);
		return ans;
	}

	inline void add(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,n);
	}

	inline void div(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		div_t(1,n);
	}

	inline int qmin(const int l,const int r){
		T::x=l,T::y=r;
		return qmin_t(1,n);
	}

	inline lint qsum(const int l,const int r){
		T::x=l,T::y=r;
		return qsum_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	T::build(1,n);
	for(int i=1; i<=q; ++i){
		const int op=nxi(),l=nxi()+1,r=nxi()+1;
		switch(op){
			case 1:
				T::add(l,r,nxi());
				break;
			case 2:
				T::div(l,r,nxi());
				break;
			case 3:
				printf("%d\n",T::qmin(l,r));
				break;
			case 4:
				printf("%lld\n",T::qsum(l,r));
				break;
		}
	}
	return 0;
}
