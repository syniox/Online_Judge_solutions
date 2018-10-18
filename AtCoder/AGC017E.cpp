#include<iostream>
#include<cstdio>
#include<cstring>
const int N=202;
int n,fa[N<<1],out[N<<1],in[N<<1];
//more:0~N,need: N+1~N<<1

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int frt(const int x){
	return fa[x]?fa[x]=frt(fa[x]):x;
}

inline bool jdg(){
	static bool vis[N<<1],vld[N<<1];
	for(int i=1;i<N;++i){
		if(in[i]>out[i]) return 0;
		if(in[i+N]<out[i+N]) return 0;
	}
	for(int i=1;i<N;++i){
		if(in[i]||out[i]){
			const int cur=frt(i);
			vis[cur]|=1;
			vld[cur]|=in[i]!=out[i];
		}
	}
	for(int i=0;i<N<<1;++i){
		if(vis[i]^vld[i]) return 0;
	}
	return 1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),nxi();
	for(int i=1;i<=n;++i){
		const int a=nxi(),b=nxi(),c=nxi(),d=nxi();
		const int f1=(c==0?a:c+N),f2=(d==0?b+N:d);
//		printf("++in:%d\n",f2);
//		printf("++out:%d\n",f1);
		++in[f2];
		++out[f1];
		const int x=frt(f1),y=frt(f2);
		if(x!=y) fa[x]=y;
	}
	puts(jdg()?"YES":"NO");
	return 0;
}
