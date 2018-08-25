#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=202;
const int mod=998244353;
int n,ans,pw2[N];
struct pnt{
	int x,y;
	pnt operator - (const pnt &b) const {
		return (pnt){x-b.x,y-b.y};
	}
}pt[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	pw2[0]=1;
	for(int i=1;i<=n;++i){
		pw2[i]=pw2[i-1]<<1<mod?pw2[i-1]<<1:(pw2[i-1]<<1)-mod;
	}
}

inline lint crs(pnt a,pnt b){
	return (lint)a.x*b.y-(lint)b.x*a.y;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	init();
	for(int i=1;i<=n;++i){
		pt[i].x=nxi();
		pt[i].y=nxi();
	}
	ans=((pw2[n]-(lint)(n-1)*n/2-n-1)%mod+mod)%mod;
	for(int i=1;i<n;++i){
		for(int j=i+1;j<n;++j){
			int tot=0;
			for(int k=j+1;k<=n;++k){
				if(crs(pt[j]-pt[i],pt[k]-pt[j])==0) ++tot;
			}
			//tot+2 dots on a line
			ans=(ans-pw2[tot]+1)%mod;
		}
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
