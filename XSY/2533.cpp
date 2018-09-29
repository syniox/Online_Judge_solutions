#include<iostream>
#include<cstdio>
#include<cstring>
#include<queue>
typedef long long lint;
const int W=6e4+2;
int cnt,limit,fir[5];
lint dis[W][5];
struct edge{
	int to,wi,nx;
}eg[9];
struct node{
	int w,x;
};

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline void add(const int a,const int b,const int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	limit=1e5;
	cnt=0;
	memset(dis,-1,sizeof(dis));
	memset(fir,0,sizeof(fir));
}

inline void spfa(){
	static std::queue <node> que;
	static bool vis[W][5];
	memset(vis,0,sizeof(vis));
	dis[0][2]=0;
	que.push((node){0,2});
	while(!que.empty()){
		node x=que.front();
		que.pop();
		vis[x.w][x.x]=0;
		for(int i=fir[x.x];i;i=eg[i].nx){
			const int y=eg[i].to,w=(x.w+eg[i].wi)%limit;
			const lint v=dis[x.w][x.x]+eg[i].wi;
			if(dis[w][y]==-1||dis[w][y]>v){
				dis[w][y]=v;
				if(!vis[w][y]){
					que.push((node){w,y});
					vis[w][y]=1;
				}
			}
		}
	}
}

inline lint get_ans(lint len){
	const int tp=len%limit;
	lint ans=9e18;
	for(int i=0;i<limit;++i){
		if(dis[i][2]!=-1){
			const lint cur=len+(i>tp?i-tp:i+limit-tp);
			apn(ans,std::max(dis[i][2],cur));
		}
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	int T=nxi<int>();
	while(T--){
		init();
		const lint len=nxi<lint>();
		for(int i=1;i<=4;++i){
			const int v=nxi<int>(),j=i+1>4?1:i+1;
			add(i,j,v);
			add(j,i,v);
		}
		for(int i=fir[2];i;i=eg[i].nx){
			apn(limit,eg[i].wi);
		}
		limit<<=1;
		spfa();
		printf("%lld\n",get_ans(len));
	}
	return 0;
}
