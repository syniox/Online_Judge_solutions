#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=505;
int n,rnk[N][N];
lint *cdis,mp[N][N],dis[N][N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
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

bool cmp_dis(const int a,const int b){//为何要按点值排序？
	return cdis[a]<cdis[b];
}

int main(){
	memset(mp,10,sizeof(mp));
	memset(dis,10,sizeof(dis));
	n=nxi();
	for(int i=1; i<=n; ++i){
		mp[i][i]=dis[i][i]=0;
	}
	for(int i=nxi(); i; --i){
		const int a=nxi(),b=nxi(),v=nxi();
		apn(mp[a][b],(lint)v);
		apn(mp[b][a],(lint)v);
		dis[a][b]=dis[b][a]=mp[a][b];
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			if(dis[j][i]>1e14) continue;
			for(int k=1; k<=n; ++k){
				apn(dis[j][k],dis[j][i]+dis[i][k]);
			}
		}
	}
	for(int i=1; i<=n; ++i){
		cdis=dis[i];
		for(int j=1; j<=n; ++j)
			rnk[i][j]=j;
		std::sort(rnk[i]+1,rnk[i]+n+1,cmp_dis);
	}
	lint ans=1e14;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n; ++j){
			if(mp[i][j]>1e9) continue;
			lint mx=0;
			for(int k=n; k; --k){
				int d=dis[i][rnk[i][k]];
				if(cabs(d-mx)<=mp[i][j])
					apn(ans,d+mx+mp[i][j]);
				apx(mx,dis[j][rnk[i][k]]);
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
