#include<iostream>
#include<cstdio>
#include<cstring>
const int N=405;
//ha: help attack
int n,ak,at[N],ha[N],hp[N],tme[N],dp[N][N];

inline void apn(int &x,const int y){
	if(x>y) x=y;
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
	n=nxi(),ak=nxi();
	for(int i=1;i<=n;++i){
		at[i]=nxi(),ha[i]=nxi(),hp[i]=nxi();
		tme[i]=(hp[i]+ak-1)/ak;
	}
	for(int i=1;i<=n;++i){
		dp[i][i]=(ha[i-1]+ha[i+1]+at[i])*tme[i];
		for(int j=i-1;j;--j){
			dp[j][i]=1e9;
			for(int k=j;k<=i;++k){
				apn(dp[j][i],dp[j][k-1]+dp[k+1][i]+(at[k]+ha[j-1]+ha[i+1])*tme[k]);
			}
		}
	}
	printf("%d\n",dp[1][n]);
	return 0;
}
