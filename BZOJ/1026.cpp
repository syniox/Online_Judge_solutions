#include<iostream>
#include<cstdio>
#include<cstring>
const int N=12;
typedef long long lint;
int l,lt[N];
lint dp[N][10];

inline void get_lt(int t){
	l=0;
	while(t){
		const int tp=t/10;
		lt[++l]=t-tp*10;
		t=tp;
	}
	if(!l) lt[++l]=0;
}

lint dfs(const int t,const int x,const bool d,const bool p0){
	if(t==1) return 1;
	if(!d&&!p0&&dp[t][x]) return dp[t][x];
	lint ans=0;
	const int limit=d?lt[t-1]:9;
	const int t1=std::min(limit,x-2);
	for(int i=0;i<=t1;++i){
		ans+=dfs(t-1,i,d&&(i==limit),p0&&i==0);
	}
	for(int i=p0?0:x+2;i<=limit;++i){
		ans+=dfs(t-1,i,d&&(i==limit),p0&&i==0);
	}
	if(!d&&!p0) dp[t][x]=ans;
	return ans;
}

inline lint solve(const int t){
	get_lt(t);
	const lint ans=dfs(l+1,0,1,1);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	lint l,r;
	scanf("%lld%lld\n",&l,&r);
	printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}
