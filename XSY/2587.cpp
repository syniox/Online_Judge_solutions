#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long lint;
const int N=1e5+2;
int n,q,hx[N],cf[N],sl[N][17],sr[N][17];

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

inline int cfmax(const int x,const int y){
	return cf[x]>cf[y]?x:y;
}

inline int bit(int x){
	int ans=0;
	if(x>>16) ans+=16,x>>=16;
	if(x>>8) ans+=8,x>>=8;
	if(x>>4) ans+=4,x>>=4;
	if(x>>2) ans+=2,x>>=2;
	if(x>>1) ++ans;
	return ans;
}

inline void get(int ss[N][17],const int x,const int t,const int f){
	const int fa=x+(1<<(t-1))*f;
	if(fa>n||fa<0) ss[x][t]=ss[x][t-1];
	else ss[x][t]=cfmax(ss[x][t-1],ss[fa][t-1]);
}

inline lint ask(const int x,const int y){
	if(x>=y) return 0;
	const int len=bit(y-x),m=cfmax(sl[x][len],sr[y-1][len]);
	lint ans=(lint)cf[m]*(y-m)*(m-x+1);
	if(x<m) ans+=ask(x,m);
	if(m<y-1) ans+=ask(m+1,y);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//	freopen("b.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=n;++i){
		hx[i]=nxi();
	}
	for(int i=1;i<n;++i){
		cf[i]=std::abs(hx[i+1]-hx[i]);
		sl[i][0]=sr[i][0]=i;
	}
	for(int t=1;t<17;++t){
		for(int x=1;x<=n;++x){
			get(sl,x,t,1);
			get(sr,x,t,-1);
		}
	}
	while(q--){
		const int x=nxi(),y=nxi();
		printf("%lld\n",ask(x,y));
	}
	return 0;
}
