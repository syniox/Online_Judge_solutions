#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=1005;
int n,len,dp[2][N][N],decide[N][N];
char ch[N][52];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void solve(const int cur_t){
	static int prs[N];
	const bool p=cur_t&1;
	memset(dp[p],0,sizeof(dp[p]));
	for(int i=1;i<=n;++i){
		prs[i]=prs[i-1]+(ch[i][cur_t]=='1');
	}
	int (*fp)[N]=dp[p^1];
	for(int i=1;i<=n;++i){
		decide[i][i]=ch[i][cur_t]=='1'?i-1:i;
		for(int j=i-1;j;--j){
			int &cur=dp[p][j][i]=1e9;
			for(int k=decide[j][i-1];k<=decide[j+1][i];++k){
				const int to_0=prs[k]-prs[j-1];
				const int to_1=i-k-(prs[i]-prs[k]);
				const int v=fp[j][k]+to_0+fp[k+1][i]+to_1;
				assert(v>=0);
				if(v<cur){
					cur=v,decide[j][i]=k;
				}
			}
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("p.in","r",stdin);
#endif
	n=nxi(),len=nxi();
	for(int i=1;i<=n;++i){
		scanf("%s",ch[i]+1);
	}
	for(int i=len;i;--i){
		solve(i);
	}
	printf("%d\n",dp[1][1][n]);
	return 0;
}
