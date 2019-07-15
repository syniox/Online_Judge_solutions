#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
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

bool vld(const int x){
	int sz=val[x];
	for(int i=1; sz<=(int)1e9&&i<x; ++i){
		sz+=val[i];
	}
	for(int i=x+1; sz<=(int)1e9&&i<=n; ++i){
		if(sz*2<val[i]) return 0;
		sz+=val[i];
	}
	return 1;
}

int main(){
	n=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	std::sort(val+1,val+n+1);
	{
		int l=1,r=n,mid;
		while(l!=r){
			mid=(l+r)>>1;
			if(vld(mid)) r=mid;
			else l=mid+1;
		}
		printf("%d\n",n-l+1);
	}
	return 0;
}
