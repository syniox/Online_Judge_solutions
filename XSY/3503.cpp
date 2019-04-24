#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1.5e5+5;
int n,m,oset,delta,val[N],buk[N<<2];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace T{
	int x,y,v;
	struct node{
		int mn,ncnt,tag;
		inline void getpsh(const int v){
			mn+=v,tag+=v;
		}
	}tr[N<<3];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void psh(const int l,const int r){
		const int tag=tr[idx(l,r)].tag,mid=(l+r)>>1;
		if(!tag||l==r) return;
		tr[idx(l,mid)].getpsh(tag);
		tr[idx(mid+1,r)].getpsh(tag);
		tr[idx(l,r)].tag=0;
	}

	void upd(const int l,const int r){
		const int k=idx(l,r),mid=(l+r)>>1;
		const int ls=idx(l,mid),rs=idx(mid+1,r);
		tr[k].mn=std::min(tr[ls].mn,tr[rs].mn);
		tr[k].ncnt=0;
		if(tr[ls].mn==tr[k].mn) tr[k].ncnt+=tr[ls].ncnt;
		if(tr[rs].mn==tr[k].mn) tr[k].ncnt+=tr[rs].ncnt;
	}

	void build(const int l,const int r){
		tr[idx(l,r)].ncnt=r-l+1;
		if(l==r) return;
		const int mid=(l+r)>>1;
		build(l,mid);
		build(mid+1,r);
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

	int ask_t(const int l,const int r){
		const int k=idx(l,r);
		psh(l,r);
		if(l>=x&&r<=y) return tr[k].mn==0?tr[k].ncnt:0;
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans+=ask_t(l,mid);
		if(y>mid) ans+=ask_t(mid+1,r);
		return ans;
	}

	inline void mod(const int l,const int r,const int v){
		T::x=l,T::y=r,T::v=v;
		mod_t(1,oset+n+m);
	}

	inline int ask(const int l,const int r){
		T::x=l,T::y=r;
		return ask_t(1,oset+n+m);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	oset=n+m;
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		++buk[oset+val[i]];
	}
	T::build(1,oset+n+m);
	for(int i=1; i<=n; ++i){
		if(buk[oset+i]){
			T::mod(oset+i-buk[oset+i]+1,oset+i,1);
		}
	}
	for(int i=1; i<=m; ++i){
		int p=nxi(),x=nxi();
		if(p>0){
			--buk[oset+val[p]];
			if(val[p]<=-delta+n){
				int pos=oset+val[p]-buk[oset+val[p]];
				T::mod(pos,pos,-1);
			}
			val[p]=x-delta;
			int pos=oset+val[p]-buk[oset+val[p]];
			++buk[oset+val[p]];
			T::mod(pos,pos,1);
		}
		else if(x>0){
			int pos=oset-delta+n;
			if(buk[pos]) T::mod(pos-buk[pos]+1,pos,-1);
			++delta;
		}
		else{
			--delta;
			int pos=oset-delta+n;
			if(buk[pos]) T::mod(pos-buk[pos]+1,pos,1);
		}
		printf("%d\n",T::ask(oset-delta+1,oset-delta+n));
	}
	return 0;
}
