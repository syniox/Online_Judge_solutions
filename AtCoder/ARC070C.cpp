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
	int n=nxi(),l=0,r=n,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if((lint)mid*(mid+1)>>1>=n) r=mid;
		else l=mid+1;
	}
	printf("%d\n",l);
	return 0;
}
