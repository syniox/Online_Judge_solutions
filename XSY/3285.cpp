#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
int n,cnt,hx[30];
lint mx,limit,buk[(int)2e7];

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

inline void build(const int x){
	int tp=cnt;
	for(int i=1;i<=tp;++i){
		lint tp=buk[i];
		for(tp*=x;tp<=limit;tp*=x) apx(mx,buk[++cnt]=tp);
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	n=nxi<int>(),limit=nxi<lint>();
	mx=buk[++cnt]=1;
	for(int i=1;i<=n;++i){
		hx[i]=nxi<int>();
	}
	std::sort(hx+1,hx+n+1);
	for(int i=n;i;--i){
		build(hx[i]);
	}
	printf("%lld\n%d\n",mx,cnt);
	return 0;
}
