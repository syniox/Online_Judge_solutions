#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=3e5+5;
int n,qa,qb;

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
	n=nxi(),qa=nxi(),qb=nxi();
	if((lint)qa*qb<n||qa+qb>n+1){
		puts("-1");
		return 0;
	}
	for(int i=1,j=n; i<=qb; ++i){
		int num=std::min(qa,j-(qb-i));
		for(int k=j-num+1; k<=j; ++k){
			printf("%d ",k);
		}
		j-=num;
	}
	puts("");
	return 0;
}
