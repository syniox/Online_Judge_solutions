#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=55;
int n;
lint val[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x>y?x=y:0;}
	template <class T> inline void apx(T &x,const T y){x<y?x=y:0;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

bool invld(){
	for(int i=1; i<=n; ++i){
		if(val[i]>=n) return 1;
	}
	return 0;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	lint ans=0;
	while(invld()){
		for(int i=1; i<=n; ++i){
			lint res=val[i]/n;
			if(!res) continue;
			val[i]-=res*n;
			for(int j=1; j<=n; ++j){
				if(i!=j) val[j]+=res;
			}
			ans+=res;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
