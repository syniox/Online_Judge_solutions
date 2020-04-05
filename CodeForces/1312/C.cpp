#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

bool good(){
	static bool vis[60];
	const int n=nxi(),q=nxi();
	assert(q!=1);
	memset(vis,0,sizeof(vis));
	bool vld=1;
	for(int i=1; i<=n; ++i){
		for(lint p=nxi(),j=0; vld&&p; p/=q,++j){
			if(p%q>1) vld=0;
			if(p%q==1){
				if(vis[j]) vld=0;
				vis[j]=1;
			}
		}
	}
	return vld;
}

int main(){
	for(int T=nxi(); T; --T){
		puts(good()?"YES":"NO");
	}
	return 0;
}
