#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
#include<cmath>
const int N=1e5+2;
int n,m,st1,st2,cf[N],fa[N],fir[N],col[N],ccl[N];
struct edge{
	int to,nx;
}eg[N<<1];

inline void add(int a,int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
	eg[++cnt]=(edge){a,fir[b]};
	fir[b]=cnt;
}

inline char get_c(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return h==t?EOF:*h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=get_c())>'9'||c<'0');
	while(x=x*10-48+c,(c=get_c())<='9'&&c>='0');
	return x;
}

void dfs(int x){
	ccl[x]=col[x];
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(fa[x]!=y){
			if(col[y]){
				st1=x,st2=y;
				continue;
			}
			fa[y]=x;
			col[y]=col[x]*-1;
			dfs(y);
			ccl[x]+=ccl[y];
		}
	}
}

void dfs2(int x){
	ccl[x]=col[x];
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(fa[x]!=y){
			if((x==st1&&y==st2)||(y==st1&&x==st2)) continue;
			dfs2(y);
			ccl[x]+=ccl[y];
		}
	}
}

inline void rev_rt(int x,int t){
	cf[x]+=t;
	while((x=fa[x])) cf[x]+=t;
}

inline int solve(){
	int cegv=0,ans=0,cnq=0;
	static int que[N];
	col[1]=1;
	dfs(1);
	for(int i=1;i<=n;++i){
		cegv+=abs(ccl[i]);
	}
	if(m==n-1) return ccl[1]?-1:cegv;
	if(col[st1]==col[st2]){
		if(ccl[1]&1) return -1;
		int p=ccl[1]>>1;
		col[st1]-=p,col[st2]-=p;
		dfs2(1);
		for(int i=1;i<=n;++i){
			ans+=abs(ccl[i]);
		}
		return ans+abs(p);
	}
	else{
		if(ccl[1]) return -1;
		rev_rt(st1,-1),rev_rt(st2,1);
		int ans=0;
		for(int i=2;i<=n;++i){
			if(cf[i]) que[++cnq]=cf[i]*ccl[i];
			else ans+=abs(ccl[i]);
		}
		std::nth_element(que+1,que+((cnq+1)>>1),que+cnq+1);
		int p=que[(cnq+1)>>1];
		for(int i=1;i<=cnq;++i){
			ans+=abs(que[i]-p);
		}
		return ans+abs(p);
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("c.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		add(nxi(),nxi());
	}
	printf("%d\n",solve());
	return 0;
}
