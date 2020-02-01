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

const int calc(int n,const int q){
	for(;;){
		if(n<=q) return n==q;
		int d=n%q,step=n/q+1;
		if(d==0) return step-1;
		n-=(d+step-1)/step*step;
	}
	assert(0);
	return 0;
}

int main(){
	int ans=0;
	for(int i=nxi(); i; --i){
		int n=nxi(),q=nxi();
		ans^=calc(n,q);
	}
	puts(ans?"Takahashi":"Aoki");
	return 0;
}
