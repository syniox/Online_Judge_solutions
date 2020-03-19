#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <cmath>
typedef long long lint;
const int N=5e4+5;

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
	for(int T=nxi(); T; --T){
		const int a=nxi(),b=nxi();
		lint prod=(lint)a*b;
		int mx=sqrt(prod),ans=(mx-1)*2-(a<mx)-(b<mx);
		if((lint)mx*(mx+1)<prod)
			ans+=(a!=mx)+(b!=mx);
		else if((lint)mx*mx<prod)
			ans+=(a!=mx&&b!=mx);
		printf("%d\n",ans);
	}
	return 0;
}
