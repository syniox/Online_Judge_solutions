#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
const int N=5e5+5;
int n,m,fir[N],ind[N],idx[N],to_s[N],to_t[N];
bool del[N<<2];
std::vector <int> from[N];
struct edge{
	int fr,to,wi,nx;
}eg[N<<2];
struct data{
	int id,v;
	bool operator < (const data &b) const {
		return v<b.v;
	}
};

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

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

inline void add_edge(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){a,b,v,fir[a]};
	fir[a]=cnt;
	++ind[b];
	from[b].push_back(cnt);
}

inline void topo(){
	static int que[N];
	int cni=0,hd=0,tl=1;
	que[0]=0;
	while(hd!=tl){
		const int x=que[hd++];
		idx[++cni]=x;
		for(int i=fir[x];i;i=eg[i].nx){
			const int y=eg[i].to;
			if(!--ind[y]) que[tl++]=y;
		}
	}
}

inline void solve(){
	std::priority_queue <data> pq;
	int nd=0,ans=1e9;
	for(int i=1;i<=n+1;++i){
		const int x=idx[i];
		const int limit=from[x].size();
		for(int j=0;j<limit;++j){
			del[from[x][j]]=1;
		}
		while(!pq.empty()&&del[pq.top().id]) pq.pop();
		if(x&&!pq.empty()){
			const int v=pq.top().v;
			if(ans>v) nd=x,ans=v;
		}
		for(int j=fir[x];j;j=eg[j].nx){
			pq.push((data){j,to_s[x]+to_t[eg[j].to]+eg[j].wi});
		}
	}
	printf("%d %d\n",nd,ans);
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int x=nxi(),y=nxi();
		add_edge(x,y,1);
	}
	for(int i=1;i<=n;++i){
		add_edge(0,i,0);
		add_edge(i,n+1,0);
	}
	topo();
	for(int i=2;i<=n+1;++i){
		const int x=idx[i];
		const int limit=from[x].size();
		for(int j=0;j<limit;++j){
			const int e=from[x][j];
			apx(to_s[x],to_s[eg[e].fr]+eg[e].wi);
		}
	}
	for(int i=n+1;i>1;--i){
		const int x=idx[i];
		for(int j=fir[x];j;j=eg[j].nx){
			apx(to_t[x],to_t[eg[j].to]+eg[j].wi);
		}
	}
	solve();
	return 0;
}
