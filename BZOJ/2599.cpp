#include<iostream>
#include<cstdio>
#include<cstring>
#include<map>
using namespace std;
const int N=2e5+1;
int n,rt,len,sum,cnt,ans,sx[N],sz[N],fir[N];
bool vis[N];
map<int,int> mp[N];
struct edge{
	int to,wi,nx;
}eg[N<<1];
template <class T> inline void apn(T &a,T b){
	if(a>b) a=b;
}
template <class T> inline void apx(T &a,T b){
	if(a<b) a=b;
}

inline void add(int a,int b,int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

void get_rt(int x,int fa){
	sz[x]=1;
	sx[x]=1e7;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y!=fa&&!vis[y]){
			get_rt(y,x);
			sz[x]+=sz[y];
			apx(sx[x],sz[y]);
		}
	}
	apx(sx[x],sum-sz[x]);
	if(sx[rt]>sx[x]) rt=x;
}

void dfs(int x,int fa){
	mp[x].clear();
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to,v=eg[i].wi;
		if(!vis[y]&&y!=fa){
			apn(mp[x][v],1);
			dfs(y,x);
			map<int,int>::iterator it;
			for(it=mp[y].begin();it!=mp[y].end();++it){
				apn(mp[x][it->first+v],it->second+1);
			}
		}
	}
}

void work(int x){
	dfs(x,0);
	vis[x]=1;
	map<int,int>::iterator it;
	for(it=mp[x].begin();it!=mp[x].end();++it){
		if(it->first<len){
			if(mp[x][len-(it->first)]){
				apn(ans,it->second+mp[x][len-(it->first)]);
			}
		}
	}
	if(mp[x][len]){
		apn(ans,mp[x][len]);
	}
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(!vis[y]){
			sum=sz[y];
			get_rt(y,x);
			work(rt);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	sx[0]=1e8;
	n=nxi(),len=nxi();
	for(int a,b,c,i=1;i<n;++i){
		a=nxi(),b=nxi(),c=nxi();
		add(a,b,c);
		add(b,a,c);
	}
	sum=n;
	get_rt(1,0);
	work(rt);
	printf("%d\n",ans);
	return 0;
}
