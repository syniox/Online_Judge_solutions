#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,v1[N],v2[N],v3[N];
lint res[N];

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
	freopen("snuke.in","r",stdin);
	freopen("snuke.out","w",stdout);
#endif
	n=nxi();
	for(int i=1; i<=n; ++i)
		v1[i]=nxi();
	for(int i=1; i<=n; ++i)
		v2[i]=nxi();
	for(int i=1; i<=n; ++i)
		v3[i]=nxi();
	std::sort(v1+1,v1+n+1);
	std::sort(v2+1,v2+n+1);
	std::sort(v3+1,v3+n+1);
	for(int i=1,j=1; i<=n; ++i){
		while(j<=n&&v1[j]<v2[i]) ++j;
		res[i]=res[i-1]+j-1;
	}
	lint ans=0;
	for(int i=1,j=1; i<=n; ++i){
		while(j<=n&&v2[j]<v3[i]) ++j;
		ans+=res[j-1];
	}
	printf("%lld\n",ans);
	return 0;
}
