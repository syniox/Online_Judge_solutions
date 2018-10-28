#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,fir[N],que[N],link[N];
bool vis[N],ccir[N];
struct edge{
	int to,nx;
}eg[N];

inline void add_edge(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int solve(const int st){
	int p=st,hd=0,tl=0,size=0,cir_size=0;
	bool circle=0;
	for(;link[p]&&!vis[p];p=link[p]){
		vis[p]=1;
		que[tl++]=p;
	}
	if(vis[link[p]]==1){
		circle=1;
		for(;!ccir[p];p=link[p]){
			ccir[p]=1;
			++cir_size;
		}
	}
	while(hd!=tl){
		const int x=que[hd++];
		++size;
		if(link[x]&&!vis[link[x]]){
			vis[link[x]]=1;
			que[tl++]=link[x];
		}
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!vis[y]){
				vis[y]=1;
				que[tl++]=y;
			}
		}
	}
	return circle?1+(cir_size>1):size;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i){
		const int x=nxi();
		link[x]=nxi();
		add_edge(link[x],x);
	}
	int ans=1;
	for(int i=1;i<=n<<1;++i){
		if(!vis[i]&&link[i]) ans=(lint)ans*solve(i)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
