#include<iostream>
#include<cstdio>
#include<cstring>
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
	dp[x][0][0]=dp[x][0][1]=0;
	sz[x]=1;
	for(int i=fir[x];i;i=eg[i].nx){
		int y=eg[i].to;
		if(y==fa) continue;
		dfs(y,x);
		int w=eg[i].wi;
		for(int i=1;i<=std::min(sz[x],m);++i){
			for(int j=1;j<=std::min(sz[y],m-i);++i){

				apn(dp[x][i+j][0],dp[x][i][0]+dp[y][j][0]+(w<<1));
				apn(dp[x][i+j][1],dp[x][i][0]+dp[y][j][1]+w);
				apn(dp[x][i+j][1],dp[x][i][1]+dp[y][j][0]+(w<<1));
				apn(dp[x][i+j][2],dp[x][i][0]+dp[y][j][2]+(w<<1));
				apn(dp[x][i+j][2],dp[x][i][1]+dp[y][j][1]+w);
				apn(dp[x][i+j][2],dp[x][i][2]+dp[y][j][0]+(w<<1));
			}
		}
		sz[x]+=sz[y];
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	memset(dp,31,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		int a=nxi(),b=nxi(),v=nxi();
		add(a,b,v);
		add(b,a,v);
	}
	dfs(1,0);
	int ans=1<<30;
	for(int i=1;i<=n;++i){
		apn(ans,dp[i][m][2]);
	}
	printf("%d\n",ans);
	return 0;
}
