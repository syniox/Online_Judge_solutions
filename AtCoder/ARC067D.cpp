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
	int n=nxi(),q1=nxi(),q2=nxi(),lst=nxi();
	lint ans=0;
	for(int i=2; i<=n; ++i){
		int cur=nxi();
		ans+=std::min((lint)q2,(lint)(cur-lst)*q1);
		lst=cur;
	}
	printf("%lld\n",ans);
}
