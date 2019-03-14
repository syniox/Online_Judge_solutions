#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1005;
int n,m,lim,to_l[N],to_r[N],dp[N][20005];
//dp[i][j]: 不能让出现在后面的人往前跑时有j个人能到第i间房的方案数?
//(涵盖所有情况?)

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
	memset(dp,-4,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=1; i<n; ++i){
		to_r[i]=nxi();
		to_l[i+1]=nxi();
		apx(lim,to_r[i]+to_l[i+1]);
	}
	for(int i=0; i<m; ++i){
		dp[1][i]=i;
	}
	int ans=m-1;
	for(int i=1; i<=n; ++i){
		//1左n右
		//在任何时候都不能放右边一个人过来?
		int mx=-1e9;
		//无法从任意一边打开
		for(int j=0; j<to_r[i]; ++j){
			apx(mx,dp[i][j]);
		}
		for(int j=0; j<to_l[i+1]; ++j){
			apx(dp[i+1][j],mx+j);
		}
		//只能从右边打开
		for(int j=0; j<to_r[i]; ++j){
			apx(dp[i+1][j+to_l[i+1]],to_l[i+1]+dp[i][j]);
		}
		//能从左边打开时右边开始都不能有人
		//只能从左边打开
		for(int j=to_r[i]; j<to_r[i]+to_l[i+1]; ++j){
			apx(dp[i+1][j-to_r[i]],dp[i][j]);
		}
		//人数足够来回接应
		for(int j=to_r[i]+to_l[i+1]; j<=lim; ++j){
			apx(dp[i+1][j],dp[i][j]);
		}
	}
	for(int i=0; i<=lim; ++i){
		apx(ans,dp[n][i]);
	}
	printf("%d\n",ans);
	return 0;
}
