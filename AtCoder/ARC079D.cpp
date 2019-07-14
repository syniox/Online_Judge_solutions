#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
lint val[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

int main(){
	lint q=nxi();
	int n=50;
	for(int i=1; i<=n; ++i){
		val[i]=q/n+i-1;
	}
	for(int i=1; i<=q%n; ++i){
		for(int j=1; j<i; ++j) --val[j];
		val[i]+=n;
		for(int j=i+1; j<=n; ++j) --val[j];
	}
	printf("%d\n",n);
	for(int i=1; i<=n; ++i){
		printf("%lld ",val[i]);
	}
	puts("");
	return 0;
}
