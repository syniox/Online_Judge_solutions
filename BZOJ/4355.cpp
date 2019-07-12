#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
int n,m;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct opt{
	int set;
	lint dlt,ap;
	inline void reset(){
		set=-1,dlt=0,ap=-1e15;
	}
	inline bool empty(){
		return set==-1&&dlt==0&&ap==-1e15;
	}
	friend opt operator + (const opt &a,const opt &b){
		if(b.set>=0) return b;
		lint ap=std::max(std::max(a.set+a.dlt,a.ap)+b.dlt,b.ap);
		return (opt){a.set,a.dlt+b.dlt,ap};
	}
};

namespace T{
	int x,y;
	opt op;
	struct node{
		opt v;
		lint min,n2;
		int ncnt;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].n2=1e15;
		tr[k].ncnt=0;
		tr[k].min=std::min(tr[ls].min,tr[rs].min);
		if(tr[ls].min==tr[k].min){
			tr[k].ncnt+=tr[ls].ncnt;
			apn(tr[k].n2,tr[ls].n2);
		}
		else apn(tr[k].n2,tr[ls].min);
		if(tr[rs].min==tr[k].min){
			tr[k].ncnt+=tr[rs].ncnt;
			apn(tr[k].n2,tr[rs].n2);
		}
		else apn(tr[k].n2,tr[rs].min);
	}

	void getopt(const int l,const int r,const opt &op){
		const int k=idx(l,r);
		if(op.set!=-1){
			tr[k].min=op.set,tr[k].ncnt=r-l+1;
			tr[k].n2=1e15;
		}
		tr[k].v=tr[k].v+op;
		tr[k].min+=op.dlt;
		if(tr[k].n2<1e15){
			tr[k].n2+=op.dlt;
		}
		if(tr[k].min>=op.ap) return;
		if(tr[k].n2>op.ap){
			tr[k].min=op.ap;
		}
		else{
			const int mid=(l+r)>>1;
			getopt(l,mid,tr[k].v);
			getopt(mid+1,r,tr[k].v);
			upd(l,r);
			tr[k].v.reset();
		}
	}
	
	void psh(const int l,const int r){
		opt &v=tr[idx(l,r)].v;
		if(v.empty()) return;
		const int mid=(l+r)>>1;
		getopt(l,mid,v);
		getopt(mid+1,r,v);
		v.reset();
	}

	void build(const int l,const int r){
		const int k=idx(l,r);
		tr[k].v.reset();
		if(l==r){
			tr[k].min=nxi();
			tr[k].n2=1e15;
			tr[k].ncnt=1;
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void apl_t(const int l,const int r){
		if(l>=x&&r<=y){
			getopt(l,r,op);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) apl_t(l,mid);
		if(y>mid) apl_t(mid+1,r);
		upd(l,r);
	}

	int q0_t(const int l,const int r){
		const int k=idx(l,r);
		if(l>=x&&r<=y) return tr[k].min==0?tr[k].ncnt:0;
		psh(l,r);
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans+=q0_t(l,mid);
		if(y>mid) ans+=q0_t(mid+1,r);
		return ans;
	}

	void apl(const int x,const int y,const opt &op){
		T::x=x,T::y=y,T::op=op;
		apl_t(1,n);
	}

	int q0(const int x,const int y){
		T::x=x,T::y=y;
		return q0_t(1,n);
	}
}

int main(){
	n=nxi(),m=nxi();
	T::build(1,n);
	while(m--){
		const int op=nxi(),l=nxi(),r=nxi();
		if(op==1){
			T::apl(l,r,(opt){nxi(),0,(lint)-1e15});
		}
		if(op==2){
			T::apl(l,r,(opt){-1,nxi(),0});
		}
		if(op==3){
			printf("%d\n",T::q0(l,r));
		}
	}
	return 0;
}
