#include <iostream>
#include <cstdio>
#include <cstring>

inline char get_c(){
	static char *h,*t,buf[20000];
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
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

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		const int m=nxi(),n=nxi();
		printf("%d\n",((m<<1)-(n>>1)+1)*(n>>1)+m-(n>>1));
	}
	return 0;
}
