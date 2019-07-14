#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;

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
	int n=nxi(),c0=0,c1=0,c2=0;
	for(int i=1; i<=n; ++i){
		const int x=nxi();
		if((x&3)==0) ++c2;
		else if((x&1)==0) ++c1;
		else ++c0;
	}
	if(c1) puts(c2>=c0?"Yes":"No");
	else puts(c2>=c0-1?"Yes":"No");
	return 0;
}
