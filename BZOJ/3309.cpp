#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=1e7+5;//!!!!
int dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

void sieve(){
	static int cnp,prm[N],plst[N],pcur[N];
	static bool npr[N],pcnt[N];
	dp[1]=0;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			pcur[i]=dp[i]=pcnt[i]=1;
			prm[++cnp]=i;
		}
		for(int j=1,k=i*prm[j]; j<=cnp&&k<N; ++j,k=i*prm[j]){
			npr[k]=1;
			if(i%prm[j]==0){
				pcur[k]=pcur[i]+1;
				plst[k]=plst[i];
				pcnt[k]=pcnt[i];
				dp[k]=(!plst[k]||plst[k]==pcur[k])?(pcnt[k]*2-1):0;
				break;
			}
			pcur[k]=1;
			const bool f=!plst[i]||plst[i]==pcur[i];
			plst[k]=f?pcur[i]:-1;
			pcnt[k]=pcnt[i]^1;
			dp[k]=f&&pcur[i]==1?(pcnt[k]*2-1):0;
		}
	}
	for(int i=1; i<N; ++i){
		dp[i]+=dp[i-1];
	}
}

int main(){
	sieve();
	for(int T=nxi(); T; --T){
		int a=nxi(),b=nxi();
		if(a>b) std::swap(a,b);
		lint ans=0;
		for(int i=1,j; i<=a; i=j+1){
			j=std::min(a/(a/i),b/(b/i));
			ans+=(lint)(a/i)*(b/i)*(dp[j]-dp[i-1]);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
