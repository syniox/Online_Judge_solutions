#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=1e9,S=1e6+5;
const int mod=1e9+7;
int n,q,inv1q,pf[S];

struct sieve_s{//f*g=h
	int v[S],cache[N/S+5];
	bool vis[N/S+5];
	virtual int g(const int x)=0;
	virtual int h(const int x)=0;
	int operator()(const int x);
};
struct mu0_s:sieve_s{
	int g(const int x){ return x; }
	int h(const int x){ return 1; }
}mu0;
struct mu1_s:sieve_s{
	int g(const int x){ return ((lint)x*(x+1)>>1)%mod; }
	int h(const int x){ return 1; }
}mu1;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}
void par(int v[]){
	for(int i=2; i<S; ++i) v[i]=(v[i]+v[i-1])%mod;
}

int sieve_s::operator()(const int x){
	if(x<S) return v[x];
	if(vis[n/x]) return cache[n/x];
	vis[n/x]=1;
	int ans=h(x);
	for(int j,i=2; i<=x; i=j+1){
		j=x/(x/i);
		ans=(ans-lint(g(j)-g(i-1))*(*this)(x/i))%mod;
	}
	ans=(ans+mod)%mod;
	return cache[n/x]=ans;
}

void preload(){
	static int mu[S],prm[S];
	static bool npr[S];
	pf[1]=mu[1]=1;
	for(int cnp=0,i=2; i<S; ++i){
		if(!npr[i]){
			mu[prm[++cnp]=i]=mod-1;
			pf[i]=mod+1-i;
		}
		for(int j=1,k; j<=cnp&&(k=i*prm[j])<S; ++j){
			npr[k]=1;
			pf[k]=pf[i];
			if(i%prm[j]==0) break; 
			pf[k]=(lint)pf[i]*pf[prm[j]]%mod;
			mu[k]=-mu[i];
		}
	}
	memcpy(mu0.v,mu,sizeof(mu0.v));
	for(int i=1; i<S; ++i) mu[i]=(lint)mu[i]*i%mod;
	memcpy(mu1.v,mu,sizeof(mu1.v));
	par(mu0.v),par(mu1.v),par(pf);
}

int qici(const int n){//sum_ i i*c^i
	int res=(lint)q*inv1q%mod*inv1q%mod;
	res=(res-((lint)inv1q*inv1q%mod+lint(n)*inv1q%mod)*fpow(q,n+1))%mod;
	return (res+mod)%mod;
}
int qwG(const int n){
	int res1=((2ll*qici((n+1)>>1)-(lint)inv1q*(q-fpow(q,((n+1)>>1)+1)))%mod+mod)%mod;
	int res2=(lint)qici(n>>1)*(q+1)%mod;
	return (res1+res2)%mod;
}
int qT2(const int n){
	int pw=fpow(q,n/2+1);
	int res=2ll*inv1q%mod*(q-pw+mod)%mod;
	if(n&1) res=(res+pw)%mod;
	return res;
}

int qpF(const int n){
	if(n<S) return pf[n];
	int ans=0;
	for(int lst=0,cur,i=1,j; i<=n; i=j+1){
		j=n/(n/i);
		cur=mu1(j);
		ans=(ans+lint(cur-lst)*(n/i))%mod;
		lst=cur;
	}
	return ans;
}

int main(){
	preload();
	n=ni,q=ni;
	inv1q=fpow(1-q+mod,mod-2);
	int ans=0;
	for(int j,i=1; i<=n; i=j+1){
		j=n/(n/i);
		ans=(ans+lint(qwG(j)-qwG(i-1))*qpF(n/i))%mod;
		ans=(ans-lint(qT2(j)-qT2(i-1))*mu0(n/i))%mod;
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
