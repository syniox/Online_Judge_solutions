#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
int n,hx[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int solve(){
	static int wid[N],height[N],sum[N],que[N];
	wid[n+1]=0,height[n+1]=0;
	int hd=0,tl=1;
	que[0]=n+1;
	for(int i=n;i;--i){
		sum[i]=sum[i+1]+hx[i];
	}
	for(int i=n;i;--i){
		while(hd<tl-1&&sum[que[hd+1]]+wid[que[hd+1]]<=sum[i]) ++hd;
		wid[i]=sum[i]-sum[que[hd]];
		height[i]=height[que[hd]]+1;
		while(tl>hd&&sum[que[tl-1]]+wid[que[tl-1]]>=wid[i]+sum[i]) --tl;
		que[tl++]=i;
	}
	return height[1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	printf("%d\n",solve());
	return 0;
}
