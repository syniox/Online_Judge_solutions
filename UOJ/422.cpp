#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int mod=998244353;
int n,m,tot,dp[2][1<<6][1200];
char ch[7][120];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

inline void get_dp(){
	//dp[i][j][k]: 之前选的状态为j，k种情况至少覆盖一个选中点的选点方案数
	const int all=(1<<n)-1;
	dp[0][0][0]=mod-1;
	for(int i=1,p=1; i<=m; ++i){
		for(int j=1; j<=n; ++j,p^=1){
			memset(dp[p],0,sizeof(dp[p]));
			for(int k=0; k<1<<n; ++k){
				//枚举p^1
				for(int l=0; l<=tot; ++l){
					if(!dp[p^1][k][l]) continue;
					twk(dp[p][k&(all^1<<(j-1))][l]+=dp[p^1][k][l]);
					if(ch[j][i]=='.') continue;
					int delta=(j<n)+(i<m)+(i>1&&!(k>>(j-1)&1))+(j>1&&!(k>>(j-2)&1));
					twk(dp[p][k|1<<(j-1)][l+delta]+=mod-dp[p^1][k][l]);
				}
			}
			/*
			printf("at pos %d.\n",i);
			for(int k=0; k<=4; ++k){
				printf("status %d: ((end0)%d,(end1)%d,",k,dp[p][0][k],dp[p][1][k]);
				printf("((end2)%d,(end3)%d\n",dp[p][2][k],dp[p][3][k]);
			}
			puts("---");
			*/
		}
	}
}

int main(){
	n=nxi(),m=nxi();
	tot=n*(m-1)+(n-1)*m;
	for(int i=1; i<=n; ++i){
		scanf("%s",ch[i]+1);
	}
	get_dp();
	int ans=0;
	for(int i=1,p=n*m&1; i<=tot; ++i){
		const int res=(lint)tot*fpow(i,mod-2)%mod;
		for(int j=0; j<1<<n; ++j){
			ans=(ans+(lint)dp[p][j][i]*res)%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
