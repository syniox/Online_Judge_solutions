#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
int n,q,val[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

namespace F2{
	inline int main(){
		static int dp[(int)1e6+5];
		memset(dp,10,sizeof(dp));
		dp[0]=0;
		for(int i=n; i; --i){
			if((lint)val[i]*i>q) continue;
			int wgt=val[i]*i;
			int limit=q/i;
			for(int j=limit; j>val[i]; --j){
				apn(dp[j],dp[j-val[i]]+wgt);
			}
			apn(dp[val[i]],(i<<1)+wgt);
		}
		for(int i=q; i>=0; --i){
			if(dp[i]<=q) return i;
		}
		return 0;
	}
}

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	printf("%d\n",F2::main());
	return 0;
}
