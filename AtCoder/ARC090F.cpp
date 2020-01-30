#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int mod=1e9+7;

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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

int main(){
	int q=nxi(),ans=0;
	for(int i=1,j=0,cc=1,cf=10,ci=1,fi=10,sum=0; i<1e8; (++i==fi)?++ci,fi*=10:0){
		while(sum<q){
			if(++j==cf) ++cc,cf*=10;
			sum+=cc;
		}
		ans+=sum==q;
		sum-=ci;
	}
	for(int i=9; i<=q; ++i){
		if(q%i>=q/i) continue;
		if(q%i==0){
			ans=(ans+fpow(10,i)-fpow(10,i-1)-q/i+1)%mod;
			ans=(ans-1)%mod;
		}
		ans=(ans+(q/i-q%i-1)/(i+1)+1)%mod;
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
