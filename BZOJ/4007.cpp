#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1024;
//wk:work  fg:fight
int n,m,st,dp[N][513],wk[513][11],fg[513][11];

inline void apx(int &a,const int b){
	if(a<b) a=b;
}
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void upd(const int x,const int dep){
	const int p=1<<dep;
	for(int i=0;i<=p;++i){
		for(int j=0;j<=p&&i+j<=m;++j){
			apx(dp[x][i+j],dp[x<<1][i]+dp[x<<1|1][j]);
		}
	}
}

void dfs(const int x,const int dep){
	//0:work  1:fight
	memset(dp[x],0,(1<<dep)+1);
	if(!dep){
		const int p=x-(1<<(n-1));
		for(int i=1;i<=n;++i){
			if(st&(1<<i)) dp[x][1]+=fg[p][i];
			else dp[x][0]+=wk[p][i];
		}
		return;
	}

	st&=(st^(1<<dep));
	dfs(x<<1,dep-1);
	dfs(x<<1|1,dep-1);
	upd(x,dep);

	st|=(st^(1<<dep));
	dfs(x<<1,dep-1);
	dfs(x<<1|1,dep-1);
	upd(x,dep);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("0.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	const int p=1<<(n-1);
	for(int i=0;i<p;++i){
		for(int j=1;j<n;++j) fg[i][j]=nxi();
	}
	for(int i=0;i<p;++i){
		for(int j=1;j<n;++j) wk[i][j]=nxi();
	}
	dfs(1,n-1);
	int ans=0;
	for(int i=0;i<=m;++i){
		apx(ans,dp[1][i]);
	}
	printf("%d\n",ans);
	return 0;
}
