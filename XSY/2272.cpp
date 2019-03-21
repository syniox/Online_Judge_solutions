#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e6+5;
int n,mx,buk[N];
lint dp[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
	n=nxi();
	for(int x,i=1; i<=n; ++i){
		++buk[x=nxi()];
		apx(mx,x);
	}
	for(int i=1; i<=mx; ++i){
		dp[i]=(lint)i*buk[i];
	}
	for(int i=0; 1<<i<=mx; ++i){
		for(int j=1; j<=mx; ++j){
			if(j>>i&1) buk[j-(1<<i)]+=buk[j];
		}
	}
	for(int i=mx; i; --i){
		for(int j=0; 1<<j<=i; ++j){
			if(!(i>>j&1)) continue;
			const int tgt=i^(1<<j);
			apx(dp[tgt],dp[i]+(lint)tgt*(buk[tgt]-buk[i]));
		}
	}
	printf("%lld\n",dp[0]);
	return 0;
}
