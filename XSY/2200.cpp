#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
int n,val[N];
lint q,preval[N],dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace T{
	//i位储存dp[i]+max(i+1,?)
	int x,y;
	lint v;
	class node{
		public:
			lint v,tag;
			inline void get_psh(const lint v){
				this->v+=v;
				tag+=v;
			}
	}tr[N<<2];

	inline void psh(const int k){
		if(!tr[k].tag) return;
		tr[k<<1].get_psh(tr[k].tag);
		tr[k<<1|1].get_psh(tr[k].tag);
		tr[k].tag=0;
	}

	inline void upd(const int k){
		tr[k].v=std::min(tr[k<<1].v,tr[k<<1|1].v);
	}

	lint ask_t(const int k,const int l,const int r){
		if(l>=x&&r<=y) return tr[k].v;
		if(l!=r) psh(k);
		const int mid=(l+r)>>1;
		if(y<=mid) return ask_t(k<<1,l,mid);
		if(x>mid) return ask_t(k<<1|1,mid+1,r);
		return std::min(ask_t(k<<1,l,mid),ask_t(k<<1|1,mid+1,r));
	}

	void add_t(const int k,const int l,const int r){
		if(l>=x&&r<=y){
			tr[k].get_psh(v);
			return;
		}
		assert(l!=r);
		psh(k);
		const int mid=(l+r)>>1;
		if(x<=mid) add_t(k<<1,l,mid);
		if(y>mid) add_t(k<<1|1,mid+1,r);
		upd(k);
	}

	inline lint ask(const int l,const int r){
		if(l>r) return 1e14;
		T::x=l,T::y=r;
		return ask_t(1,0,n);
	}

	inline void add(const int l,const int r,const lint v){
		T::x=l,T::y=r,T::v=v;
		add_t(1,0,n);
	}
}

inline int get_llim(const int x){
	int l=0,r=x,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(preval[x]-preval[mid]<=q) r=mid;
		else l=mid+1;
	}
	return l;
}

inline void work(){
	static int stk[N],top;
	for(int i=1; i<=n; ++i){
		for(; top&&val[stk[top]]<=val[i]; --top){
			int delta=val[i]-val[stk[top]];
			T::add(stk[top-1],stk[top]-1,delta);
		}
		stk[++top]=i;
		T::add(i-1,i-1,val[i]);
		dp[i]=T::ask(get_llim(i),i-1);
		if(i<n) T::add(i,i,dp[i]);
	//	printf("%lld ",dp[i]);
	}
	//puts("");
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		preval[i]=preval[i-1]+val[i];
	}
	work();
	printf("%lld\n",dp[n]);
	return 0;
}
