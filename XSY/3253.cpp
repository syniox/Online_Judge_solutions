#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=305;
const int mod=1e9+7;
int n,tot,v1[N],v2[N],cbat[N<<1],chol[N<<1];
int dp[N][N];//可进洞，必进洞

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

class _disc{
	protected:
		int cnt,v[N<<1];
	public:
		inline void insert(const int x){
			v[++cnt]=x;
		}
		inline int build(){
			std::sort(v+1,v+cnt+1);
			cnt=std::unique(v+1,v+cnt+1)-v-1;
			return cnt;
		}
		inline int ask(const int x){
			return std::lower_bound(v+1,v+cnt+1,x)-v;
		}
}D;

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		v1[i]=nxi(),v2[i]=nxi();
		D.insert(v1[i]);
		D.insert(v2[i]);
	}
	tot=D.build();
	for(int i=1; i<=n; ++i){
		++cbat[D.ask(v1[i])];
		++chol[D.ask(v2[i])];
	}
	dp[0][0]=1;
	for(int i=tot; i; --i){
		static int fp[N][N];
		while(cbat[i]--){
			memcpy(fp,dp,sizeof(fp));
			memset(dp,0,sizeof(dp));
			for(int j=0; j<=n; ++j){
				for(int k=0; k<=n; ++k){
					int r=fp[j][k];
					if(!r) continue;
					if(j) dp[j-1][k]=(dp[j-1][k]+(lint)r*j)%mod;
					if(k) dp[j][k-1]=(dp[j][k-1]+(lint)r*k)%mod;
					dp[0][j+k]=(dp[0][j+k]+r)%mod;
				}
			}
		}
		if(!chol[i]) continue;
		for(int j=n; j>=chol[i]; --j){
			memcpy(dp[j],dp[j-chol[i]],sizeof(dp[j]));
		}
		for(int j=0; j<chol[i]; ++j){
			memset(dp[j],0,sizeof(dp[j]));
		}
	}
	int ans=0;
	for(int i=0; i<=n; ++i){
		ans=(ans+dp[i][0])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
