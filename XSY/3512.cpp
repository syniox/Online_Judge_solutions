#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=405;
int C[N][N],pw2[N*N],wgt[N][N],cnt[N][N],sum[N][N];

namespace utils{
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;
const int n=nxi(),mod=nxi();

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	pw2[0]=1;
	for(int i=1; i<=n*n; ++i){
		pw2[i]=pw2[i-1]*2%mod;
	}
	C[0][0]=1;
	for(int i=1; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=n-i; ++j){
			wgt[i][j]=(lint)pw2[j*(j-1)>>1]*fpow(pw2[i]+mod-1,j)%mod;
		}
	}
}

int main(){
	init();
	cnt[1][1]=1;
	sum[1][1]=n-1;
	for(int i=1; i<=n; ++i){
		for(int j=1; j<=i; ++j){
			const int curc=cnt[i][j],curs=sum[i][j];
			for(int k=1; k<=n-i; ++k){
				const int w=(lint)wgt[j][k]*C[n-i][k]%mod;
				cnt[i+k][k]=(cnt[i+k][k]+(lint)w*curc)%mod;
				sum[i+k][k]=(sum[i+k][k]+(lint)w*curs)%mod;
				sum[i+k][k]=(sum[i+k][k]+(lint)(n-i-k)*w%mod*curc)%mod;
			}
		}
	}
	int ans=0;
	for(int i=1; i<=n; ++i){
		ans=(ans+sum[n][i])%mod;
	}
	ans=(lint)ans*fpow(n-1,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
