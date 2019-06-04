#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3005;
const int mod=1e9+7;
int n,q,cnt,val[N],dp[N];

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

template <class T>
inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void get_val(){
	static int buk[N];
	bool flag=0;
	for(int i=1; i*i<=n; ++i){
		if(n%i) continue;
		val[++cnt]=i;
		if(i*i==n) flag=1;
		else buk[cnt]=n/i;
	}
	for(int i=cnt-flag; i; --i){
		val[++cnt]=buk[i];
	}
}

void get_dp(){
	for(int i=1; i<=cnt; ++i){
		int res=fpow(q,(val[i]+1)>>1);
		for(int j=1; j<i; ++j){
			if(val[i]%val[j]==0) res=(res-dp[j])%mod;
		}
		dp[i]=(res+mod)%mod;
	}
}

int main(){
	n=nxi(),q=nxi();
	get_val();
	get_dp();
	int ans=0;
	for(int i=1; i<=cnt; ++i){
		int wgt=val[i]&1?val[i]:val[i]>>1;
		ans=(ans+(lint)wgt*dp[i])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
