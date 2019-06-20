#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=998244353;
int n,m,f[18];

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
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

void get_f(){
	static lint dp[N];
	for(int i=1; i<=m; ++i){
		dp[i]=1;
	}
	f[1]=m;
	for(int i=2; i<18; ++i){
		memset(dp,0,(1<<(i-2))*sizeof(dp[0]));
		for(int j=m; j>=1<<(i-2); --j){
			if(!dp[j]) continue;
			for(int k=j*2; k<=m; k+=j){
				dp[k]+=dp[j];
			}
			dp[j]=0;
		}
		lint res=0;
		for(int j=1<<(i-2); j<=m; ++j){
			res+=(dp[j]%=mod);
		}
		f[i]=res%mod;
	}
}

int main(){
	static int dp[N];
	n=nxi(),m=nxi();
	get_f();
	dp[0]=n&1?-1:1;
	for(int i=1; i<=n; ++i){
		const int lim=std::min(i,17);
		for(int j=1; j<=lim; ++j){
			dp[i]=(dp[i]-(lint)f[j]*dp[i-j])%mod;
		}
	}
	printf("%d\n",(dp[n]+mod)%mod);
	return 0;
}
