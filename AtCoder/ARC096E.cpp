#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=3005;
int n,mod,S[N][N],C[N][N];

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

int fpow(int x,int t,const int mod=::mod){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	n=nxi(),mod=nxi();
	S[0][0]=1;
	for(int i=0; i<=n+1; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			S[i][j]=((lint)S[i-1][j]*j+S[i-1][j-1])%mod;
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	int ans=0;
	for(int i=0; i<=n; ++i){//内定不合法个数
		int bs=fpow(2,n-i);
		int ri=0,rv=fpow(2,fpow(2,n-i,mod-1));
		for(int j=0,st=1; j<=i; ++j,st=(lint)st*bs%mod)
			ri=(ri+(lint)S[i+1][j+1]*st)%mod;
		int res=(lint)rv*ri%mod*C[n][i]%mod;
		ans=(ans+(i&1?mod-res:res))%mod;
	}
	printf("%d\n",ans);
	return 0;
}
