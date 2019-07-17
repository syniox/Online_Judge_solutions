#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x<y?y:x;}
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
#ifdef LOCAL
	freopen("range.in","r",stdin);
	freopen("range.out","w",stdout);
#endif
	int n=nxi(),ans=0;
	for(int i=1,l=1; i<=n; ++i){
		if(i!=nxi()){
			if(l<i) ans+=(i-l+1)>>1;
			l=i+1;
		}
		else if(i==n){
			ans+=(i-l+2)>>1;
		}
	}
	printf("%d\n",ans);
	return 0;
}
