#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=60;
lint n,s,q;
int buk[N];

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

bool jdg(const lint lim){
	static lint dp[N+1][N+8];
	memset(dp,30,sizeof(dp));
	dp[N][0]=0;
	for(int i=N; i; --i){
		for(int j=0; j<=N-i+5; ++j){
			if(dp[i][j]>1ll<<60) continue;
			lint req=dp[i][j]*2+buk[i-1];
			lint use=std::min(lim>>i&1?n:(lint)j,req);
			use-=(use&1)^(q&1);
			lint nx_j=n-std::max(j,use)+j;
			if(j>=3){

			}
			//apn(dp[i-1][nx_j],req-use);
		}
	}
	for(int i=std::min((lint)N,n); ~i; --i){
		if(dp[0][i]==0) return 1;
	}
	return 0;
}

lint rmain(){
	n=nxi(),s=nxi(),q=nxi();
	if(s<q||((s-q)&1)) return -1;
	if(n==1) return s==q?s:-1;
	if(n==2) return (!q)&&s%2==0?s>>1:-1;
	for(int i=N-1; ~i; --i){
		buk[i]=(q>>i&1)+((s-q)>>(i+1))*2;
	}
	lint l=s/n,r=s,mid;
	while(l!=r){
		mid=(l+r)>>1;
		if(jdg(mid)) r=mid;
		else l=mid+1;
	}
	return l;
}

int main(){
	for(int T=nxi(); T; --T){
		printf("%lld\n",rmain());
	}
	return 0;
}
