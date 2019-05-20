#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=2e5+5;
typedef long long lint;
int n,q;

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	template <class T> inline T cabs(const T x){
		return x<0?-x:x;
	}
}
using namespace utils;

namespace T{
	int x,y;
	lint v;
	struct node{
		lint v0,v1,delta;
		//v0: 上升
		inline void getv(const lint v){
			v0+=v,v1+=v,delta+=v;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		assert(l!=r);
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].v0=std::min(tr[ls].v0,tr[rs].v0);
		tr[k].v1=std::min(tr[ls].v1,tr[rs].v1);
	}

	inline void psh(const int l,const int r){
		assert(l!=r);
		lint &d=tr[idx(l,r)].delta;
		if(!d) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].getv(d);
		tr[idx(mid+1,r)].getv(d);
		d=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=(node){(lint)1e12+l,(lint)1e12+(n-r+1),0};
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void apl_t(const int l,const int r){
		if(l==r){
			const int k=idx(l,r);
			const lint old=tr[k].v0-l;
			if(v<old){
				tr[k]=(node){v+l,v+(n-r+1),0};
			}
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) apl_t(l,mid);
		else apl_t(mid+1,r);
		upd(l,r);
	}

	lint qmin0_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].v0;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=1e16;
		if(x<=mid) apn(ans,qmin0_t(l,mid));
		if(y>mid) apn(ans,qmin0_t(mid+1,r));
		return ans;
	}

	lint qmin1_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].v1;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=1e16;
		if(x<=mid) apn(ans,qmin1_t(l,mid));
		if(y>mid) apn(ans,qmin1_t(mid+1,r));
		return ans;
	}

	lint qans_t(const int l,const int r){
		if(l==r) return tr[idx(l,r)].v0-l;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=1e16;
		apn(ans,qans_t(l,mid));
		apn(ans,qans_t(mid+1,r));
		return ans;
	}

	inline void apl(const int x,const lint v){
		T::x=x,T::v=v;
		return apl_t(1,n);
	}

	inline lint qmin0(const int x,const int y){
		T::x=x,T::y=y;
		return qmin0_t(1,n);
	}

	inline lint qmin1(const int x,const int y){
		T::x=x,T::y=y;
		return qmin1_t(1,n);
	}
}

int main(){
	n=nxi(),q=nxi();
	int st_a=nxi(),st_b=nxi();
	T::build(1,n);
	int lst=nxi();
	T::apl(st_a,cabs(lst-st_b));
	T::apl(st_b,cabs(lst-st_a));
	for(int i=2; i<=q; ++i){
		const int x=nxi();
		lint res1=T::qmin1(1,x)-(n-x+1);
		lint res2=T::qmin0(x,n)-x;
		T::tr[T::idx(1,n)].getv(cabs(x-lst));
		T::apl(lst,std::min(res1,res2));
		lst=x;
	}
	printf("%lld\n",T::qans_t(1,n));
	return 0;
}
