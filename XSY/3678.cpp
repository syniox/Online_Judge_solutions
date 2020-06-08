#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e5+5;
int n;
lint pl[N],pr[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
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
		pl[i]=nxi(),pr[i]=nxi();
	}
	lint ans=0;
	for(int i=60; ~i; --i){
		bool can1=1;
		for(int j=1; j<=n; ++j){
			can1&=pr[j]>=(1ll<<i);
		}
		if(can1){
			ans|=1ll<<i;
			for(int j=1; j<=n; ++j){
				pr[j]^=(1ll<<i);//若此位为0不影响决策
				pl[j]=pl[j]<(1ll<<i)?0:pl[j]^(1ll<<i);
			}
		}else{
			for(int j=1; j<=n; ++j){
				if(pl[j]&(1ll<<i)){
					pl[j]^=(1ll<<i);
					pr[j]^=(1ll<<i);
				}
			}
		}
	}
	printf("%lld\n",ans);
	return 0;
}
