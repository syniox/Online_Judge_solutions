#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=12,V=150;
const int mod=998244353;
int n,m,q,sumv[1<<N],val[N],dp[1<<N];
int inv[V],C[V][V],lg2[1<<N],cbit[1<<N];

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

int main(){
	for(int i=0; i<V; ++i){
		C[i][0]=1;
		for(int j=1; j<=i; ++j){
			C[i][j]=(C[i-1][j-1]+C[i-1][j])%mod;
		}
	}
	inv[0]=inv[1]=1;
	for(int i=2; i<V; ++i){
		inv[i]=(lint)(mod+i-1)/i*inv[i-mod%i]%mod;
		assert((lint)i*inv[i]%mod==1);
	}
	n=nxi(),m=nxi(),q=nxi();
	for(int i=0; i<n+m; ++i) val[i]=nxi(),lg2[1<<i]=i;
	for(int i=1; i<1<<(n+m); ++i){
		sumv[i]=sumv[i^(i&-i)]+val[lg2[i&-i]];
		cbit[i]=cbit[i^(i&-i)]+1;
	}
	apn(q,sumv[(1<<(n+m))-1]);
	dp[0]=1;
	for(int t=0; t<q; ++t){
		for(int i=(1<<(n+m))-1; ~i; --i){
			int w=(lint)dp[i]*inv[n+m-cbit[i]]%mod;
			if(!w) continue;
			for(int j=0; j<n+m; ++j){
				if(i>>j&1) continue;
				dp[i|1<<j]=(dp[i|1<<j]+(lint)w*C[t-sumv[i]][val[j]-1])%mod;
			}
			dp[i]=w;
		}
	}
	int ans=0;
	for(int t=((1<<m)-1)<<n,i=0; i<1<<n; ++i){
		static int f[V];
		const int rest=q-sumv[i|t];
		if(rest<0) continue;
		memset(f,0,sizeof(f));
		f[0]=1;
		for(int j=0; j<n; ++j){
			if(i>>j&1) continue;
			for(int k=rest; ~k; --k){
				for(int l=1; l<=std::min(k,val[j]-1); ++l){
					f[k]=(f[k]+(lint)f[k-l]*C[k][l])%mod;
				}
			}
		}
		ans=(ans+(lint)f[rest]*dp[i|t])%mod;
	}
	printf("%d\n",ans);
	return 0;
}
