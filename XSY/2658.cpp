#include<iostream>
#include<cstdio>
#include<algorithm>
#include<cstring>
typedef long long lint;
const int N=1002,T=3002;
int n,m,dp[T];
struct data{
	int a,b,c;
	bool operator < (const data &y) const {
		return (lint)c*y.b<(lint)y.c*b;
	}
}dt[N];

inline void apx(int &x,const int y){
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
	freopen("b.in","r",stdin);
#endif
	int T=nxi();
	while(T--){
		memset(dp,0,sizeof(dp));
		n=nxi(),m=nxi();
		for(int i=1;i<=n;++i){
			dt[i].a=nxi(),dt[i].b=nxi(),dt[i].c=nxi();
		}
		std::sort(dt+1,dt+n+1);
		for(int i=1;i<=n;++i){
			const data cur=dt[i];
			int ct;
			for(int j=m;j;--j){
				if((ct=j-cur.c)>=0) apx(dp[j],dp[ct]+cur.a-cur.b*j);
			}
		}
		int ans=0;
		for(int i=1;i<=m;++i){
			apx(ans,dp[i]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
