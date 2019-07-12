#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=105;
int n,m,w1,dp[N][N*3];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		int w=nxi(),v=nxi();
		if(i==1) w1=w;
		int dlt=w-w1;
		for(int j=i; j>=1; --j){
			for(int k=j*3; k>=dlt; --k){
				apx(dp[j][k],dp[j-1][k-dlt]+v);
			}
		}
	}
	int ans=0;
	for(int i=1; m>=w1*i&&i<=n; ++i){
		for(int j=std::min(i*3,m-w1*i); ~j; --j){
			apx(ans,dp[i][j]);
		}
	}
	printf("%d\n",ans);
	return 0;
}
