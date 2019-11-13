#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,m,va[N],vb[N];
int cntb,cb[N*30];

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
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		va[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		vb[i]=nxi();
	}
	for(int i=1; i<=m; ++i){
		for(int j=0; j<30; ++j){
			cb[++cntb]=vb[i]^(1<<j);
		}
	}
	std::sort(cb+1,cb+cntb+1);
	lint ans=0;
	for(int i=1; i<=n; ++i){
		for(int j=0; j<30; ++j){
			int tgt=va[i]^1<<j;
			int lp=std::lower_bound(cb+1,cb+cntb+1,tgt)-cb;
			if(cb[lp]!=tgt) continue;
			int up=std::upper_bound(cb+1,cb+cntb+1,tgt)-cb;
			ans+=up-lp;
		}
	}
	std::sort(vb+1,vb+m+1);
	for(int i=1; i<=n; ++i){
		int lp=std::lower_bound(vb+1,vb+m+1,va[i])-vb;
		if(vb[lp]!=va[i]) continue;
		int up=std::upper_bound(vb+1,vb+m+1,va[i])-vb;
		ans-=(up-lp)*30;
	}
	printf("%lld\n",ans/2);
	return 0;
}
