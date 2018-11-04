#include <iostream>
#include <cstdio>
#include <cstring>
const int N=50005;
int n,q,hx[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y;
	struct node{
		int n,x;
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		const int k=idx(l,r),ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].n=std::min(tr[ls].n,tr[rs].n);
		tr[k].x=std::max(tr[ls].x,tr[rs].x);
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].n=tr[idx(l,r)].x=hx[l];
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	int ask_x_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].x;
		int ans=0,mid=(l+r)>>1;
		if(x<=mid) apx(ans,ask_x_t(l,mid));
		if(y>mid) apx(ans,ask_x_t(mid+1,r));
		return ans;
	}

	int ask_n_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)].n;
		int ans=1e9,mid=(l+r)>>1;
		if(x<=mid) apn(ans,ask_n_t(l,mid));
		if(y>mid) apn(ans,ask_n_t(mid+1,r));
		return ans;
	}

	inline int ask_x(const int x,const int y){
		T::x=x,T::y=y;
		return ask_x_t(1,n);
	}

	inline int ask_n(const int x,const int y){
		T::x=x,T::y=y;
		return ask_n_t(1,n);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	T::build(1,n);
	while(q--){
		const int l=nxi(),r=nxi();
		printf("%d\n",T::ask_x(l,r)-T::ask_n(l,r));
	}
	return 0;
}
