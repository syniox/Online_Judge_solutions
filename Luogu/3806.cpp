#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=10005;
const char ot[2][4]={"NAY","AYE"};
int n,m,cnt,fir[N];
int rt,sz[N],dis[N],que[N],mxs[N],ans[10000005];
bool vis[N];
struct edge{
	int to,wi,nx;
}eg[N<<1];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}

inline void add(int a,int b,int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}
void frt(int x,int f,int t){
	sz[x]=1;
	mxs[x]=0;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]&&f!=y){
			frt(y,x,t);
			mxs[x]=max(mxs[x],sz[y]);
			sz[x]+=sz[y];
		}
	}
	mxs[x]=max(mxs[x],t-sz[x]);
	if(mxs[rt]>mxs[x]) rt=x;
}
void fdp(int x){
	que[++cnt]=dis[x];
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]){
			dis[y]=dis[x]+eg[i].wi;
			fdp(y);
		}
	}
}
void fsm(int x,int t,int fg){
	cnt=0,dis[x]=t;
	fdp(x);
	for(int i=1;i<cnt;++i){
		for(int j=i+1;j<=cnt;++j){
			ans[que[i]+que[j]]+=fg;
		}
	}
}
void ask(int x){
//	printf("%d\n",x);
	vis[x]=1;
	fsm(x,0,1);
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]){
			rt=0;//
			frt(y,0,sz[y]);
			fsm(rt,eg[i].wi,-1);
			ask(rt);
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	for(int a,b,c,i=1;i<n;++i){
		a=nxi(),b=nxi(),c=nxi();
		add(a,b,c);
		add(b,a,c);
	}
	mxs[0]=1e8;
	frt(1,0,n);
	ask(rt);
//	for(int i=1;i<=1000000;++i){
//		if(ans[i]) printf("%d ",i);
//	}
	for(int i=1;i<=m;++i){
		printf("%s\n",ot[ans[nxi()]]);
	}
	return 0;
}
