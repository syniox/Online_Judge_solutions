#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5;
const int mod=1e9+7;
int n,buk[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
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
	n=nxi();
	for(int i=1; i<=n; ++i){
		++buk[nxi()];
	}
	for(int i=1+(n&1); i<n; i+=2){
		if(buk[i]!=2){
			puts("0");
			return 0;
		}
	}
	int ans=1;
	for(int i=1; i<=n>>1; ++i){
		ans=(ans<<1)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
