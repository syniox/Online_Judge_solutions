#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e6+5;
const int mod=1e9+7;
int fac[N],ifac[N];
int x1,x2,x3,x4,x5,x6;
int y1,y2,y3,y4,y5,y6;

inline int nxi(FILE *fd=stdin){
	int x=0;
	char c;
	while((c=fgetc(fd))>'9'||c<'0');
	while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	assert(x>=y&&y>=0);
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

int solve(const int sx,const int sy,const int tx,const int ty){
	int ans=0;
	//enters by (i,y3-1)
	for(int i=x3; i<=x4; ++i){
		const int sa=i-sx,sb=y3-1-sy;
		const int ta=tx-i,tb=ty-y3;
		ans=(ans-(lint)(i+y3)*C(sa+sb,sa)%mod*C(ta+tb,tb))%mod;
	}
	//enters by (x3-1,i)
	for(int i=y3; i<=y4; ++i){
		const int sa=x3-1-sx,sb=i-sy;
		const int ta=tx-x3,tb=ty-i;
		ans=(ans-(lint)(i+x3)*C(sa+sb,sa)%mod*C(ta+tb,tb))%mod;
	}
	//leaves by (i,y4+1)
	for(int i=x3; i<=x4; ++i){
		const int sa=i-sx,sb=y4-sy;
		const int ta=tx-i,tb=ty-y4-1;
		ans=(ans+(lint)(i+y4+1)*C(sa+sb,sa)%mod*C(ta+tb,ta))%mod;
	}
	//leaves by (x4+1,i)
	for(int i=y3; i<=y4; ++i){
		const int sa=x4-sx,sb=i-sy;
		const int ta=tx-x4-1,tb=ty-i;
		ans=(ans+(lint)(i+x4+1)*C(sa+sb,sa)%mod*C(ta+tb,ta))%mod;
	}
	return ans<0?ans+mod:ans;
}

int main(){
	init();
	x1=nxi(),x2=nxi(),x3=nxi(),x4=nxi(),x5=nxi(),x6=nxi();
	y1=nxi(),y2=nxi(),y3=nxi(),y4=nxi(),y5=nxi(),y6=nxi();
	int st_x[]={x1-1,x2,x2,x1-1};
	int st_y[]={y1-1,y1-1,y2,y2};
	int ed_x[]={x6+1,x5,x5,x6+1};
	int ed_y[]={y6+1,y6+1,y5,y5};
	int ans=0;
	for(int i=0; i<4; ++i){
		for(int j=0; j<4; ++j){
			int res=solve(st_x[i],st_y[i],ed_x[j],ed_y[j]);
			ans=(ans+((i^j)&1?mod-res:res))%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
