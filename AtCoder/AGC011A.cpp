#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,q,lim,val[N];

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
	n=nxi(),q=nxi(),lim=nxi();
	for(int i=1; i<=n; ++i)
		val[i]=nxi();
	std::sort(val+1,val+n+1);
	int ans=0;
	for(int i=1,r=-1,c=0; i<=n; ++i){
		if(val[i]>r||c>=q)
			++ans,r=val[i]+lim,c=0;
		++c;
	}
	printf("%d\n",ans);
	return 0;
}
