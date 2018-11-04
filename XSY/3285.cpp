#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int W=1.5e7+5;
int n,cnt1,cnt2,hx[30];
lint mx,limit,buk1[W],buk2[W];

template <class T> inline void apx(T &x,T y){
	if(x<y) x=y;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<='0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void build(lint buk[],int &cnt,const int x){
	lint ddl=limit/x;
	for(int i=1;i<=cnt;i++){
		if(buk[i]<=ddl){
			apx(mx,buk[++cnt]=buk[i]*x);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi<int>(),limit=nxi<lint>();
	mx=buk1[++cnt1]=buk2[++cnt2]=1;
	for(int i=1;i<=n;++i){
		hx[i]=nxi<int>();
	}
	std::sort(hx+1,hx+n+1);
	for(int i=n;i;--i){
		if(i&1) build(buk1,cnt1,hx[i]);
		else build(buk2,cnt2,hx[i]);
	}
	lint ans=0;
	std::sort(buk1+1,buk1+cnt1+1);
	std::sort(buk2+1,buk2+cnt2+1);
	for(int i=1,j=cnt2;i<=cnt1;i++){
		for(lint tp=limit/buk1[i];buk2[j]>tp;--j);
		ans+=j;
		apx(mx,buk1[i]*buk2[j]);
	}
	printf("%lld\n%lld\n",mx,ans);
	return 0;
}
