#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=2e5+5;
const int S=10;
int n,q,mod,dp[N];
int mtx[S+5][S],res[S];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline int nxi(){
		int x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

inline int id(const int i,const int j){
	return i*3+j;
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

void get_dp(){
	static const int N=20;
	static int f[N+1][N+1][N+1];
	dp[0]=1;
	f[1][0][0]=1;
	for(int i=1; i<N; ++i){
		for(int j=0; j<i; ++j){
			for(int k=0; k<i; ++k){
				const int cur=f[i][j][k];
				if(!cur) continue;
				for(int l=1; l<=i+1; ++l){//第1个元素在加入后的排名
					if(l<=j) continue;
					int nx_j=max(j+(j>=l),l<=k?l:0);
					int nx_k=max(k+(k>=l),l-1);
					f[i+1][nx_j][nx_k]=(f[i+1][nx_j][nx_k]+cur)%mod;
				}
				dp[i]=(dp[i]+cur)%mod;
			}
		}
	}
}

void gauss(){
	static bool free[N];
	for(int i=0; i<9; ++i){
		int j=i;
		for(; j<12&&!mtx[j][i]; ++j);
		if(j==12){
			free[i]=1;
			continue;
		}
		if(j!=i){
			for(int k=0; k<9; ++k){
				swap(mtx[j][k],mtx[i][k]);
			}
		}
		for(int k=i+1; k<12; ++k){
			int wgt=(lint)(mod-mtx[k][i])*fpow(mtx[i][i],mod-2)%mod;
			for(int l=i; l<9; ++l){
				mtx[k][l]=(mtx[k][l]+(lint)mtx[i][l]*wgt)%mod;
			}
		}
	}
	bool f=0;
	for(int i=0; i<9; ++i){
		if(free[i]) res[i]=f=1;
	}
	assert(f);
	for(int i=8; ~i; --i){
		if(free[i]) continue;
		assert(mtx[i][i]);
		int scc=0;
		for(int j=i+1; j<9; ++j){
			scc=(scc+(lint)res[j]*mtx[i][j])%mod;
		}
		res[i]=(lint)fpow(mtx[i][i],mod-2)*(mod-scc)%mod;
	}
	/*
	for(int i=0; i<8; ++i){
		eprintf("%d ",res[i]);
	}
	eprintf("\n");
	*/
}

int prf(int *res,const int n){
	return (res[0]+(lint)res[1]*n+(lint)res[2]*n%mod*n)%mod;
}

int calc(const int n){
	int w=prf(res,n),w1=prf(res+3,n),w2=prf(res+6,n);
	int sum=((lint)w2*dp[n-2]+(lint)w1*dp[n-1])%mod;
	return (lint)sum*fpow(w,mod-2)%mod;
}

int main(){
	q=nxi(),mod=nxi();
	get_dp();
	/*
	dp[1]=1,dp[2]=1;
	for(int i=3; i<15; ++i){
		dp[i]=(dp[i-1]+dp[i-2])%mod;
	}
	*/
	for(int i=3; i<15; ++i){
		for(int j=0; j<3; ++j){
			for(int k=0,w=1; k<3; ++k,w*=i){
				int tmp=(lint)dp[i-j]*w%mod;
				mtx[i-3][id(j,k)]=j==0?mod-tmp:tmp;
			}
		}
	}
	gauss();
	for(int i=20; i<N; ++i){
		dp[i]=calc(i);
	}
	while(q--){
		printf("%d\n",dp[nxi()]);
	}
	return 0;
}
