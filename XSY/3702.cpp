#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=3e5+5;
int n,q,nx_x[N],nx_y[N],vx[N],vy[N];
std::vector <int> buk[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

struct _D{
	int cnt,v[N];
	inline void add(const int x){
		v[++cnt]=x;
	}
	inline void build(int *nx){
		std::sort(v+1,v+cnt+1);
		cnt=std::unique(v+1,v+cnt+1)-v-1;
		for(int i=1; i<=cnt; ++i){
			nx[i]=std::upper_bound(v+1,v+cnt+1,v[i]+q)-v-1;
		}
	}
	inline int ask(const int x){
		return std::lower_bound(v+1,v+cnt+1,x)-v;
	}
}Dx,Dy;

namespace T{
#define mid ((l+r)>>1)
	int x,y,v;
	struct node{
		int mx,tag;
		inline void getpsh(const int t){
			mx+=t,tag+=t;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}
	inline void upd(const int l,const int r){
		tr[idx(l,r)].mx=std::max(tr[idx(l,mid)].mx,tr[idx(mid+1,r)].mx);
	}
	inline void psh(const int l,const int r){
		int &t=tr[idx(l,r)].tag;
		if(!t) return;
		tr[idx(l,mid)].getpsh(t);
		tr[idx(mid+1,r)].getpsh(t);
		t=0;
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].getpsh(v);
			return;
		}
		psh(l,r);
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	void add(const int l,const int r,const int v){
		x=l,y=r,T::v=v;
		add_t(1,Dy.cnt);
	}
	int ask(){
		return tr[idx(1,Dy.cnt)].mx;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		int a=nxi(),b=nxi();
		vx[i]=a+b,vy[i]=a-b;
		Dx.add(vx[i]),Dy.add(vy[i]);
	}
	Dx.build(nx_x);
	Dy.build(nx_y);
	for(int i=1; i<=n; ++i){
		vx[i]=Dx.ask(vx[i]);
		vy[i]=Dy.ask(vy[i]);
		buk[vx[i]].push_back(vy[i]);
	}
	int ans=0;
	for(int l=1,i=1; i<=Dx.cnt; ++i){
		std::vector <int> ::iterator it;
		for(; nx_x[l]<i; ++l){
			for(it=buk[l].begin(); it!=buk[l].end(); ++it){
				T::add(*it,nx_y[*it],-1);
			}
		}
		for(it=buk[i].begin(); it!=buk[i].end(); ++it){
			T::add(*it,nx_y[*it],1);
		}
		apx(ans,T::ask());
	}
	printf("%d\n",ans);
	return 0;
}
