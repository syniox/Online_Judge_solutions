#include<iostream>
#include<cstdio>
#include<cstring>
const int N=2502,M=52;
int n,m,sum,fir[N<<1],cur[N<<1],dep[N<<1],mp[M][M];
struct edge{
	int to,wi,nx;
}eg[N*6];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-';
	f&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline void add(const int a,const int b,const int v){
	static int cnt=1;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline void build(const int x,const int y){
	static const int cx[]={0,-1,1,0,0},cy[]={0,0,0,-1,1};
	const int fx=-mp[x][y];
	if(fx<=2){
		int tx=fx==1?1:n;
		if(tx==x) return;
		add(0,(tx-1)*m+y+N,1000-mp[tx][y]);
		for(;tx-cx[fx]!=x;tx-=cx[fx]){
			add((tx-1)*m+y+N,(tx-cx[fx]-1)*m+y+N,1000-mp[tx-cx[fx]][y]);
		}
		add((tx-1)*m+y+N,(N<<1)-1,1000);
	}
	else{
		const int px=(x-1)*m;
		int ty=y+cy[fx];
		if(!ty||ty>m) return;
		add(0,px+ty,1000);
		for(;ty>1&&ty<m;ty+=cy[fx]){
			add(px+ty,px+ty+cy[fx],1000-mp[x][ty]);
		}
		add(px+ty,(N<<1)-1,1000-mp[x][ty]);
	}
	sum+=1000;
}

inline bool dinic_bfs(){
	static int que[N<<1];
	int hd=0,tl=1;
	memset(dep,0,sizeof(dep));
	dep[0]=1;
	while(hd!=tl){
		const int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(eg[i].wi&&!dep[y]){
				dep[y]=dep[x]+1;
				que[tl++]=y;
			}
		}
	}
	return dep[(N<<1)-1];
}

int dinic_dfs(const int x,const int t){
	if(x==(N<<1)-1) return t;
	int tt=t,tp;
	for(int &i=cur[x];i;i=eg[i].nx){
		const int y=eg[i].to,v=eg[i].wi;
		if(dep[y]==dep[x]+1&&v&&(tp=dinic_dfs(y,std::min(v,tt)))){
			eg[i].wi-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
			if(!tt) break;
		}
	}
	return t-tt;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			mp[i][j]=nxi();
		}
	}
	for(int i=1;i<=n;++i){
		for(int j=1;j<=m;++j){
			if(mp[i][j]<0) build(i,j);
			else{
				const int cur=(i-1)*m+j;
				add(cur,cur+N,1e8);
			}
		}
	}
	while(dinic_bfs()) sum-=dinic_dfs(0,1e8);
	printf("%d\n",sum);
	return 0;
}
