#include<iostream>
#include<cstdio>
#include<cmath>
#include<cstring>
#include<cassert>
#include<set>
#include<map>
typedef long long lint;
std::set<int> st;
std::map<int,int>mp;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t,const int mod){
	lint ans=1;
	for(;t;x=x*x%mod,t>>=1){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

inline int solve(int b,int n,int p){
	b%=p,n%=p;
	if((!b&&n)||(b&&!n)) return -1;
	st.clear();
	mp.clear();
	const int m=ceil(sqrt(p)),mod=p;
	for(int i=1,j=(lint)n*b%mod;i<=m;j=(lint)j*b%mod,++i){
		st.insert(j);
//		printf("j%d\n",j);
		mp[j]=std::max(mp[j],i);
	}
	int t=qpow(b,m,mod);
	for(int i=1,j=t;i<=m;j=(lint)j*t%mod,++i){
		if(st.find(j)!=st.end()) return i*m-mp[j];
	}
	return -1;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1754.in","r",stdin);
#endif
	int b,n,p;
	while(~scanf("%d%d%d",&p,&b,&n)){
		const int ans=solve(b,n,p);
		if(ans==-1) puts("no solution");
		else printf("%d\n",ans);
	}
	return 0;
}
