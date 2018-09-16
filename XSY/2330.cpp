#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
typedef long long lint;
const int N=1e5+2;
//col: ((1r) 4 5|6 7c) 2 0 | 3 1
int R,C,n,hx[N],dep[N<<1],col[N],cur[N<<1],fir[N<<1];
lint pm[N];
std::map<lint,int> mp;
struct edge{
	int to,wi,nx;
}eg[N<<2];

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

inline void add(const int a,const int b,const int v){
	static int cnt=1;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline void try_add(const int x,const int t){
	static const int nx[]={3,-1,0,1};
	const lint to=pm[x]+t;
	if(mp.find(to)==mp.end()) return;
	const int y=mp[to];
	if(nx[col[x]]==col[y]) add(x+(col[x]?0:N),y,col[y]?hx[y]:1e8);
}

inline void build(const int x){
	//2 0|3 1
	//->2 0->0 ->3 ->1
	const int pc=pm[x]%C;
	if(col[x]==2) add(0,x,hx[x]);
	if(!col[x]) add(x,x+N,hx[x]);
	if(col[x]==1){
		add(x,(N<<1)-1,hx[x]);
		return;
	}
	if(pc)try_add(x,1);
	if(pc!=1) try_add(x,-1);
	try_add(x,-C);
	try_add(x,C);
}

inline bool dinic_bfs(){
	static int que[N<<1];
	memset(dep,0,sizeof(dep));
	int hd=0,tl=1;
	dep[0]=1;
	while(hd!=tl){
		const int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!dep[y]&&eg[i].wi){
				dep[y]=dep[x]+1;
				que[tl++]=y;
			}
		}
	}
	return dep[(N<<1)-1];
}

int dinic_dfs(const int x,const int t){
	if(x==(N<<1)-1) return t;
	int tp,tt=t;
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
//	freopen("b.in","r",stdin);
#endif
	C=nxi(),R=nxi(),n=nxi();
	for(int i=1;i<=n;++i){
		const int y=nxi(),x=nxi();
		hx[i]=nxi();
		mp[pm[i]=(lint)(x-1)*C+y]=i;
		col[i]=(((x+y)&1)<<1)+(bool)((y&2));
	}
	for(int i=1;i<=n;++i){
		build(i);
	}
	int ans=0;
	while(dinic_bfs()) ans+=dinic_dfs(0,1e8);
	printf("%d\n",ans);
	return 0;
}
