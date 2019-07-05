#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1005;
const int mod=1e9+7;
int n,cnp,prm[N],buk[N];
bool npr[N];

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

void init(){
	npr[1]=1;
	for(int i=2; i<=n; ++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1; j<=cnp&&i*prm[j]<=n; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

int main(){
	n=nxi();
	init();
	for(int i=1; i<=cnp; ++i){
		for(int t=prm[i]; t<=n; t*=prm[i]){
			buk[i]+=n/t;
		}
	}
	int ans=1;
	for(int i=1; i<=cnp; ++i){
		ans=(lint)ans*(buk[i]+1)%mod;
	}
	printf("%d\n",ans);
	return 0;
}
