#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2,mod=10007;
int l,st,dp[N][3][2];
char ch[N];
bool used,ispr[10];

inline void init(){
	ispr[2]=ispr[3]=ispr[5]=ispr[7]=1;
}

inline void twk(int &x){
	if(x>=mod) x-=mod;
}

//d: top? p: all prime? p0: pre-0?
int dfs(int t,int s,bool d,bool p,bool p0){
	if(t==l) return s==st&&!p&&!p0;
	if(!d&&!p0&&dp[t][s][p]) return dp[t][s][p];
	const int limit=d?ch[t+1]:9;
	int ans=0;
	if(0<limit){
		twk(ans+=dfs(t+1,s,0,p0,p0));//
	}
	for(int i=1;i<limit;++i){
		twk(ans+=dfs(t+1,(s+i)%3,0,p&&ispr[i],0));
	}
	const bool f0=!limit&&p0;
	twk(ans+=dfs(t+1,(s+limit)%3,d,(p&&ispr[limit])||f0,f0));
//	printf("%d %d %d %d %d: %d\n",t,s,d,p,p0,ans);
	if(!d&&!p0) dp[t][s][p]=ans;
	return ans;
}

inline int solve(){
	memset(dp,0,sizeof(dp));
	scanf("%s",ch+1);
	l=strlen(ch+1);
	for(int i=1;i<=l;++i){
		ch[i]-='0';
		if(!used) st+=ch[i];
	}
	if(!used) st%=3;
	if(!used) used=1;
//	const int ans=dfs(0,0,1,1,1);
//	printf("%d\n",ans);
//	return ans;
	return dfs(0,0,1,1,1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	printf("%d\n",(solve()-solve()+mod)%mod);
	return 0;
}
