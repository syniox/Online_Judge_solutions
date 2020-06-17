#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e7+5;
const int mod=20101009;
int mu[N],ms2[N];
//ms2[n]: \sum _ {i=1} ^ n mu[i]*i*i

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=c=='-'&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

void init(){
	static int cnp,prm[N/10];
	static bool npr[N];
	mu[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i])
			mu[prm[++cnp]=i]=-1;
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
			mu[i*prm[j]]=-mu[i];
		}
	}
	for(int i=1; i<N; ++i){
		ms2[i]=(ms2[i-1]+(lint)mu[i]*i%mod*i)%mod;
	}
}

inline int getg(const int x,const int y){
	return (lint)x*(x+1)/2%mod*((lint)y*(y+1)/2%mod)%mod;
}

int getsum(const int x,const int y){
	int ans=0;
	for(int i=1,j=1; i<=std::min(x,y); i=j+1){
		j=std::min(x/(x/i),y/(y/i));
		ans=(ans+(lint)(ms2[j]-ms2[i-1])*getg(x/i,y/i))%mod;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	init();
	int n=nxi(),m=nxi(),ans=0;
	for(int i=1,j=1; i<=std::min(n,m); i=j+1){
		j=std::min(n/(n/i),m/(m/i));
		ans=(ans+(lint)(i+j)*(j-i+1)/2%mod*getsum(n/i,m/i))%mod;
	}
	printf("%d\n",(ans+mod)%mod);
	return 0;
}
