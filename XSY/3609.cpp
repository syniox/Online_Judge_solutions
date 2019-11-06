#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=105;
int n,m,mod,pw2[N*N],C[N][N],lnk[N][N];
int cnt[N][N][N][2],sum[N][N][N][2];
//点不相同
//lnk: 每个j至少连一个i
//cnt: 方案数
//sum: 每种情况最远点距离之和

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

void apadd(int &x,const lint y){
	x=(x+y)%mod;
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void init(){
	pw2[0]=1;
	for(int i=1; i<N*N; ++i){
		pw2[i]=(pw2[i-1]<<1)%mod;
	}
	for(int i=1; i<=std::max(n,m); ++i){
		lnk[i][0]=1;
		for(int j=1; j<=std::max(n,m); ++j){
			lnk[i][j]=(lint)(pw2[i]-1+mod)*lnk[i][j-1]%mod;
		}
	}
	for(int i=0; i<=std::max(n,m); ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j]+C[i-1][j-1])%mod;
		}
	}
}

int main(){
	n=nxi(),m=nxi(),mod=nxi();
	init();
	cnt[1][0][1][0]=1;
	int ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=0; j<=m; ++j){
			for(int k=1; k<=i; ++k){
				int curc=cnt[i][j][k][0],curs=sum[i][j][k][0];
				if(!curc&&!curs) continue;
				for(int l=1; l<=m-j; ++l){
					int wgt=(lint)lnk[k][l]*C[j+l][j]%mod;
					int tmp=(lint)wgt*l%mod*C[n][i]%mod*C[m][j+l]%mod*pw2[(n-i)*(m-j)]%mod;
					ans=(ans+(lint)tmp*(curs+curc))%mod;
					apadd(cnt[i][j+l][l][1],(lint)curc*wgt);
					apadd(sum[i][j+l][l][1],((lint)curs+curc)*wgt);
				}
			}
			for(int k=1; k<=j; ++k){
				int curc=cnt[i][j][k][1],curs=sum[i][j][k][1];
				if(!curc&&!curs) continue;
				for(int l=1; l<=n-i; ++l){
					int wgt=(lint)lnk[k][l]*C[i+l][i]%mod;
					apadd(cnt[i+l][j][l][0],(lint)curc*wgt);
					apadd(sum[i+l][j][l][0],((lint)curs+curc)*wgt);
				}
			}
		}
	}
	ans=(lint)ans*fpow(pw2[n*m],mod-2)%mod*fpow(n,mod-2)%mod*fpow(m,mod-2)%mod;
	printf("%d\n",ans);
	return 0;
}
