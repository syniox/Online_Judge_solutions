#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
const int S=1005;
int n,cnp,hx[N],prm[S],buk[N*10];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	static bool npr[N];
	for(int i=2;i<S;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<S;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
		++buk[hx[i]];
	}
	for(int i=(N*10)>>1;i;--i){
		if(!buk[i]) continue;
		for(int j=i<<1;j<N*10;j+=i){
			buk[j]+=buk[i];
		}
	}
	for(int i=1;i<=n;++i){
		printf("%d\n",buk[hx[i]]-1);
	}
	return 0;
}
