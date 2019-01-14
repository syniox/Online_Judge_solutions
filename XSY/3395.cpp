#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cstdlib>
typedef long long lint;
const int N=1.2e7;
const int M=21;
const int mod=998244353;
int n,m,pos[M];
int fac[N],ifac[N];
int inv2n;
int pre_C[N<<1];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}
template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int C(int x,int y){
	if(x<y||x<0||y<0) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

inline void init(){
	inv2n=qpow(qpow(2,n),mod-2);
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[N-1]=qpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
	pre_C[0]=1;
	for(int i=1; i<=n; ++i){
		pre_C[i]=(pre_C[i-1]+C(n,i))%mod;
	}
}

inline int get_ans(int len){
	lint res;
	if((n&1)==(len&1)){
		int _lim=(n+len)>>1;
		res=(pre_C[n]-pre_C[_lim])<<1;
		res=(res+pre_C[_lim]-pre_C[_lim-1])%mod;
	}
	else{
		res=((pre_C[n]-pre_C[(n+len-1)>>1])<<1)%mod;
	}
	return res;
}

int main(){
	n=nxi(),m=nxi();
	init();
	for(int i=1; i<=m; ++i){
		pos[i]=nxi();
	}
	std::sort(pos+1,pos+m+1);
	int ans=0;
	for(int i=1,pt=-1e9; i<=m; ++i){
		for(apx(pt,pos[i]-n); pt<=pos[i]+n; ++pt){
			int res=1;
			for(int j=i; j<=m; ++j){
				if(pt<pos[j]-n) break;
				int len=abs(pos[j]-pt);
				res=res*(1-(lint)get_ans(len)*inv2n%mod)%mod;
			}
			if(res<0) res+=mod;
			ans=(ans+mod+1-res)%mod;
		}
	}
	twk(ans+=mod);
	printf("%d\n",ans);
	return 0;
}
