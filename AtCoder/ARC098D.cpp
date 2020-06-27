#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=2e5+5;
int n,val[N],nx[20][2];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=0; i<20; ++i){
		nx[i][0]=nx[i][1]=n+1;
	}
	lint ans=0;
	for(int i=n; i>=1; --i){
		int r=n;
		for(int j=0; j<20; ++j){
			if(val[i]>>j&1) nx[j][1]=nx[j][0],nx[j][0]=i;
			apn(r,nx[j][1]-1);
		}
		ans+=r-i+1;
	}
	printf("%lld\n",ans);
	return 0;
}
