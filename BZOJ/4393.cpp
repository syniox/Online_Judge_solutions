#include <iostream>
#include <cstdio>
#include <cstring>
const int N=5e6+5;
bool dp[N];

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
	const int t=nxi(),a=nxi(),b=nxi();
	int ans=0;
	dp[0]=1;
	for(int i=1;i<=t;++i){
		if(i-a>=0) dp[i]|=dp[i-a];
		if(i-b>=0) dp[i]|=dp[i-b];
		if(dp[i]) ans=i;
	}
	for(int i=1;i<=t;++i){
		if(i<<1<=t) dp[i]|=dp[i<<1];
		if((i<<1|1)<=t) dp[i]|=dp[i<<1|1];
		if(i-a>=0) dp[i]|=dp[i-a];
		if(i-b>=0) dp[i]|=dp[i-b];
		if(dp[i]) apx(ans,i);
	}
	printf("%d\n",ans);
	return 0;
}
