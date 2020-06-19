#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,val[N];
lint m,pos[N],gain[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
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

lint solve(){
	static lint qsum[N];
	for(int i=1; i<=n; ++i){
		qsum[i]=qsum[i-1]+val[i]-pos[i]+pos[i-1];
	}
	for(int i=1; i<=n; ++i){
		apx(qsum[i],qsum[i-1]);
	}
	lint ss=0,ans=qsum[n];
	for(int i=n; i; --i){
		ss+=val[i];
		apx(ans,ss-(m-pos[i])*2+qsum[i-1]);
	}
	return ans;
}

int main(){
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		pos[i]=nxi(),val[i]=nxi();
	}
	lint ans=solve();
	for(int i=1; i<=n; ++i)
		pos[i]=m-pos[i];
	std::reverse(pos+1,pos+n+1);
	std::reverse(val+1,val+n+1);
	apx(ans,solve());
	printf("%lld\n",ans);
	return 0;
}
