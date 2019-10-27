#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=405;
const int INF=1e8;
int n,m,ans_l[N][N],ans_r[N][N],vis[N][N];
char mp[N][N];
//从哪来： 0右1上2左3下
int c_fr[4][2]={{1,-1},{-1,1},{-1,1},{1,-1}};//另一维坐标变动

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int dfs(const int x,const int y,const int p){
	//都是从哪来
	if(vis[x][y]==1||x<1||x>n||y<1||y>m) return 0;
	if(vis[x][y]==-1) return INF;
	vis[x][y]=-1;
	int ans=0,t=c_fr[p][(int)mp[x][y]];
	if(p&1){
		ans=dfs(x,y+t,t+1);
		if(ans<INF) ans+=dfs(x+2-p,y,p);
	}
	else{
		ans=dfs(x+t,y,2-t);
		if(ans<INF) ans+=dfs(x,y+p-1,p);
	}
	vis[x][y]=1;
	return ans+1;
}

int main(){
	memset(ans_l,10,sizeof(ans_l));
	memset(ans_r,10,sizeof(ans_r));
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		scanf("%s",mp[i]+1);
		for(int j=1; j<=m; ++j){
			mp[i][j]=mp[i][j]=='Z';
		}
	}
	for(int i=1; i<=n; ++i){
		memset(vis,0,sizeof(vis));
		ans_l[i][0]=0;
		for(int j=1; j<=m; ++j){//先左
			ans_l[i][j]=ans_l[i][j-1]+dfs(i,j,0);
			if(ans_l[i][j]>=INF) break;
		}
		memset(vis,0,sizeof(vis));
		ans_r[i][m+1]=0;
		for(int j=m; j>=1; --j){//先右
			ans_r[i][j]=ans_r[i][j+1]+dfs(i,j,2);
			if(ans_r[i][j]>=INF) break;
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=m; ++j){
			int res=std::min(ans_l[i][j],ans_r[i][j]);
			printf("%d ",res<INF?res<<1:-1);
		}
		puts("");
	}
	return 0;
}
