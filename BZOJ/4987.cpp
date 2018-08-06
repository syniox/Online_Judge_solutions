#include<iostream>
#include<cstdio>
#include<cstring>
#include<cassert>
const int N=3005;
int n,m,sz[N],fir[N],dp[N][N][3];
struct edge{
	int to,wi,nx;
}eg[N<<1];

inline void apn(int &x,const int y){
	if(x>y) x=y;
}

inline void add(const int a,const int b,const int v){
	static int cnt;
	eg[++cnt]=(edge){b,v,fir[a]};
	fir[a]=cnt;
}

inline char gtc(){
	static char buf[20000],*h,*t;
	if(h==t){
		t=(h=buf)+fread(buf,1,20000,stdin);
	}
	return *h++;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=gtc())>'9'||c<'0');
	while(x=x*10-48+c,(c=gtc())>='0'&&c<='9');
	return x;
}

void dfs(const int x,const int fa){
	memset(dp[x][0],0,3<<2);
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y==fa) continue;
		dfs(y,x);
		int w=eg[i].wi,ltj=std::min(sz[x]-1,m-1);
		for(int j=ltj;j>=0;--j){
			int ltk=std::min(sz[y]-1,m-j-1);
			for(int k=0;k<=ltk;++k){

				apn(dp[x][j+k+1][0],dp[x][j][0]+dp[y][k][0]+(w<<1));
				apn(dp[x][j+k+1][1],dp[x][j][0]+dp[y][k][1]+w);
				apn(dp[x][j+k+1][1],dp[x][j][1]+dp[y][k][0]+(w<<1));
				apn(dp[x][j+k+1][2],dp[x][j][0]+dp[y][k][2]+(w<<1));
				apn(dp[x][j+k+1][2],dp[x][j][1]+dp[y][k][1]+w);
				apn(dp[x][j+k+1][2],dp[x][j][2]+dp[y][k][0]+(w<<1));
			}
		}
		sz[x]+=sz[y];
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	memset(dp,60,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1;i<n;++i){
		int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	dfs(1,0);
	int ans=1<<30;
	for(int i=1;i<=n;++i){
		apn(ans,dp[i][m-1][0]);
		apn(ans,dp[i][m-1][1]);
		apn(ans,dp[i][m-1][2]);
	}
	printf("%d\n",ans);
	return 0;
}
