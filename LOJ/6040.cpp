#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,pow2[N],dp[N][N];
bool mtrx[N][N];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}

	template <class T>
	inline void apx(T &x,const T y){
		x<y?x=y:0;
	}

	template <class T>
	inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
}
using namespace utils;

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int get_r(const bool mtrx[N][N]){
	static std::bitset <N> m[N];
	int res=0;
	for(int i=0; i<n; ++i){
		m[i].reset();
		for(int j=0; j<n; ++j){
			if(mtrx[i][j]) m[i][j]=1;
		}
	}
	for(int i=0; i<n; ++i){
		int j=res;
		for(; j<n&&m[j][i]==0; ++j);
		if(j==n) continue;
		std::swap(m[res],m[j]);
		for(int k=0; k<n; ++k){
			if(res==k||!m[k][i]) continue;
			m[k]^=m[res];
		}
		++res;
	}
	return res;
}

int main(){
	n=nxi();
	for(int i=0; i<n; ++i){
		for(int j=0; j<n; ++j) mtrx[i][j]=nxi();
	}
	pow2[0]=1;
	for(int i=1; i<=n; ++i){
		pow2[i]=(pow2[i-1]<<1)%mod;
	}
	dp[0][0]=1;
	for(int i=0; i<n; ++i){
		for(int j=0; j<=i; ++j){
			const int cur=dp[i][j];
			if(!cur) continue;
			dp[i+1][j]=(dp[i+1][j]+(lint)pow2[j]*cur)%mod;
			dp[i+1][j+1]=(dp[i+1][j+1]+(lint)(pow2[n]-pow2[j]+mod)*cur)%mod;
		}
	}
	int r=get_r(mtrx);
	fprintf(stderr,"r: %d\n",r);
	int ans=0;
	for(int i=r; i<=n; ++i){
		const int wgt=fpow(pow2[n-i],n);
		ans=(ans+(lint)wgt*dp[i][r]%mod*dp[n][i])%mod;
	}
	printf("%lld\n",(lint)ans*fpow(dp[n][r],mod-2)%mod);
	return 0;
}
