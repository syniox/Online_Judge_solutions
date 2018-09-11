#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2;
int n,hx[N];

inline int gcd(int a,int b){
	for(;b;a%=b,std::swap(a,b));
	return a;
}

inline char get_c(){
	static char buf[20000],*h,*t;
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

bool bfs(){
	bool fx=0;
	for(;;){
		int cnt=0,lst=0;
		for(int i=1;i<=n;++i){
			if(hx[i]&1) ++cnt,lst=i;
		}
		if((n-cnt)&1) return fx^1;
		if(cnt!=1||hx[lst]==1) return fx;
		--hx[lst];
		int tp=hx[1];
		for(int i=2;i<=n;++i){
			tp=gcd(tp,hx[i]);
		}
		for(int i=1;i<=n;++i){
			hx[i]/=tp;
		}
		fx^=1;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	puts(bfs()?"First":"Second");
	return 0;
}
