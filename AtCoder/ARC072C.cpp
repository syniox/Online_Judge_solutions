#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
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

lint solve(const bool f){
	lint ans=0,s=0;
	for(int i=1; i<=n; ++i){
		s+=val[i];
		if((i&1)==f&&s<=0) ans+=-s+1,s=1;
		if((i&1)!=f&&s>=0) ans+=s+1,s=-1;
	}
	return ans;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	printf("%lld\n",std::min(solve(0),solve(1)));
	return 0;
}
