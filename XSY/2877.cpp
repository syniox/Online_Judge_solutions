#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,m,q,ban1[N<<2],ban2[N<<2];
struct _pair{
	int x,y;
}lim1[N],lim2[N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

template <class T,size_t S>
class _disc{
	public:
		T v[S],*tl;
		int tot;
		_disc(){tl=v;}
		inline void ins(const T &x){
			*++tl=x;
		}
		inline void build(){
			std::sort(v+1,tl);
			tl=std::unique(v+1,tl+1)-1;
			tot=tl-v;
		}
		inline int ask(const T &x){
			return std::lower_bound(v,tl+1,x)-v;
		}
};
_disc <int,N<<2> D;

class _seg{
	protected:
		int x,v;
		struct node{
			int sum;
			bool clr;
			inline void getclr(){
				sum=0,clr=1;
			}
		}tr[N<<3];

		inline int idx(const int l,const int r){
			return (l+r)|(l!=r);
		}

		inline void upd(const int l,const int r){
			const int mid=(l+r)>>1;
			tr[idx(l,r)].sum=(tr[idx(l,mid)].sum+tr[idx(mid+1,r)].sum)%mod;
		}

		inline void psh(const int l,const int r){
			assert(l!=r);
			const int mid=(l+r)>>1;
			bool &c=tr[idx(l,r)].clr;
			if(c==0) return;
			tr[idx(l,mid)].getclr();
			tr[idx(mid+1,r)].getclr();
			c=0;
		}

		void add_t(const int l,const int r){
			if(l==r){
				tr[idx(l,r)].sum=(tr[idx(l,r)].sum+v)%mod;
				return;
			}
			psh(l,r);
			const int mid=(l+r)>>1;
			if(x<=mid) add_t(l,mid);
			else add_t(mid+1,r);
			upd(l,r);
		}

		void clr_t(const int l,const int r){
			if(r<=x){
				tr[idx(l,r)].getclr();
				return;
			}
			psh(l,r);
			const int mid=(l+r)>>1;
			clr_t(l,mid);
			if(x>mid) clr_t(mid+1,r);
			upd(l,r);
		}
	public:
		int tot;

		inline int qsum(){
			return tr[idx(0,tot)].sum;
		}

		inline void add(const int x,const int v){
			this->x=x,this->v=v;
			add_t(0,tot);
		}

		inline void clr(const int r){
			this->x=r;
			clr_t(0,tot);
		}

		inline void init(const int len){
			tot=D.tot;
			add(0,1);
			add(1,fpow(2,len-1)-1);
		}
}T1,T2;

void getlim(_pair *lim,const int len){
	for(int i=1; i<=len; ++i){
		lim[i].x=nxi(),lim[i].y=nxi();
		D.ins(lim[i].y);
		if(lim[i].x>1) D.ins(lim[i].x-1);
	}
}

void pshlim(_pair *lim,int *ban,const int len){
	for(int i=1; i<=len; ++i){
		apx(ban[D.ask(lim[i].y)],D.ask(lim[i].x-1));
	}
}

int main(){
	memset(ban1,-1,sizeof(ban1));
	memset(ban2,-1,sizeof(ban2));
	q=nxi(),n=nxi(),m=nxi();
	getlim(lim1,n);
	getlim(lim2,m);
	D.ins(q);
	D.build();
	pshlim(lim1,ban1,n);
	pshlim(lim2,ban2,m);
	T1.init(D.v[1]);
	T2.init(D.v[1]);
	if(ban1[1]>=0) T2.clr(ban1[1]);
	if(ban2[1]>=0) T1.clr(ban2[1]);
	for(int i=2; i<=D.tot; ++i){
		const int s1=T1.qsum(),s2=T2.qsum(),pw=fpow(2,D.v[i]-D.v[i-1]-1);
		T1.add(i-1,s2);
		T2.add(i-1,s1);
		if(pw-1>0){
			const int v=(lint)(pw-1)*(s1+s2)%mod;
			T1.add(i,v);
			T2.add(i,v);
		}
		if(ban1[i]>=0) T2.clr(ban1[i]);
		if(ban2[i]>=0) T1.clr(ban2[i]);
	}
	printf("%d\n",(T1.qsum()+T2.qsum())%mod);
	return 0;
}
