#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=45;
const int mod=1011110011;
//max: dp[n][cn][m]
int n,m,cn;
lint C[N][N],dp[N][N][N];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	C[0][0]=1;
	for(int i=1;i<N;++i) C[i][0]=1;
	for(int i=1;i<N;++i){
		for(int j=1;j<N;++j){
			C[i][j]=C[i-1][j-1]+C[i-1][j];
			if(C[i][j]>=mod) C[i][j]-=mod;
		}
	}
}

inline int get_pre(const int pre[N][N],int _x,int _y,int x,int y){
	const int a=(_y>1?pre[x][_y-1]:0);
	const int b=(_x>1?pre[_x-1][y]:0);
	const int c=(_x>1&&_y>1?pre[_x-1][_y-1]:0);
	return pre[x][y]-a-b+c;
}
inline void push_dp(const int t){
	for(int i=0;i<=cn;++i){
		for(int j=0;j<=m;++j){
			for(int k=0;k<=i;++k){
				for(int l=0;l<=j;++l){
					if(i-k+l>cn) break;
					dp[t+1][i-k+l][j-l]+=dp[t][i][j]*C[i][k]%mod*C[j][l]%mod;
				}
			}
		}
	}
	for(int i=0;i<=cn;++i){
		for(int j=0;j<=m;++j){
			dp[t+1][i][j]%=mod;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	n=nxi(),m=nxi(),cn=nxi();
	dp[0][0][m]=1;
	for(int i=0;i<n;++i){
		push_dp(i);
	}
	lint ans=0;
	for(int i=0;i<=cn;++i){
		twk(ans+=dp[n][i][0]);
	}
	printf("%lld\n",ans);
	return 0;
}
