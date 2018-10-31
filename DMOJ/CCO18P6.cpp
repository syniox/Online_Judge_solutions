#include <iostream>
#include <cstdio>
#include <cstring>
const int N=4100;
int n,cnt_dt[2],hx[N];
struct data{
	int l,r;
}dt[(int)4e5];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace S{
	bool f;
	inline void reverse(const int l,const int r){
		if(l>r) return;
		const int limit=(r-l+1)>>1;
		for(int i=1;i<=limit;++i){
			std::swap(hx[l+i-1],hx[r-i+1]);
			dt[++cnt_dt[f]]=(data){l+i-1,r-i+1};
		}
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
	cnt_dt[1]=cnt_dt[0];
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	S::f=1;
	S::solve(1,n);
	printf("%d\n",cnt_dt[1]);
	for(int i=1;i<=cnt_dt[0];++i){
		printf("%d %d\n",dt[i].l,dt[i].r);
	}
	for(int i=cnt_dt[1];i>cnt_dt[0];--i){
		printf("%d %d\n",dt[i].l,dt[i].r);
	}
	puts("");
	return 0;
}
