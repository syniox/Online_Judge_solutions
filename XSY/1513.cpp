#include<iostream>
#include<cstdio>
#include<cstring>
const int N=1e5+2,mod=10007;
int l,st,dp[N][3];
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
	if(t==l) return s==st&&!p0;
	if(!d&&!p&&!p0&&dp[t][s]) return dp[t][s];
	const int limit=d?ch[t+1]:9;
	int ans=0;
	if(0<limit){
		twk(ans+=dfs(t+1,s,0,p0||p,p0));
	}
	for(int i=1;i<limit;++i){
		twk(ans+=dfs(t+1,(s+i)%3,0,p&&ispr[i],0));
	}
	twk(ans+=dfs(t+1,(s+limit)%3,d,p&&(ispr[limit]||(!limit&&p0)),p0&&!limit));
	if(!d&&!p&&!p0) dp[t][s]=ans;
	return ans;
}

inline int solve(){
	scanf("%s",ch+1);
	l=strlen(ch+1);
	if(st) used=1;
	for(int i=1;i<=l;++i){
		ch[i]-='0';
		if(!used) st+=ch[i];
	}
	st%=3;
	int ans=dfs(0,0,1,1,1);
	printf("%d\n",ans);
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	init();
	printf("%d\n",(solve()-solve()+mod)%mod);
	return 0;
}
