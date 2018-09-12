#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=20,Y=164;
int l,f_mod,lt[N];
lint dp[N][Y][Y];
bool vis[N][Y][Y];

template <class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}
//d: top? s: sum f: cur%mod
lint dfs(const int t,const int s,const int f,const bool d){
	if(!d&&vis[t][s][f]) return dp[t][s][f];
	if(t==1) return f==0&&s==f_mod;
	const int mod=f_mod,limit=d?lt[t-1]:9;
	lint ans=0;
	int p=f*10%mod;
	for(int i=0;i<=limit;++i){
		ans+=dfs(t-1,s+i,p,d&&i==limit);
		if(++p==mod) p=0;
	}
	if(!d) vis[t][s][f]=1,dp[t][s][f]=ans;
	return ans;
}

inline lint solve(lint t){
	l=0;
	while(t){
		const lint tp=t/10;
		lt[++l]=t-tp*10;
		t=tp;
	}
	lint ans=0;
	const int limit=std::min(l*9,18*9);
	for(int i=1;i<=limit;++i){
		memset(vis,0,sizeof(vis));
		f_mod=i;
		ans+=dfs(l+1,0,0,1);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	lint l=nxi<lint>(),r=nxi<lint>();
	printf("%lld\n",solve(r)-solve(l-1));
	return 0;
}
