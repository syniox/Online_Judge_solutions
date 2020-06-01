#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int w,h,n,ans,C[N*2][N*2];

namespace utils{
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

void solve1(const int w,const int h){
	static int pv[N];
	pv[0]=1;
	for(int i=1; i<h; ++i){
		int res=0;
		for(int j=1; j<=w; ++j){
			res=(res+(lint)C[j+i-2][i-1]*C[w-j+i][i])%mod;
		}
		pv[i]=res;
	}
	for(int i=1,s=w+1; i<=h; ++i,s=(lint)s*(w+1)%mod){
		for(int j=1; j+i-1<=h; ++j){
			ans=(ans+(lint)s*pv[j-1]%mod*pv[h-i-j+1])%mod;
		}
	}
}

void solve2(const int w,const int h){
	for(int i=1; i<h; ++i){
		for(int s=0,j=w; j>1; --j){
			s=(s+(lint)C[h-i+j-2][j-1]*C[h-i+w-j][w-j])%mod;
			ans=(ans+2ll*s*C[i+j-2][i]%mod*C[i+w-j][i-1])%mod;
		}
	}
}

int main(){
	w=nxi(),h=nxi(),n=w+h;
	for(int i=0; i<=n; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	solve1(w,h),solve1(h,w);
	solve2(w,h),solve2(h,w);
	for(int i=1; i<h; ++i){
		for(int j=1; j<w; ++j){
			int up=(lint)C[i+j-1][i]*C[i-1+w-j][i-1]%mod;
			int dn=(lint)C[h-i-1+j][j]*C[h-i+w-j-1][h-i]%mod;
			ans=(ans-2ll*up*dn)%mod;
		}
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
