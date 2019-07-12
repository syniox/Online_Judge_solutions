#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;

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
	int n=nxi(),q=nxi(),r_end=-1;
	lint ans=0;
	for(int i=1; i<=n; ++i){
		int p=nxi();
		ans+=(p+q-1)-std::max(p-1,r_end);
		r_end=p+q-1;
	}
	printf("%lld\n",ans);
	return 0;
}
