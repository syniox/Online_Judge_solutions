#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
int n,tot,imp[N],ans[N],lst[N],nxt[N];
bool bimp[N];

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

int dis(const int x,const int y){
	return x<=y?y-x:y+n-x;
}

void solve(){
	int mn=1e9;
	for(int i=1; i<=n; ++i){
		apn(mn,n-i+dis(i,lst[i]));
	}
	for(int i=1; i<=n; ++i){
		mn=std::min(mn+1,dis(i,lst[i]));
		apn(ans[i],mn);
	}
	mn=1e9;
	for(int i=n; i>=1; --i){
		apn(mn,i-1+dis(nxt[i],i));
	}
	for(int i=n; i>=1; --i){
		mn=std::min(mn+1,dis(nxt[i],i));
		apn(ans[i],mn);
	}
}

int main(){
	memset(ans,10,sizeof(ans));
	n=nxi();
	for(int i=2; i<=n; ++i){
		imp[i-1]=(nxi()-i+1+n-1)%n+1;
	}
	std::sort(imp+1,imp+n);
	tot=std::unique(imp+1,imp+n)-imp-1;
	if(tot==1){
		for(int i=1; i<=n; ++i){
			printf("%d\n",std::min(i-1,n+1-i)+std::min(dis(i,imp[1]),dis(imp[1],i)));
		}
		return 0;
	}
	for(int i=1; i<=tot; ++i){
		bimp[imp[i]]=1;
	}
	for(int l=0,i=1; !lst[i]; i=i%n+1){
		if(l) lst[i]=l;
		if(bimp[i]) l=i;
	}
	for(int i=n,nx=0; !nxt[i]; i=(i+n-2)%n+1){
		if(nx) nxt[i]=nx;
		if(bimp[i]) nx=i;
	}
	solve();
	for(int i=1; i<=n; ++i){
		printf("%d\n",std::min(i-1,n+1-i)+ans[i]);
	}
	return 0;
}
