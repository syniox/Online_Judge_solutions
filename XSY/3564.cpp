#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=70;
const lint mod=(lint)1e16+61;
int cnt,lim[N];
lint n;

namespace utils{
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

lint smul(lint a,lint b){
	lint ans=0;
	for(; b; b>>=1,a=(a+a)%mod){
		if(b&1) ans=(ans+a)%mod;
	}
	return ans;
}

lint fpow(lint x,lint t){
	lint ans=1;
	for(; t; x=smul(x,x),t>>=1){
		if(t&1) ans=smul(ans,x);
	}
	return ans;
}

lint dfs(const int t,const bool f1,const bool f2,const bool z1,const bool z2,const bool q){
	static lint dp[N][2][2][2][2][2];
	static bool vis[N][2][2][2][2][2];
	if(t==-1) return z1&&z2&&q^1;
	if(vis[t][f1][f2][z1][z2][q]) return dp[t][f1][f2][z1][z2][q];
	vis[t][f1][f2][z1][z2][q]=1;
	lint ans=0;
	bool lim1=!(f1&&lim[t]==0),lim2=!(f2&&lim[t]==0);
	for(int i=0; i<=lim1; ++i){
		for(int j=0; j<=lim2; ++j){
			ans+=dfs(t-1,f1&&i==lim1,f2&&j==lim2,z1|i,z2|j,q^i^j);
		}
	}
	return dp[t][f1][f2][z1][z2][q]=ans%mod;
}

int main(){
	n=nxi();
	if(n==1){
		puts("1");
		return 0;
	}
	for(lint t=n; t; ++cnt,t/=2){
		lim[cnt]=t&1;
	}
	lint ans=(dfs(cnt-1,1,1,0,0,0)-n+mod)%mod;
	ans=smul(ans,fpow(n,mod-2));
	ans=smul(ans,fpow(n-1,mod-2));
	printf("%lld\n",ans);
	return 0;
}
