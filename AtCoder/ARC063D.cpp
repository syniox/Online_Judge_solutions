#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1e5+5;
int n,val[N];

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
	n=nxi();
	if(nxi()<2){
		puts("0");
		return 0;
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	int res=0,ans=0;
	for(int mx=0,i=n; i>=1; --i){
		apx(res,mx-val[i]);
		apx(mx,val[i]);
	}
	for(int mx=0,i=n; i>=1; --i){
		ans+=mx-val[i]==res;
		apx(mx,val[i]);
	}
	printf("%d\n",ans);
	return 0;
}
