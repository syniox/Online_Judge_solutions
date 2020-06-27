#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2005;
int n,val[N<<1],pos[2][N],dp[N],fp[2][N<<1][N];
bool col[N<<1];//白1黑0

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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
	n=nxi();
	for(int i=1; i<=n<<1; ++i){
		char c;
		while((c=getchar())!='W'&&c!='B');
		col[i]=c=='W';
		val[i]=nxi();
		pos[col[i]][val[i]]=i;
	}
	for(int i=n<<1; i; --i){
		memcpy(fp[0][i],fp[0][i+1],(n+2)*sizeof(int));
		memcpy(fp[1][i],fp[1][i+1],(n+2)*sizeof(int));
		for(int j=val[i]+1; j<=n+1; ++j)
			++fp[col[i]][i][j];
	}
	memset(dp,10,sizeof(dp));
	dp[0]=0;
	for(int i=1; i<=n<<1; ++i){//dp([i])[j]: 当前白点cnt
		for(int j=std::min(n,i); ~j&&i-j<=n; --j){
			const int cw=j,cb=i-j,r0=dp[j],r1=j?dp[j-1]:2e8;
			const int p0=pos[0][cb],p1=pos[1][cw];
			const int res0=r0+p0+fp[0][p0][cb]+fp[1][p0][cw+1]-i;//加黑
			const int res1=r1+p1+fp[0][p1][cb+1]+fp[1][p1][cw]-i;//加白
			dp[j]=std::min(res0,res1);
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
