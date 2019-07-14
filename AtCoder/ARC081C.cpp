#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,val[N];

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
		val[i]=nxi();
	}
	std::sort(val+1,val+n+1);
	int r1=0,r2=0;
	for(int i=n,s=-1,r=n+1; (!r1||!r2)&&i>=1; --i){
		if(val[i]!=s) r=i,s=val[i];
		if(i<r){
			r-=2;
			if(r1) r2=val[i];
			else r1=val[i];
		}
	}
	printf("%lld\n",(lint)r1*r2);
	return 0;
}
