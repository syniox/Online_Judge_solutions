#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
int n,val[N],sd[N][N],sx[N][N];
lint dp[N][N],xp[N][N];

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

void oput(const int l,const int r,const int shift){
	if(l==r) return;
	int p2=sd[l][r],p1=sx[l][p2-1];
	oput(l,p1,shift+0);
	oput(p1+1,p2-1,shift+1);
	oput(p2,r,shift+2);
	printf("%d\n",shift+2);
}

int main(){
	memset(xp,-10,sizeof(xp));
	memset(dp,-10,sizeof(dp));
	n=nxi();
	for(int i=1; i<=n; ++i){
		sx[i][i+1]=i;
		xp[i][i+1]=dp[i][i]=val[i]=nxi();
	}
	for(int i=1; i<=n; ++i){
		for(int j=i-2; j>=1; j-=2){
			for(int k=j+2; k<=i; k+=2){
				lint v=xp[j][k-1]+dp[k][i];
				if(dp[j][i]<v){
					sd[j][i]=k,dp[j][i]=v;
				}
			}
			if(dp[j][i]>xp[j][i-1]){
				xp[j][i+1]=dp[j][i],sx[j][i+1]=i;
			}
			else{
				xp[j][i+1]=xp[j][i-1];
				sx[j][i+1]=sx[j][i-1];
			}
		}
	}
	{
		int pl=1,pr=1;
		for(int i=1; i<=n; ++i){
			for(int j=i; j<=n; j+=2){
				if(dp[i][j]>dp[pl][pr]) pl=i,pr=j;
			}
		}
		assert(((pr-pl)&1)==0);
		printf("%lld\n",dp[pl][pr]);
		printf("%d\n",(pl-1)+(n-pr)+(pr-pl)/2);
		for(int i=n; i>pr; --i) printf("%d\n",i);
		for(int i=1; i<pl; ++i) printf("%d\n",1);
		oput(pl,pr,0);
	}
	return 0;
}
