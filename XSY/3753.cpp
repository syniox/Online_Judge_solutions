#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <map>
using namespace std;
typedef long long lint;
const lint N=5e9+5;
const int S=1.4e7;
const int mod=1e9+7;
const int inv2=(mod+1)>>1;
const int inv6=(mod+1)/6;
lint n,m;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct sieve_s{//f*g=h
	map<lint,int> mp;
	int v[S];
	virtual int g(const lint x)=0;
	virtual int h(const lint x)=0;
	void par(){
		for(int i=2; i<S; ++i) v[i]=(v[i]+v[i-1])%mod;
	}
	int operator()(const lint x){
		if(x<S) return v[x];
		map<lint,int>::iterator it=mp.find(x);
		if(it!=mp.end()) return it->second;
		int ans=h(x);
		for(lint i=2,j; i<=x; i=j+1){
			j=x/(x/i);
			ans=(ans-(lint)(g(j)+mod-g(i-1))*(*this)(x/i))%mod;
		}
		return mp[x]=(ans+mod)%mod;
	}

	void check(const int n){
		for(int i=1; i<=n; ++i){
			eprintf("%d ",(*this)(i));
		}
		eprintf("\n");
	}
};

struct s0_s:sieve_s{
	int g(const lint x){return x%mod;}
	int h(const lint x){return 1;}
}s0;
struct s1_s:sieve_s{
	int g(const lint x){return x%mod*(x+1)%mod*inv2%mod;}
	int h(const lint x){return 1;}
}s1;
struct s2_s:sieve_s{
	int g(const lint x){return x%mod*(x+1)%mod*(x*2%mod+1)%mod*inv6%mod;}
	int h(const lint x){return 1;}
}s2;

void preload(){
	static int mu[S],prm[S/5];
	static bool npr[S];
	int cnp=0;
	mu[1]=1;
	for(int i=2; i<S; ++i){
		if(!npr[i]){
			mu[i]=mod-1;
			prm[++cnp]=i;
		}
		for(int j=1; j<=cnp&&i*prm[j]<S; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
			mu[i*prm[j]]=mod-mu[i];
		}
	}
	memcpy(s0.v,mu,sizeof(mu));
	for(int i=1; i<S; ++i) mu[i]=(lint)mu[i]*i%mod;
	memcpy(s1.v,mu,sizeof(mu));
	for(int i=1; i<S; ++i) mu[i]=(lint)mu[i]*i%mod;
	memcpy(s2.v,mu,sizeof(mu));
	s0.par(),s1.par(),s2.par();
}

inline int psum(const lint n){
	return n%mod*(n+1)%mod*inv2%mod;
}
int q0(const lint d){
	return n%mod*m%mod*(n/d)%mod*(m/d)%mod;
}
int q1(const lint d){
	int nd=(n/d)%mod,md=(m/d)%mod;
	int r1=md*m%mod*psum(nd)%mod;
	int r2=nd*n%mod*psum(md)%mod;
	return (r1+r2)%mod;
}
int q2(const lint d){
	return (lint)psum(m/d)*psum(n/d)%mod;
}

int main(){
	n=nxi(),m=nxi();
	preload();
	int ans=0;
	for(lint j,i=1; i<=min(n,m); i=j+1){
		j=min(n/(n/i),m/(m/i));
		ans=(ans+(lint)(s0(j)+mod-s0(i-1))*q0(i))%mod;
		ans=(ans-(lint)(s1(j)+mod-s1(i-1))*q1(i))%mod;
		ans=(ans+(lint)(s2(j)+mod-s2(i-1))*q2(i))%mod;
	}
	ans=(ans+mod)%mod;
	ans=4ll*ans%mod;
	printf("%d\n",ans);
	return 0;
}

