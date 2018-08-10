#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<queue>
const int N=2002;
int n,hx[N],in[N],fir[N];
bool vis[N];
struct edge{
	int to,nx;
}eg[N*10];
struct node{
	int x,v;
	bool operator < (const node &b) const {
		return v<b.v;
	}
};
std::priority_queue <node> pq;

inline int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}

inline void add(int a,int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,fir[b]};
	fir[b]=cnt;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void dfs(int x){
	vis[x]=1;
	for(int i=1;i<=n;++i){
		if(!vis[i]&&gcd(hx[i],hx[x])!=1){
			++in[i];
			add(x,i);
			dfs(i);
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	for(int i=1;i<=n;++i) hx[i]=nxi();
	std::sort(hx+1,hx+n+1);
	for(int i=1;i<=n;++i){
		if(!vis[i]) pq.push((node){i,hx[i]}),dfs(i);
	}
	while(!pq.empty()){
		node x=pq.top();
		pq.pop();
		printf("%d ",x.v);
		for(int i=fir[x.x];i;i=eg[i].nx){
			int y=eg[i].to;
			if(--in[y]==0) pq.push((node){y,hx[y]});
		}
	}
	puts("");
	return 0;
}
