#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
struct _pair{
	lint x,y;
};

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

_pair solve(int n,int m){
	if((n&1)==0||(m&1)==0){
		lint res=(lint)n*m>>1;
		return (_pair){res,res};
	}
	if(n>m) std::swap(n,m);
	return (_pair){(lint)n*(m>>1),(lint)n*((m+1)>>1)};
}

int solve3(const int n,const int m){
	lint ans=std::min(n,m);
	for(int i=1; i<=std::max(1,n/3*2); ++i){
		_pair res1=solve(n-i,m);
		apn(ans,std::max((lint)i*m,res1.y)-std::min((lint)i*m,res1.x));
	}
	return ans;
}

int main(){
	int n=nxi(),m=nxi();
	if(n%3==0||m%3==0){
		puts("0");
		return 0;
	}
	int ans=std::min(n,m);
	apn(ans,solve3(n,m));
	apn(ans,solve3(m,n));
	printf("%d\n",ans);
}
