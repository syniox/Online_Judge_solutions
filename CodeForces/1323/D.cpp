#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=4e5+5;
int n,w,val[N];

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
	int ans=0;
	for(int i=0; i<=24; ++i){
		static int b0[N],b1[N];
		int c0=0,c1=0;
		for(int j=1; j<=n; ++j){
			if(val[j]>>i&1) b1[c1++]=val[j]&((1<<i)-1);
			else b0[c0++]=val[j]&((1<<i)-1);
		}
		std::sort(b0,b0+c0);
		std::sort(b1,b1+c1);
		bool res=0;
		for(int j=0; j<c0; ++j){
			res^=(b0+c0-std::lower_bound(b0+j+1,b0+c0,(1<<i)-b0[j]))&1;
		}
		for(int j=0; j<c1; ++j){
			res^=(b1+c1-std::lower_bound(b1+j+1,b1+c1,(1<<i)-b1[j]))&1;
		}
		for(int j=0; j<c0; ++j){
			res^=(std::lower_bound(b1,b1+c1,(1<<i)-b0[j])-b1)&1;
		}
		ans+=res<<i;
	}
	printf("%d\n",ans);
	return 0;
}
