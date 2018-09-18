#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e6+2;
int n,q,xdep,ask[N],fir[N],dep[N],ans[N],cntd[N];
struct edge{
	int to,nx;
}eg[N];
struct pnt{
	int x,y;
	pnt operator - (const pnt &b) const {
		return (pnt){x-b.x,y-b.y};
	}
	friend lint crs(const pnt &a,const pnt &b){
		return (lint)a.x*b.y-(lint)a.y*b.x;
	}
}pt[N];

inline void apx(int &x,const int y){
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

inline void add(const int a,const int b){
	static int cnt;
	eg[++cnt]=(edge){b,fir[a]};
	fir[a]=cnt;
}

void init_dfs(const int x){
	++pt[dep[x]].y;
	apx(xdep,dep[x]);
	for(int i=fir[x];i;i=eg[i].nx){
		const int y=eg[i].to;
		dep[y]=dep[x]+1;
		init_dfs(y);
	}
}

inline void solve(){
	static int st[N];
	int top=0;
	st[++top]=1,st[++top]=2;
	for(int i=3;i<=xdep;++i){
		while(top>1&&crs(pt[st[top]]-pt[st[top-1]],pt[i]-pt[st[top]])<0){
			--top;
		}
		st[++top]=i;
	}
	int cnt=1;
	for(int i=1;i<top;++i){
		const pnt cur=pt[st[i+1]]-pt[st[i]];
		for(;cnt<N&&crs(cur,(pnt){1,cnt})<0;++cnt){
			ans[cnt]=pt[st[i]].x+(n-pt[st[i]].y+cnt-1)/cnt;
		}
	}
	for(;cnt<N-1;++cnt) ans[cnt]=xdep;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	for(int i=1;i<=q;++i){
		ask[i]=nxi();
	}
	for(int i=2;i<=n;++i){
		add(nxi(),i);
	}
	dep[1]=1;
	init_dfs(1);
	for(int i=1;i<=n;++i){
		pt[i].x=i;
		pt[i].y+=pt[i-1].y;
	}
	solve();
	for(int i=1;i<=q;++i){
		printf("%d ",ans[ask[i]]);
	}
	puts("");
	return 0;
}
