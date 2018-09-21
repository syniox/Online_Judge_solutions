#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2;
int n;
lint dp[2][3];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi();
	dp[1][0]=nxi();
	dp[1][1]=dp[1][2]=-1e13;
	for(int i=2;i<=n;++i){
		char op;
		while((op=getchar())!='-'&&op!='+');
		const int hx=nxi(),p=i&1;
		const int cur=hx*(op=='+'?1:-1);
		dp[p][0]=dp[p^1][0]+cur;
		dp[p][1]=dp[p^1][1]-cur;
		dp[p][2]=dp[p^1][2]+cur;
		apx(dp[p][1],dp[p][2]);
		apx(dp[p][0],dp[p][1]);
		if(op=='-'){
			apx(dp[p][1],dp[p^1][0]-hx);
			apx(dp[p][2],dp[p^1][1]+hx);
		}
	}
	lint ans=-1e16;
	for(int i=0;i<3;++i){
		apx(ans,dp[n&1][i]);
	}
	printf("%lld\n",ans);
	return 0;
}
