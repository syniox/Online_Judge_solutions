#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=605;
int n,m,cnt,tot,vl[N],in[N];
int fir[N],cur[N],que[N],dep[N];
bool ps[N];
struct edge{
	int to,wi,nx;
}eg[190000];

inline void add(int a,int b,int v){
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
	++in[a];
	eg[++cnt]=(edge){a,0,fir[b]};
	fir[b]=cnt;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void tps(){
	int p=n*m,hd=0,tl=0;
	for(int i=1;i<=p;++i){
		if(!in[i]) ps[i]=1,que[tl++]=i;
	}
	while(hd!=tl){
		int x=que[hd++];
		for(int i=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(!eg[i].wi&&--in[y]==0){
				ps[y]=1;
				que[tl++]=y;
			}
		}
	}
}

inline bool bfs(){
	memset(dep,0,sizeof(dep));
	int hd=0,tl=1;
	que[0]=0;
	dep[0]=1;
	while(hd!=tl){
		int x=que[hd++];
		for(int i=cur[x]=fir[x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(eg[i].wi&&!dep[y]){
				que[tl++]=y;
				dep[y]=dep[x]+1;
			}
		}
	}
	return dep[N-1];
}

int dfs(int x,int t){
	if(x==N-1) return t;
	int tt=t,tp;
	for(int &i=cur[x];i;i=eg[i].nx){
		int y=eg[i].to,&v=eg[i].wi;
		if(v&&tt&&dep[y]==dep[x]+1&&(tp=dfs(y,min(v,tt)))){
			v-=tp;
			eg[i^1].wi+=tp;
			tt-=tp;
			if(!tt) break;
		}
	}
	return t-tt;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	cnt=1;
	n=nxi(),m=nxi();
	for(int a,b,k,i=1;i<=n*m;++i){
		if(i%m) add(i,i+1,6000000);
		scanf("%d",vl+i);
		k=nxi();
		while(k--){
			a=nxi(),b=nxi();
			add(a*m+b+1,i,6000000);
		}
	}
	tps();
	for(int i=1;i<=n*m;++i){
		if(ps[i]){
			if(vl[i]>0) tot+=vl[i],add(0,i,vl[i]);
			else if(vl[i]!=0) add(i,N-1,-vl[i]);
		}
	}
	while(bfs()){
		tot-=dfs(0,6000000);
	}
	printf("%d\n",tot);
	return 0;
}
