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
	int same=1,minb=1e9;
	lint ans=0;
	for(int i=nxi(); i; --i){
		int a=nxi(),b=nxi();
		same&=a==b;
		if(a>b) apn(minb,b);
		ans+=a;
	}
	printf("%lld\n",same?0ll:ans-minb);
	return 0;
}
