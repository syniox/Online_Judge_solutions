#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
const int N=1002;
typedef long long lint;
int n,sum,sp,pos,s1[N],s2[N];
lint dp[N][N][2];
//dp的值算上了不修的那些点的代价
struct data{
	int x,u;
	bool operator < (const data &b) const {
		return x<b.x;
	}
}dt[N];

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void solve(){
	int l=0,r=n+1;
	for(int i=1;i<=n;++i){
		if(dt[i].x<=pos) l=i;
		if(dt[i].x>=pos){
			r=i;
			break;
		}
	}
	for(int i=1;i<=n;++i){
		const lint tp=dp[i][i][0]=dp[i][i][1]=(lint)s1[n]*abs(pos-dt[i].x);
		for(int j=i+1;j<=l;++j) dp[i][l][0]=tp;
		for(int k=i-1;k>=r;--k) dp[k][i][1]=tp;
		for(int j=i-1;j;--j){
			apn(dp[j][i][0],dp[j+1][i][0]+(lint)(s1[j]+s2[i+1])*(dt[j+1].x-dt[j].x));
			apn(dp[j][i][0],dp[j+1][i][1]+(lint)(s1[j]+s2[i+1])*(dt[i].x-dt[j].x));
			apn(dp[j][i][1],dp[j][i-1][1]+(lint)(s1[j-1]+s2[i])*(dt[i].x-dt[i-1].x));
			apn(dp[j][i][1],dp[j][i-1][0]+(lint)(s1[j-1]+s2[i])*(dt[i].x-dt[j].x));
		}
	}

//	for(int i=1;i<=n;++i){
//		for(int j=i;j<=n;++j){
//			printf("%d %d: l%lld r%lld\n",i,j,dp[i][j][0],dp[i][j][1]);
//		}
//	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	memset(dp,1,sizeof(dp));
	n=nxi(),sp=nxi(),pos=nxi();
	for(int i=1;i<=n;++i){
		dt[i].x=nxi();
		sum+=nxi();
		dt[i].u=nxi();
	}
	std::sort(dt+1,dt+n+1);
	for(int i=1;i<=n;++i){
		s1[i]=s1[i-1]+dt[i].u;
	}
	for(int i=n;i;--i){
		s2[i]=s2[i+1]+dt[i].u;
	}
	solve();
	printf("%lld\n",std::min(dp[1][n][0],dp[1][n][1])/sp+sum);
	return 0;
}
