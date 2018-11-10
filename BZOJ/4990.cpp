#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1e6+5;
int n,cnt,buk[N],hx[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline char get_c(){
	static char *h,*t,buf[200000];
	if(h==t){
		t=(h=buf)+fread(buf,1,200000,stdin);
		if(h==t) return EOF;
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
	return x;
}

inline void add(const int x){
	static int que[10];
	int top=0;
	for(int i=std::max(1,x-4);i<=std::min(n,x+4);++i){
		que[++top]=buk[i];
	}
	std::sort(que+1,que+top+1);
	for(int i=top;i;--i){
		int pos=std::lower_bound(hx+1,hx+cnt+1,que[i])-hx;
		hx[pos]=que[i];
		apx(cnt,pos);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i) buk[nxi()]=i;
	for(int i=1;i<=n;++i) add(nxi());
	printf("%d\n",cnt);
	return 0;
}
