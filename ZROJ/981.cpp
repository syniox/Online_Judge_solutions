#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=2e5+5;
int n,q,val[N];
lint dp[N];

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

int main(){
	n=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	lint ans=0;
	for(int i=2; i<=n; ++i){
		ans+=std::max(0,std::max(val[i],val[i-1]));
	}
	printf("%lld\n",ans);
	for(int i=1; i<=q; ++i){
		int x=nxi(),v=nxi();
		if(x>1){
			ans-=std::max(0,std::max(val[x-1],val[x]));
			ans+=std::max(0,std::max(val[x-1],v));
		}
		if(x<n){
			ans-=std::max(0,std::max(val[x+1],val[x]));
			ans+=std::max(0,std::max(val[x+1],v));
		}
		val[x]=v;
		printf("%lld\n",ans);
	}
	return 0;
}

