#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
int n,q;

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[1<<20];
	if(h==t){
		t=(h=buf)+fread(buf,1,1<<20,stdin);
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
	int x,y,v;
	struct node{
		int n,f;
		lint s;
		inline void get_psh(const int l,const int v){
			n+=v,f+=v,s+=(lint)l*v;
		}
	}tr[N<<1];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		tr[k].n=std::min(tr[idx(l,mid)].n,tr[idx(mid+1,r)].n);
		tr[k].s=tr[idx(l,mid)].s+tr[idx(mid+1,r)].s;
	}

	inline void psh(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		if(tr[k].f&&l!=r){
			tr[idx(l,mid)].get_psh(mid-l+1,tr[k].f);
			tr[idx(mid+1,r)].get_psh(r-mid,tr[k].f);
			tr[k].f=0;
		}
	}

	void build(const int l,const int r){
		if(l==r){
			tr[idx(l,r)].n=tr[idx(l,r)].s=nxi();
			return;
		}
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
		upd(l,r);
	}

	void mod_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].get_psh(r-l+1,v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	int ask_n_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y) return tr[idx(l,r)].n;
		int ans=1e9,mid=(l+r)>>1;
		if(x<=mid) apn(ans,ask_n_t(l,mid));
		if(y>mid) apn(ans,ask_n_t(mid+1,r));
		return ans;
	}

	lint ask_s_t(const int l,const int r){
		psh(l,r);
		if(l>=x&&r<=y) return tr[idx(l,r)].s;
		int mid=(l+r)>>1;
		lint ans=0;
		if(x<=mid) ans+=ask_s_t(l,mid);
		if(y>mid) ans+=ask_s_t(mid+1,r);
		return ans;
	}

	inline void mod(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		mod_t(1,n);
	}

	inline int ask_n(const int l,const int r){
		T::x=l,T::y=r;
		return ask_n_t(1,n);
	}
	
	inline lint ask_s(const int l,const int r){
		T::x=l,T::y=r;
		return ask_s_t(1,n);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	T::build(1,n);
	while(q--){
		char op;
		while((op=get_c())>'Z'||op<'A');
		const int a=nxi(),b=nxi();
		switch(op){
			case 'M': printf("%d\n",T::ask_n(a,b));break;
			case 'S': printf("%lld\n",T::ask_s(a,b));break;
			case 'P': T::mod(a,b,nxi());break;
		}
	}
	return 0;
}
