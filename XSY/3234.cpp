#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,hx[N],ans;

template <class T> inline void twk(T &x){
	if(x>mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace T{
	int x,y,cnr,cnt,rt[N];
	struct node{
		int l,r,s,bel;
	}tr[N*31];
	void mod(int &k,int p,int l,int r){
		k=++cnt;
		tr[k]=tr[p];
		++tr[k].s;
		tr[k].bel=cnr;
		if(l==r) return;
		const int mid=(l+r)>>1;
		if(x<=mid) mod(tr[k].l,tr[p].l,l,mid);
		else mod(tr[k].r,tr[p].r,mid+1,r);
	}
	int ask_s(int k,int p,int l,int r){
		if(tr[k].s==tr[p].s) return 0;
		if(l>=x&&r<=y) return tr[k].s-tr[p].s;
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans+=ask_s(tr[k].l,tr[p].l,l,mid);
		if(y>mid) ans+=ask_s(tr[k].r,tr[p].r,mid+1,r);
		return ans;
	}
	int ask_x(int k,int p,int l,int r){
		if(l==r) return tr[k].bel;
		const int mid=(l+r)>>1;
		if(tr[tr[k].r].s>tr[tr[p].r].s) return ask_x(tr[k].r,tr[p].r,mid+1,r);
		return ask_x(tr[k].l,tr[p].l,l,mid);
	}
	inline void mod_t(const int v){
		T::x=v;
		++cnr;
		mod(rt[cnr],rt[cnr-1],0,1e9);
	}
	inline int ask_s_t(const int p,const int k,const int x,const int y){
		T::x=x,T::y=y;
		return ask_s(rt[k],rt[p-1],0,1e9);
	}
	inline int ask_x_t(const int p,const int k){
		return ask_x(rt[k],rt[p-1],0,1e9);
	}
}

int solve(const int l,const int r){
	const int pos=T::ask_x_t(l,r);
	int ans=0;
	if(pos-l<r-pos){
		for(int i=l;i<=pos;++i){
			twk(ans+=T::ask_s_t(pos,r,0,hx[pos]/hx[i]));
		}
	}
	else{
		for(int i=pos;i<=r;++i){
			twk(ans+=T::ask_s_t(l,pos,0,hx[pos]/hx[i]));
		}
	}
	if(l<pos) twk(ans+=solve(l,pos-1));
	if(r>pos) twk(ans+=solve(pos+1,r));
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
		T::mod_t(hx[i]);
	}
	printf("%d\n",solve(1,n));
	return 0;
}
