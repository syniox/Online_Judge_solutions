#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1.5e5+5;
int n,m,q,va[N],vb[N];

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

namespace T{
	int x,y,v;
	struct node{
		int delta,min;
		void get_v(const int d){
			delta+=d,min+=d;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].min=std::min(tr[idx(l,mid)].min,tr[idx(mid+1,r)].min);
	}

	inline void psh(const int l,const int r){
		int &d=tr[idx(l,r)].delta;
		if(!d||l==r) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].get_v(d);
		tr[idx(mid+1,r)].get_v(d);
		d=0;
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].min=-l;
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void add_t(const int l,const int r){
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_v(v);
			return;
		}
		psh(l,r);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(l,mid);
		if(y>mid) add_t(mid+1,r);
		upd(l,r);
	}

	inline void add(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,m);
	}

	inline bool valid(){
		return tr[idx(1,m)].min>=0;
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=m; ++i){
		vb[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		va[i]=nxi();
	}
	std::sort(vb+1,vb+m+1);
	T::build(1,m);
	for(int i=1; i<=m; ++i){
		int pos=std::lower_bound(vb+1,vb+m+1,q-va[i])-vb;
		if(pos<=m) T::add(pos,m,1);
	}
	int ans=T::valid();
	for(int i=m+1; i<=n; ++i){
		int pos_ad=std::lower_bound(vb+1,vb+m+1,q-va[i])-vb;
		if(pos_ad<=m) T::add(pos_ad,m,1);
		int pos_rm=std::lower_bound(vb+1,vb+m+1,q-va[i-m])-vb;
		if(pos_rm<=m) T::add(pos_rm,m,-1);
		ans+=T::valid();
	}
	printf("%d\n",ans);
	return 0;
}
