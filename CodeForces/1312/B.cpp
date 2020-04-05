#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
typedef long long lint;
const int N=105;
int n,val[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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
	for(int T=nxi(); T; --T){
		n=nxi();
		for(int i=1; i<=n; ++i){
			val[i]=nxi();
		}
		std::sort(val+1,val+n+1);
		for(int i=n; i>=1; --i){
			printf("%d ",val[i]);
		}
		puts("");
	}
	return 0;
}
