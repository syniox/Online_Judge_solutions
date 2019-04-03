#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=200;

inline lint nxi(){
	lint x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int hbit(lint x){
	int ans=0;
	for(int i=32; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("c.in","r",stdin);
#endif
	static int que[N];
	const lint q=nxi()+1;
	int hd=100,tl=99,pos=0;
	for(int i=hbit(q)-1; ~i; --i){
		que[++tl]=++pos;
		if(q>>i&1) que[--hd]=++pos;
	}
	printf("%d\n",pos<<1);
	for(int i=hd; i<=tl; ++i){
		printf("%d ",que[i]);
	}
	for(int i=1; i<=pos; ++i){
		printf("%d ",i);
	}
	puts("");
	return 0;
}
