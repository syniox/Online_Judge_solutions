#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1e5+2; 
const int mod=1e5+3;
bool mk[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline lint qpow(lint x,int t){
	lint ans=1;
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) ans=ans*x%mod;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	int n,q,cnt=0,ans=0;
	lint fac=1;
	n=nxi(),q=nxi();

	for(int i=1;i<=n;++i){
		mk[i]=nxi();
		fac=fac*i%mod;
	}
	for(int i=n;i;--i){
		bool p=mk[i];
		for(int j=i*2;j<=n;++j){
			if(mk[j]) p^=1;
		}
		cnt+=mk[i]=p;
	}
	if(cnt<=q){
		printf("%lld\n",(lint)cnt*fac%mod);
		return 0;
	}
	int pre=0;
	for(int i=n;i>cnt;--i){
		pre=(1+(lint)(n-i)*qpow(i,mod-2)%mod*(pre+1))%mod;
	}
	for(int i=cnt;i>q;--i){
		pre=(1+(lint)(n-i)*qpow(i,mod-2)%mod*(pre+1))%mod;
		ans+=pre;
		if(ans>=mod) ans-=mod;
	}
	printf("%lld\n",(ans+q)*fac%mod);
	return 0;
}
