#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=80;

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
	int qa=nxi(),qb=nxi();
	printf("%d %d\n",N,N);
	for(int i=0; i<N; ++i){
		for(int j=0; j<N/2-1; ++j){
			putchar((j&1)==0&&(i&1)==0&&--qb>0?'#':'.');
		}
		putchar('.');
		putchar('#');
		for(int j=N/2+1; j<N; ++j){
			putchar((j&1)==0&&(i&1)==0&&--qa>0?'.':'#');
		}
		puts("");
	}
	return 0;
}
