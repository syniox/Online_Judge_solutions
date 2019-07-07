#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;

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
	int n=nxi(),m=nxi(),r1=0,r2=0;
	for(int i=1,lst=nxi(); i<n; ++i){
		int cur=nxi();
		r1=(r1+(lint)(cur-lst)*i%mod*(n-i))%mod;
		lst=cur;
	}
	for(int i=1,lst=nxi(); i<m; ++i){
		int cur=nxi();
		r2=(r2+(lint)(cur-lst)*i%mod*(m-i))%mod;
		lst=cur;
	}
	printf("%lld\n",(lint)r1*r2%mod);
	return 0;
}
