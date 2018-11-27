#include <iostream>
#include <cstdio>
#include <cstring>
const int N=32005;
int n,cnt_dt,hx[N];
struct data{
	int l,r;
}dt[(int)4e6+5];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	inline void reverse(const int l,const int r){
		if(l>=r) return;
		int limit=(r-l+1)>>1;
		for(int i=0;i<limit;++i){
			std::swap(hx[l+i],hx[r-i]);
		}
		dt[++cnt_dt]=(data){l,r};
	}

	inline void build(const int l,const int r,const int spr){
		if(l>=r||spr==l-1||spr==r) return;
		const int mid=(l+r)>>1;
		int pti=0,ptj=0;
		while(pti+ptj<(mid-l+1)){
			if(l+pti-1==spr) ++ptj;
			else if(spr+ptj==r) ++pti;
			else{
				if(hx[l+pti]<hx[spr+ptj+1]) ++pti;
				else ++ptj;
			}
		}
		reverse(l+pti,spr);
		reverse(spr+1,spr+ptj);
		reverse(l+pti,spr+ptj);
		if(l<mid) build(l,mid,l+pti-1);
		if(mid+1<r) build(mid+1,r,spr+ptj);
	}

	void solve(const int l,const int r){
		const int mid=(l+r)>>1;
		if(l<mid) solve(l,mid);
		if(mid+1<r) solve(mid+1,r);
		if(l<r) build(l,r,mid);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	S::solve(1,n);
	printf("%d\n",cnt_dt);
	for(int i=1;i<=cnt_dt;++i){
		printf("%d %d\n",dt[i].l,dt[i].r);
	}
	return 0;
}
