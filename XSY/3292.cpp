#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=19260817;
int n,m,idx[N];
char str[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace T{
	int x,v,cnt,rt[N];
	struct node{
		int l,r,s;
	}tr[N*20];

	void build(const int k,const int l,const int r){
		if(l==r){
			tr[k].s=str[l]-'a'+1;
			return;
		}
		const int mid=(l+r)>>1;
		build(tr[k].l=++cnt,l,mid);
		build(tr[k].r=++cnt,mid+1,r);
		tr[k].s=((lint)tr[tr[k].l].s*qpow(27,r-mid)+tr[tr[k].r].s)%mod;
	}

	void mod_t(int &k,const int p,const int l,const int r){
		tr[k=++cnt]=tr[p];
		if(l==r){
			tr[k].s=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(tr[k].l,tr[p].l,l,mid);
		else mod_t(tr[k].r,tr[p].r,mid+1,r);
		tr[k].s=((lint)tr[tr[k].l].s*qpow(27,r-mid)+tr[tr[k].r].s)%mod;
	}

	inline void mod(const int r,const int p,const int x,const int v){
		T::x=x,T::v=v;
		mod_t(rt[r],rt[p],1,m);
	}
}

bool cmp(int a,int b){
	using T::tr;
	if(tr[T::rt[a]].s==tr[T::rt[b]].s) return a<b;
	int x=T::rt[a],y=T::rt[b];
	while(tr[x].l){
		if(tr[tr[x].l].s!=tr[tr[y].l].s){
			x=tr[x].l,y=tr[y].l;
		}
		else x=tr[x].r,y=tr[y].r;
	}
	return tr[x].s<tr[y].s;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	scanf("%s",str+1);
	T::build(T::rt[1]=++T::cnt,1,m);
	idx[1]=1;
	for(int i=2;i<=n;++i){
		idx[i]=i;
		const int p=nxi(),pos=nxi();
		char c;
		while((c=getchar())>'z'||c<'a');
		T::mod(i,p,pos,c-'a'+1);
	}
	std::sort(idx+1,idx+n+1,cmp);
	for(int i=1;i<=n;++i){
		printf("%d ",idx[i]);
	}
	puts("");
	return 0;
}
