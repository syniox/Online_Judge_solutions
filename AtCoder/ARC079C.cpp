#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <bitset>
typedef long long lint;
const int N=2e5+5;
std::bitset <N> vld1,vld2;

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
	const int n=nxi();
	for(int i=nxi(); i; --i){
		const int a=nxi(),b=nxi();
		if(a==1||b==1) vld1[a+b-1]=1;
		if(a==n||b==n) vld2[a+b-n]=1;
	}
	vld1&=vld2;
	puts(vld1.count()?"POSSIBLE":"IMPOSSIBLE");
	return 0;
}
