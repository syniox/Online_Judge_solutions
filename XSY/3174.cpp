#include<iostream>
#include<cstdio>
#include<cstring>
const int N=3002;
int n,hx[N],fir[N];
bool vld[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline void add(int a,int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10-48+c,(c=gtc())>='0'&&c<='9');
	return x;
}

void dfs(int x,int f){
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(hx[y]>=hx[x]||y==f) continue;
		dfs(y,x);
		if(!vld[y]) vld[x]=1;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i) hx[i]=nxi();
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi();
		add(a,b);
		add(b,a);
	}
	for(int i=1;i<=n;++i){
		memset(vld,0,sizeof(vld));
		dfs(i,0);
		if(vld[i]) printf("%d ",i);
	}
	puts("");
	return 0;
}
