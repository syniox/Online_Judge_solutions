#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <queue>
typedef long long lint;
using namespace std;
const int N=5005;
int n,m,q,val[N];
lint dp[N];

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
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	memset(dp,-10,sizeof(dp));
	dp[0]=0;
	for(int i=1; i<=q; ++i){
		static lint fp[N];
		deque<int> dq;
		memcpy(fp,dp,sizeof(fp));
		for(int j=1; j<=n; ++j){
			for(; !dq.empty()&&fp[dq.back()]<fp[j-1]; dq.pop_back());
			dq.push_back(j-1);
			if(j-dq.front()>m) dq.pop_front();
			dp[j]=fp[dq.front()]+val[j];
		}
	}
	lint ans=-1;
	for(int i=n-m+1; i<=n; ++i){
		apx(ans,dp[i]);
	}
	printf("%lld\n",ans);
	return 0;
}
