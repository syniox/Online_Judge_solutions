#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3005;
const int mod=1e9+7;
int n,q,dp[N],lim_r[N],sum0[N];

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

int main(){
	static char str[N];
	n=nxi(),q=nxi();
	scanf("%s",str+1);
	for(int i=1; i<=n; ++i){
		lim_r[i]=i;
		sum0[i]=sum0[i-1]+(str[i]=='0');
	}
	for(int i=1; i<=q; ++i){
		const int x=nxi(),y=nxi();
		for(int i=x; i<y; ++i){
			apx(lim_r[i],y);
		}
	}
	for(int i=1; i<=n; ++i){
		apx(lim_r[i],lim_r[i-1]);
	}
	dp[0]=1;
	for(int i=0; i<n; ++i){
		static int fp[N];
		memcpy(fp,dp,n*sizeof(int));
		memset(dp,0,n*sizeof(int));
		int r=lim_r[i+1];
		int add_0=sum0[r]-sum0[lim_r[i]];
		for(int j=0; j<=r; ++j){
			if(!fp[j]) continue;
			//print 1
			if(j+add_0<r-i){
				dp[j+add_0]=(dp[j+add_0]+fp[j])%mod;
			}
			//print 0
			if(j+add_0-1>=0){
				dp[j+add_0-1]=(dp[j+add_0-1]+fp[j])%mod;
			}
		}
	}
	printf("%d\n",dp[0]);
	return 0;
}
