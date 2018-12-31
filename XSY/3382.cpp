#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,q;
struct vec{
	int x,y;
	friend bool cmp_x(const vec &a,const vec &b){
		return a.x<b.x;
	}
}pnt[N];

bool cmp_x(const vec &a,const vec &b);

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=get_c())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=get_c());
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return f?-x:x;
}

namespace D{
	int pt,val[N<<1];

	inline void ins(int x){
		val[++pt]=x;
	}

	inline void build(){
		std::sort(val+1,val+pt+1);
		pt=std::unique(val+1,val+pt+1)-val-1;
	}

	inline int ask(int x){
		return std::lower_bound(val+1,val+pt+1,x)-val;
	}
}

namespace T{
	int x,y,v,len;
	struct node{
		int s,delta;
		inline void get_psh(int delta){
			s+=delta,this->delta+=delta;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void init(){
		len=D::pt;
		for(int i=idx(len,len); i; --i){
			tr[i].s=-1e6,tr[i].delta=0;
		}
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].s=std::max(tr[idx(l,mid)].s,tr[idx(mid+1,r)].s);
	}

	inline void psh(const int l,const int r){
		int &delta=tr[idx(l,r)].delta;
		if(l==r||!delta) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].get_psh(delta);
		tr[idx(mid+1,r)].get_psh(delta);
		delta=0;
	}

	inline void mod_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_psh(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	inline void mod(const int l,const int r,const int v){
		if(l>r) return;
		T::x=l,T::y=r,T::v=v;
		T::mod_t(1,len);
	}
}

int jdg(lint tgt){
	static int to_r[N],cnt[N];
	memset(cnt,0,sizeof(cnt));
	int ans=0;
	T::init();
	for(int i=1,j=1; i<=D::pt; ++i){
		while(j<D::pt&&(lint)D::val[j+1]-D::val[i]<=tgt) ++j;
		to_r[i]=j;
	}
	for(int i=1,j=1; i<=n; ++i){
		for(; (lint)pnt[i].x-pnt[j].x>tgt; ++j){
			int cur=D::ask(pnt[j].y);
			if(!--cnt[cur]) T::mod(cur,cur,-1e6);
			T::mod(cur+1,to_r[cur],-1);
		}
		int cur=D::ask(pnt[i].y);
		if(!cnt[cur]++) T::mod(cur,cur,1e6);
		T::mod(cur+1,to_r[cur],1);
		apx(ans,T::tr[T::idx(1,T::len)].s);
		if(ans+1>=q) return 1;
	}
	return 0;
}

inline lint bin_search(){
	lint l=1,r=4e9,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(jdg(mid)) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		pnt[i].x=nxi(),pnt[i].y=nxi();
		D::ins(pnt[i].y);
	}
	D::build();
	std::sort(pnt+1,pnt+n+1,cmp_x);
	printf("%lld\n",bin_search());
	return 0;
}
