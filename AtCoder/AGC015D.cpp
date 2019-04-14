#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int hbit(lint x){
	if(!x) return -1;
	int ans=0;
	for(int i=32; i; i>>=1){
		if(x>>i) ans+=i,x>>=i;
	}
	return ans;
}

inline lint solve(lint a,lint b){
	if(a==b) return 1;
	if(a>b) std::swap(a,b);
	int dpos=hbit(a^b);
	a&=(1ll<<(dpos+1))-1;
	b&=(1ll<<(dpos+1))-1;
	if(b!=1ll<<dpos) b|=(1ll<<hbit(b^1ll<<dpos))-1;
	return (((1ll<<dpos)-a)<<1)+std::min((a|1ll<<dpos)-1,b)-(1ll<<dpos)+1;
}

int main(){
#ifdef LOCAL
	freopen("d.in","r",stdin);
#endif
	lint a=nxi<lint>(),b=nxi<lint>();
	printf("%lld\n",solve(a,b));
}
