#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e6+5;
int n;
lint dp[N];
struct _pair{
	int x,y;
}pep[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool _pr_cmp_x(const _pair &a,const _pair &b){
	return a.x<b.x;
}

template <class T> inline void apn(T &x,const T y){
	x>y?x=y:0;
}

namespace T{
	int x,y;
	lint v;
	struct node{
		lint val,tag;
		inline void getpsh(lint v){
			val+=v,tag+=v;
		}
	}tr[N<<1];
	//i存dp[i]+mx(i+1,??)

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void psh(const int l,const int r){
		lint &t=tr[idx(l,r)].tag;
		if(!t) return;
		const int mid=(l+r)>>1;
		tr[idx(l,mid)].getpsh(t);
		tr[idx(mid+1,r)].getpsh(t);
		t=0;
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)].val=std::min(tr[idx(l,mid)].val,tr[idx(mid+1,r)].val);
	}

	lint ask_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y) return tr[idx(l,r)].val;
		const int mid=(l+r)>>1;
		lint ans=1e18;
		if(x<=mid) apn(ans,ask_t(l,mid));
		if(y>mid) apn(ans,ask_t(mid+1,r));
		return ans;
	}

	void mod_t(const int l,const int r){
		if(l!=r) psh(l,r);
		if(l>=x&&r<=y){
			tr[idx(l,r)].getpsh(v);
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		if(y>mid) mod_t(mid+1,r);
		upd(l,r);
	}

	inline lint ask(const int l,const int r){
		T::x=l,T::y=r;
		return ask_t(0,n);
	}

	inline void mod(const int l,const int r,const lint v){
		T::x=l,T::y=r,T::v=v;
		mod_t(0,n);
	}
}

void solve(){
	static int stk[N];
	int top=0,lpos=-1;
	for(int i=1; i<=n; ++i){
		for(; top&&pep[stk[top]].y<pep[i].y; --top){
			T::mod(stk[top-1],stk[top]-1,(pep[i].y-pep[stk[top]].y)<<1);
		}
		T::mod(i-1,i-1,pep[i].y<<1);
		stk[++top]=i;
		for(; lpos+1<i&&dp[lpos+1]<pep[i].x; ++lpos);
		dp[i]=1e18;
		if(~lpos){
			int *p=std::lower_bound(stk+1,stk+top+1,lpos+1);
			dp[i]=(lint)pep[i].x+(pep[(*p)].y<<1);
		}
		if(lpos<i-1){
			apn(dp[i],T::ask(lpos+1,i-1));
		}
		T::mod(i,i,dp[i]);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		pep[i].x=nxi(),pep[i].y=nxi();
	}
	std::sort(pep+1,pep+n+1,_pr_cmp_x);
	solve();
	printf("%lld\n",dp[n]);
	return 0;
}
