#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e5+5;
int n,m,tick,fa[N],dep[N],ch_tick[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_rt(int x){
	while(fa[x]) x=fa[x];
	return x;
}

inline void merge(const int x,const int y){
	++tick;
	if(x==y) return;
	if(dep[x]<dep[y]) fa[x]=y,ch_tick[x]=tick;
	else{
		fa[y]=x,ch_tick[y]=tick;
		if(dep[x]==dep[y]) ++dep[x];
	}
}

inline int solve(const int x,const int y){
	static int dp[N];
	int rt;
	for(rt=x;fa[rt];rt=fa[rt]){
		dp[fa[rt]]=std::max(ch_tick[rt],dp[rt]);
	}
	int lca,cnt=0;
	for(lca=y;fa[lca]&&lca!=x&&!dp[lca];lca=fa[lca]){
		apx(cnt,ch_tick[lca]);
	}
	int ans=std::max(cnt,dp[lca]);
	for(int p=fa[x];p;p=fa[p]) dp[p]=0;
	if(!fa[lca]&&lca!=rt) return 0;
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1,ans=0;i<=m;++i){
		const int op=nxi();
		const int x=nxi()^ans,y=nxi()^ans;
		if(!op) merge(get_rt(x),get_rt(y));
		else printf("%d\n",ans=solve(x,y));
	}
	return 0;
}
