#include<iostream>
#include<cstdio>
#include<cstring>
const int N=10002;
int S,T,cur[N<<1],fir[N<<1],dep[N<<1];
char map[N];
struct edge{
	int to,wi,nx;
}eg[N*400];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void add(int a,int b,int v){
	static int cnt=1;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline bool bfs(){
	static int que[N<<1];
	memset(dep,0,sizeof(dep));
	int hd=0,tl=1;
	que[0]=S+N;
	dep[S+N]=1;
	while(hd!=tl){
		int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!dep[y]&&eg[i].wi){
				dep[y]=dep[x]+1;
				que[tl++]=y;
			}
		}
	}
	return dep[T];
}

int dfs(int x,int t){
	if(x==T) return t;
	int tt=t,tp;
	for(int &i=cur[x];i;i=eg[i].nx){
		int y=eg[i].to,v=eg[i].wi;
		if(v&&tt&&dep[y]==dep[x]+1&&(tp=dfs(y,std::min(v,tt)))){
			eg[i].wi-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
		}
		if(!tt) break;
	}
	return t-tt;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("b.in","r",stdin);
#endif
	int R=nxi(),C=nxi();
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			char c;
			while((c=getchar())!='S'&&c!='T'&&c!='.'&&c!='o');
			if(c=='S') S=(i-1)*C+j;
			if(c=='T') T=(i-1)*C+j;
			map[(i-1)*C+j]=c;
		}
	}
	if((S-1)/C==(T-1)/C||S%C==T%C){
		puts("-1");
		return 0;
	}
	for(int i=1;i<=R;++i){
		for(int j=1;j<=C;++j){
			int now=(i-1)*C+j;
			if(map[now]=='.'||map[now]=='T') continue;
			if(map[now]!='S') add(now,now+N,1);
			for(int k=1;k<=R;++k){
				char tp=map[(k-1)*C+j];
				if(k!=i&&(tp=='o'||tp=='T')){
					add(now+N,(k-1)*C+j,1);
				}
			}
			for(int k=1;k<=C;++k){
				char tp=map[(i-1)*C+k];
				if(k!=j&&(tp=='o'||tp=='T')){
					add(now+N,(i-1)*C+k,1);
				}
			}
		}
	}
	int ans=0;
	while(bfs()){
		ans+=dfs(S+N,N);
	}
	printf("%d\n",ans);
	return 0;
}
