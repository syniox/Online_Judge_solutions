#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+5;
const int mod=1e9+7;
int n,pre_dp[N][2];
lint lim_a,lim_b,val[N];

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int get_dp(int l,int r,bool type){
	if(l>r) return 0;
	return (pre_dp[r][type]-(l>0?pre_dp[l-1][type]:0)+mod)%mod;
}

int main(){
	n=nxi<int>();
	lim_a=nxi<lint>(),lim_b=nxi<lint>();
	for(int i=1; i<=n; ++i){
		val[i]=nxi<lint>();
	}
	val[0]=-2e18,val[n+1]=2e18;
	pre_dp[0][0]=pre_dp[0][1]=1;
	for(int ptl_a=0,ptl_b=0,ptr_a=-1,ptr_b=-1,i=1; i<=n; ++i){
		if(val[i]-val[i-1]<lim_a) ptl_a=i-1;
		if(val[i]-val[i-1]<lim_b) ptl_b=i-1;
		while(ptr_a<i-1&&val[i+1]-val[ptr_a+1]>=lim_b) ++ptr_a;
		while(ptr_b<i-1&&val[i+1]-val[ptr_b+1]>=lim_a) ++ptr_b;
		pre_dp[i][0]=(pre_dp[i-1][0]+get_dp(ptl_a,ptr_a,1))%mod;
		pre_dp[i][1]=(pre_dp[i-1][1]+get_dp(ptl_b,ptr_b,0))%mod;
	}
	const int ans_0=(pre_dp[n][0]-pre_dp[n-1][0]+mod)%mod;
	const int ans_1=(pre_dp[n][1]-pre_dp[n-1][1]+mod)%mod;
	printf("%d\n",(ans_0+ans_1)%mod);
	return 0;
}
