#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1.5e5+5;
int delta,n,m,val[N],buk[N*3],psum[N*3];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=(c=='-')&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

namespace T{
	int x,y,v,tr[N*6];

	inline int idx(const int l,const int r){
		return (l+r)|(l!=r);
	}

	inline void upd(const int l,const int r){
		const int mid=(l+r)>>1;
		tr[idx(l,r)]=tr[idx(l,mid)]+tr[idx(mid+1,r)];
	}

	int ask_t(const int l,const int r){
		if(l>=x&&r<=y) return tr[idx(l,r)];
		const int mid=(l+r)>>1;
		int ans=0;
		if(x<=mid) ans+=ask_t(l,mid);
		if(y>mid) ans+=ask_t(mid+1,r);
		return ans;
	}

	void mod_t(const int l,const int r){
		if(l==r){
			tr[idx(l,r)]=v;
			return;
		}
		const int mid=(l+r)>>1;
		if(x<=mid) mod_t(l,mid);
		else mod_t(mid+1,r);
		upd(l,r);
	}

	void mod(const int x,const int v){
		T::x=x,T::v=v;
		mod_t(1,n+(m<<1));
	}

	inline int ask(const int l,const int r){
		T::x=l,T::y=r;
		return ask_t(1,n+(m<<1));
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		++buk[val[i]];
	}
	for(int i=1; i<=n; ++i){
		for(int j=0; j<buk[i]; ++j){
			++psum[m+i-j];
		}
	}
	for(int i=1; i<=n; ++i){
		if(psum[m+i]) T::mod(m+i,1);
	}
	for(int i=1; i<=m; ++i){
		const int p=nxi(),x=nxi();
		if(p==0) delta+=x;
		else{
			if(!--psum[m+val[p]-(--buk[val[p]])]){
				T::mod(m+val[p]-buk[val[p]],0);
			}
			val[p]=x-delta;
			if(!psum[m+val[p]-(buk[val[p]]++)]++){
				T::mod(m+val[p]-buk[val[p]]+1,1);
			}
		}
		int res=T::ask(m+delta+1,m+delta+n);
		printf("%d\n",n-res);
	}
	return 0;
}
/*
2 5
-7 9 
2 -8
1 -6
0 1
1 3
   */
