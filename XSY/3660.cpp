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
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

bool jdg(const lint tgt){
	static lint dp[N+1][N+5];//i位以上，j个自由位时最少借位数
	memset(dp,30,sizeof(dp));
	dp[N][0]=0;
	for(int i=N; i; --i){
		for(int j=0; j<N-i+5; ++j){
			const lint cur=dp[i][j],req=cur*2+buk[i-1];
			if(cur>1ll<<60) continue;
			if(tgt>>(i-1)&1){
				lint use=std::min(req,n-((n^req)&1));
				lint nx_j=n-std::max(use,(lint)j)+j;
				if(req-use==0&&nx_j>=3) return 1;
				for(; use>=0&&nx_j<=n; use-=2,nx_j+=2){
					if(nx_j-j>=2&&nx_j>=5) break;
					apn(dp[i-1][nx_j],req-use);
				}
			}
			else{
				lint use=std::min(req,j-((j^req)&1));
				if(use<0) continue;
				if(j>2&&use==req) return 1;
				apn(dp[i-1][j],req-use);
			}
		}
	}
	for(int i=0; i<N+5; ++i){
		if(!dp[0][i]) return 1;
	}
	return 0;
}

lint rmain(){
	n=nxi(),s=nxi(),q=nxi();
	if(s<q||(s-q)&1) return -1;
	for(int i=0; i<N; ++i){
		buk[i]=(q>>i&1)+2*((s-q)>>(i+1)&1);
		if(buk[i]>n) return -1;
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
