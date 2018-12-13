#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
const int N=1005;
int n,q,sv,dp[N][N];
int pre_p[N][N],pre_s[N][N];

struct items{
	int id,req,val,t;
}item[N];

bool cmp_req(const items &a,const items &b){
	return a.req<b.req;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void print(){
	static int stk[N];
	int top=0;
	printf("%d\n",dp[n][q]);
	for(int i=n,x=q;i;x=pre_s[i][x],--i){
		if(pre_p[i][x]) stk[++top]=pre_p[i][x];
	}
	for(;top;--top){
		printf("%d ",stk[top]);
	}
	puts("");
}

int main(){
	n=nxi(),q=nxi(),sv=nxi();
	for(int i=1;i<=n;++i){
		item[i].id=i;
		item[i].req=nxi(),item[i].val=nxi(),item[i].t=nxi();
	}
	std::sort(item+1,item+n+1,cmp_req);
	for(int i=0;i<=q;++i){
		dp[0][i]=sv;
	}
	for(int i=1;i<=n;++i){
		for(int j=0;j<=q;++j){
			dp[i][j]=dp[i-1][j];
			pre_s[i][j]=j;
			if(j<item[i].t) continue;
			int fr=j-item[i].t;
			if(dp[i-1][fr]>=item[i].req&&dp[i-1][fr]+item[i].val>=dp[i][j]){
				dp[i][j]=dp[i-1][fr]+item[i].val;
				pre_s[i][j]=fr;
				pre_p[i][j]=item[i].id;
			}
		}
	}
	print();
	return 0;
}
