#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n,m;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline char get_c(){
		static char buf[20000],*h,*t;
		if(h==t){
			t=(h=buf)+fread(buf,1,20000,stdin);
			if(h==t) return EOF;
		}
		return *h++;
	}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=get_c())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=get_c());
		while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

namespace T{
	int x,y,v;
	struct node{
		int max,cmax,x2,tag;
		lint s;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void upd(const int l,const int r){
		assert(l!=r);
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].s=tr[ls].s+tr[rs].s;
		tr[k].cmax=0;
		tr[k].x2=-1;
		tr[k].max=std::max(tr[ls].max,tr[rs].max);
		if(tr[ls].max==tr[k].max){
			tr[k].cmax+=tr[ls].cmax;
			apx(tr[k].x2,tr[ls].x2);
		}
		else apx(tr[k].x2,tr[ls].max);
		if(tr[rs].max==tr[k].max){
			tr[k].cmax+=tr[rs].cmax;
			apx(tr[k].x2,tr[rs].x2);
		}
		else apx(tr[k].x2,tr[rs].max);
	}

	void get_psh(const int l,const int r,const int v){
		const int k=idx(l,r);
		if(tr[k].max<=v) return;
		if(tr[k].tag==-1||tr[k].tag>v){
			tr[k].tag=v;
		}
		if(tr[k].x2<v){
			tr[k].s-=(lint)(tr[k].max-v)*tr[k].cmax;
			tr[k].max=v;
			return;
		}
		assert(l!=r);
		const int mid=(l+r)>>1;
		get_psh(l,mid,v);
		get_psh(mid+1,r,v);
		upd(l,r);
	}

	void psh(const int l,const int r){
		const int mid=(l+r)>>1;
		const int t=tr[idx(l,r)].tag;
		if(t!=-1){
			get_psh(l,mid,t);
			get_psh(mid+1,r,t);
		}
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		tr[k].tag=-1;
		if(l==r){
			tr[k].max=tr[k].s=nxi();
			tr[k].cmax=1,tr[k].x2=0;
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void apmin_t(const int l,const int r){
		if(l>=x&&r<=y){
			get_psh(l,r,v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) apmin_t(l,mid);
		if(y>mid) apmin_t(mid+1,r);
		upd(l,r);
	}

	int qmax_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].max;
		psh(l,r);
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) apx(ans,qmax_t(l,mid));
		if(y>mid) apx(ans,qmax_t(mid+1,r));
		return ans;
	}

	lint qsum_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].s;
		psh(l,r);
		const int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=qsum_t(l,mid);
		if(y>mid) ans+=qsum_t(mid+1,r);
		return ans;
	}

	void apmin(const int x,const int y,const int v){
		T::x=x,T::y=y,T::v=v;
		apmin_t(1,n);
	}

	int qmax(const int x,const int y){
		T::x=x,T::y=y;
		return qmax_t(1,n);
	}

	lint qsum(const int x,const int y){
		T::x=x,T::y=y;
		return qsum_t(1,n);
	}
}

int main(){
	for(int T=nxi(); T; --T){
		n=nxi(),m=nxi();
		T::build(1,n);
		for(int i=1; i<=m; ++i){
			const int op=nxi();
			if(op==0){
				const int l=nxi(),r=nxi(),v=nxi();
				T::apmin(l,r,v);
			}
			if(op==1){
				const int l=nxi(),r=nxi();
				printf("%d\n",T::qmax(l,r));
			}
			if(op==2){
				const int l=nxi(),r=nxi();
				printf("%lld\n",T::qsum(l,r));
			}
		}
	}
	return 0;
}
