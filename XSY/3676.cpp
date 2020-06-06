#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
int n,m,val[N],use[N];

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

lint solve(){
	static int idx[N];
	static lint dis[N];
	int p=0,l=0,clen=0;
	for(; ; p=(p+use[p])%m){
		if(idx[p]){
			clen=l-idx[p]+1;
			break;
		}
		idx[p]=++l;
		dis[l]=dis[l-1]+use[p];
	}
	int pre=l-clen;
	if(n<=pre) return dis[n];
	n-=pre;
	return (dis[l]-dis[l-clen])*(n/clen)+dis[n%clen+pre];
}

int main(){
	n=nxi(),m=nxi();
	for(int i=0; i<m; ++i){
		val[i]=nxi();
	}
	for(int l=1e9,i=(m*2)-1; ~i; --i){
		l=std::min(l+1,val[(i%m)]);
		if(i<m) use[i]=l;
	}
	printf("%lld\n",solve());
	return 0;
}
