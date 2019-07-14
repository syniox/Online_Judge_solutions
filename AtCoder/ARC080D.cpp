#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=505;
int row,col,q,val[N*N];

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
	row=nxi(),col=nxi(),q=nxi();
	for(int i=1; i<=q; ++i){
		val[i]=nxi();
	}
	for(int i=1,j=1; i<=row; ++i){
		static int buk[N];
		int pt=i&1?1:col,ed=i&1?1:-1;
		for(; pt&&pt<=col; pt+=ed){
			buk[pt]=j;
			if(!--val[j]) ++j;
		}
		for(int i=1; i<=col; ++i){
			printf("%d ",buk[i]);
		}
		puts("");
	}
	return 0;
}
