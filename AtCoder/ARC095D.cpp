#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,val[N];

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
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	std::sort(val+1,val+n+1);
	int tgt=val[n]>>1,*p=std::lower_bound(val+1,val+n,tgt);
	if(p==val+n) printf("%d %d\n",val[n],*--p);
	else printf("%d %d\n",val[n],*p-tgt<=tgt-*--p?*++p:*p);
	return 0;
}
