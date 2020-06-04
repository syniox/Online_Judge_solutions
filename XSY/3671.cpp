#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2005;
const int mod=1e9+7;
int n,q,dp[N][N];
//剩余i人，准备枪决j时0号人存活的概率

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

int gcd(int x,int y){
	return y?gcd(y,x%y):x;
}
inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void solve(){
	static int val[N],buk[N];
	static bool vis[N];
	dp[1][0]=1;
	for(int i=2; i<=n; ++i){
		const int d=i/gcd(i,q),inv2=fpow(2,mod-2);
		const int wgt=(lint)fpow(2,d-1)*fpow(fpow(2,d)-1,mod-2)%mod;
		//wgt: 2^(d-1)/(2^d-1)
		memset(vis,0,i*sizeof(vis[0]));
		for(int j=0; j<i; ++j){
			if(vis[j]) continue;
			int top=0;
			for(int k=j%i; !vis[k]; k=(k+q)%i){
				vis[buk[top++]=k]=1;
			}
			assert(top==d);
			for(int k=0; k<top; ++k){
				val[k]=buk[k]?(lint)wgt*dp[i-1][(buk[k]+q-1)%(i-1)]%mod:0;
			}
			for(int k=0,w=1; k<top; ++k,w=(lint)w*inv2%mod){
				dp[i][j]=(dp[i][j]+(lint)w*val[k])%mod;
			}
			for(int k=1,w=fpow(inv2,top-1); k<top; ++k){
				dp[i][buk[k]]=((dp[i][buk[k-1]]-val[k-1])*2ll+(lint)w*val[k-1])%mod;
			}
		}
	}
}

int main(){
	n=nxi(),q=nxi();
	solve();
	printf("%d\n",(dp[n][(q-1)%n]+mod)%mod);
	return 0;
}
