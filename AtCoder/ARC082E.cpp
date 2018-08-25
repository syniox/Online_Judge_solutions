#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=202;
const int mod=998244353;
int n,ans,pw2[N];
struct pnt{
	int x,y;
	inline int quad() const {
		if(x>0&&y>=0) return 1;
		if(x<=0&&y>0) return 2;
		if(x<0&&y<=0) return 3;
		if(x>=0&&y<0) return 4;
		return 0;
	}
	inline pnt abs() const {
		if(quad()<=2)return *this;
		return (pnt){-x,-y};
	}
	inline friend lint crs(pnt a,pnt b){
		return (lint)a.x*b.y-(lint)b.x*a.y;
	}
	pnt operator - (const pnt &b) const {
		return (pnt){x-b.x,y-b.y};
	}
	bool operator < (const pnt &b) const {
		int l=quad(),r=b.quad();
		if(l==r) return crs(*this,b)>0;
		return l<r;
	}
}base,pt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline bool cmp(pnt a,pnt b){
	return (a-base).abs()<(b-base).abs();
}

inline void init(){
	pw2[0]=1;
	for(int i=1;i<=n;++i){
		pw2[i]=pw2[i-1]<<1<mod?pw2[i-1]<<1:(pw2[i-1]<<1)-mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	init();
	for(int i=1;i<=n;++i){
		pt[i].x=nxi();
		pt[i].y=nxi();
	}
	ans=((pw2[n]-n-1)%mod+mod)%mod;
	for(int i=1;i<n;++i){
		base=pt[i];
		std::sort(pt+i+1,pt+n+1,cmp);
		for(int k=i+1,j=i+1;j<=n;j=k+1){
			k=j;
			while(k<n&&crs(pt[j]-pt[i],pt[k+1]-pt[i])==0) ++k;
			ans=(ans-pw2[k-j+1]+1)%mod;
		}
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
