#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=305;
int n,cnt,dis[N][N],mp[N][N];
struct _pair{
	int x,y;
	friend bool operator < (const _pair &a,const _pair &b){
		return dis[a.x][a.y]<dis[b.x][b.y];
	}
}pr[N*N];


namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x<y?y:x;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
#ifdef LOCAL
	freopen("road.in","r",stdin);
	freopen("road.out","w",stdout);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			dis[i][j]=nxi();
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=n; ++k){
				if(dis[i][j]+dis[j][k]<dis[i][k]){
					puts("-1");
					return 0;
				}
			}
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=i+1; j<=n; ++j){
			pr[++cnt]=(_pair){i,j};
		}
	}
	std::sort(pr+1,pr+cnt+1);
	memset(mp,63,sizeof(mp));
	for(int i=1; i<=n; ++i){
		mp[i][i]=0;
	}
	lint ans=0;
	for(int i=1; i<=cnt; ++i){
		int x=pr[i].x,y=pr[i].y;
		if(mp[x][y]==dis[x][y]) continue;
		mp[x][y]=mp[y][x]=dis[x][y];
		for(int j=1; j<=n; ++j){
			apn(mp[j][y],mp[j][x]+dis[x][y]);
			mp[y][j]=mp[j][y];
		}
		for(int j=1; j<=n; ++j){
			apn(mp[j][x],mp[j][y]+dis[y][x]);
			mp[x][j]=mp[j][x];
		}
		for(int j=1; j<=n; ++j){
			for(int k=1; k<=n; ++k){
				apn(mp[j][k],mp[j][x]+mp[x][k]);
			}
		}
		ans+=dis[x][y];
	}
	printf("%lld\n",ans);
	return 0;
}
