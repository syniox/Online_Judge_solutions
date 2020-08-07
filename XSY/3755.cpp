#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=105,M=31;
const int mod=1e9+7;
int n,m,val[N],dp[M][N][N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

int main(){
	n=ni,m=ni;
	for(int i=1; i<=n; ++i){
		val[i]=ni;
	}
	for(int i=1; i<=n+1; ++i){
		for(int j=i-1; j<=n+1; ++j){
			dp[0][i][j]=1;
		}
	}
	//计算子集方案(只考虑A上为1的位置)
	int ans=1;
	for(int i=1; i<=m; ++i){
		dp[i][1][0]=1;
		for(int r=1; r<=n; ++r){
			for(int l=r+1; l>=1; --l){
				int res=0;//倍率??
				for(int d=r; d>=l-1; --d){//左区间右端点
					res=(res+(lint)dp[i-1][l][d]*dp[i-1][d+1][r])%mod;
					if((val[d]>>(i-1)&1)==0) break;
				}
				dp[i][l][r]=res;
			}
		}
	}
	ans=(lint)ans*dp[m][1][n]%mod;
	//计算超集方案(只考虑A上为0的位置)
	for(int i=1; i<=m; ++i){
		dp[i][1][0]=1;
		for(int r=1; r<=n; ++r){
			for(int l=r+1; l>=1; --l){
				int res=0;//倍率??
				for(int d=r; d>=l-1; --d){//左区间右端点
					res=(res+(lint)dp[i-1][l][d]*dp[i-1][d+1][r])%mod;
					if(val[d]>>(i-1)&1) break;
				}
				dp[i][l][r]=res;
			}
		}
	}
	ans=(lint)ans*dp[m][1][n]%mod;
	printf("%d\n",ans);
	return 0;
}
