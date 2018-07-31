#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int mod=1e9+7;
const int N=1e6+5;
int n,cnp,prm[N];
bool npr[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t){
	lint ans(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

struct Djs{
	bool vis[(int)1e3+5];
	lint a[N],b[N];
	virtual lint adj (int x)=0;
	virtual lint dirch (int x)=0;

	lint operator () (int x){
		if(x<N) return a[x];
		const int dv=n/x;
		if(vis[dv]) return b[dv];
		vis[dv]=1;
		lint ans=dirch(x);
		for(int i=2,j=x/i,d;i<=x;i=d+1,j=x/i){
			d=x/j;
			ans=((ans-(adj(d)-adj(i-1))*(*this)(j))%mod+mod)%mod;
		}
		return b[dv]=ans;
	}
};

struct Phi:Djs{
	virtual lint adj(int x){
		static const int inv2=qpow(2,mod-2);
		return (lint)x*(x+1)%mod*inv2%mod;
	}
	virtual lint dirch(int x){
		static const int inv6=qpow(6,mod-2);
		return (lint)x*(x+1)%mod*(x<<1|1)%mod*inv6%mod;
	}
}phi;

inline void init(){
	phi.a[1]=1;
	for(int i=2;i<N;++i){
		if(!npr[i]){
			prm[++cnp]=i;
			phi.a[i]=i-1;
		}
		for(int j=1;j<=cnp&&i*prm[j]<N;++j){
			npr[i*prm[j]]=N;
			if(i%prm[j]==0){
				phi.a[i*prm[j]]=phi.a[i]*prm[j];
				break;
			}
			phi.a[i*prm[j]]=phi.a[i]*(prm[j]-1);
		}
		phi.a[i]=(phi.a[i]*i%mod+phi.a[i-1])%mod;
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
#endif
	init();
	n=nxi();
	printf("1\n%lld\n",phi(n));
	return 0;
}
