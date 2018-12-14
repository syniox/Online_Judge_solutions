#include <iostream>
#include <cstdio>
#include <cstring>
const int N=1e5+5;
//dp[0]记录下降序列最高在多少
//dp[1]记录上升序列最低在多少
int n,hx[N],dp[2][N];
bool frm[2][N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(const int l){
	memset(dp[0],0,(l+1)<<2);
	memset(dp[1],1,(l+1)<<2);
	dp[0][0]=N;
	dp[0][1]=0;
}

inline bool solve(){
	for(int i=1; i<=n; ++i){
		if(hx[i]>hx[i-1]){
			dp[0][i]=dp[0][i-1];
			frm[0][i]=0;
		}
		else{
			dp[1][i]=dp[1][i-1];
			frm[1][i]=1;
		}
		if(hx[i]>dp[1][i-1]&&dp[0][i]<hx[i-1]){
			dp[0][i]=hx[i-1];
			frm[0][i]=1;
		}
		if(hx[i]<dp[0][i-1]&&dp[1][i]>hx[i-1]){
			dp[1][i]=hx[i-1];
			frm[1][i]=0;
		}
		if(!dp[0][i]&&dp[1][i]>=N) return 0;
	}
	return 1;
}

inline void print_seq(){
	static int buk[2][N];
	int pt[2]={0,0};
	bool cur;
	if(dp[0][n]) cur=0;
	else cur=1;
	for(int i=n; i; --i){
		buk[cur][++pt[cur]]=hx[i];
		cur=frm[cur][i];
	}
	puts("YES");
	for(int i=0; i<2; ++i){
		printf("%d ",pt[i]);
		for(int j=pt[i]; j; --j){
			printf("%d ",buk[i][j]);
		}
		puts("");
	}
}

int main(){
	for(int T=nxi(); T; --T){
		n=nxi();
		init(n);
		for(int i=1; i<=n; ++i){
			hx[i]=nxi();
		}
		if(solve()) print_seq();
		else puts("NO");
	}
	return 0;
}
