#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;

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
	int n=nxi(),q=nxi();
	if(q==0){
		printf("%lld\n",(lint)n*n);
		return 0;
	}
	lint ans=0;
	for(int i=q; i<=n; ++i){
		//fprintf(stderr,"%d: %d\n",i,(n/i)*(i-q)+std::max(0,n%i-q+1));
		ans+=(n/i)*(i-q)+std::max(0,n%i-q+1);
	}
	printf("%lld\n",ans);
	return 0;
}
