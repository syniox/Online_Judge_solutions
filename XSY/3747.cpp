#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const int N=255;
int n,m,val[N];
int mp[N][N],dp[N][N][2];
//mp: 该路径上除去末尾的点权和
//0: 异色 1: 同色

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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
struct data{
	int a,b;
	bool f;
};
vector<data> dbuk[N*200];

void upd(const data d,const int v){
	if(v<1e8&&v<dp[d.a][d.b][d.f]){
		dp[d.a][d.b][d.f]=v;
		dbuk[v].push_back(d);
	}
}
void dij(){
	static bool vis[N][N][2];
	dp[1][1][0]=0;
	dbuk[0].push_back((data){1,1,0});
	for(int d=0; d<N*200; ++d){
		for(int ttt=0; ttt<(int)dbuk[d].size(); ++ttt){
			data it=dbuk[d][ttt];
			if(vis[it.a][it.b][it.f]) continue;
			vis[it.a][it.b][it.f]=1;
			if(it.f==0){//找新的A类
				for(int i=1; i<=n; ++i){
					int v=d+mp[i][it.a]-val[i]*(i!=it.a);
					upd((data){it.b,i,1},v);
				}
			}else{//找其中的B类
				for(int i=1; i<=n; ++i){
					int v=d+mp[it.a][i]+mp[i][it.b];
					upd((data){i,it.b,0},v);
				}
			}
		}
	}
}

int main(){
	memset(mp,10,sizeof(mp));
	memset(dp,10,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		mp[i][i]=0;
	}
	for(int i=1; i<=m; ++i){
		const int a=nxi(),b=nxi();
		mp[a][b]=val[a];
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=n; ++k){
				apn(mp[j][k],mp[j][i]+mp[i][k]);
			}
		}
	}
	dij();
	printf("%d\n",dp[n][n][0]<1e8?dp[n][n][0]+val[n]:-1);
	return 0;
}
