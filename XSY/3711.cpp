#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int K=11,M=20;
const int mod=1e9+7;
int n,m,inv[10005],res[1<<M];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
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

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

struct num0{
	int v,c0;
	num0(int val,int cnt0):v(val),c0(cnt0){}
	num0():v(1),c0(0){}
	void operator=(const int v){
		if(v==0) c0=1,this->v=1;
		else this->v=v,c0=0;
	}
	num0 qinv()const{
		return (num0){fpow(v,mod-2),-c0};
	}
	int qval()const{
		return c0?0:v;
	}
	friend num0 operator*(const num0 &a,const num0 &b){
		return (num0){(int)((lint)a.v*b.v%mod),a.c0+b.c0};
	}
	num0 operator*(const int x)const{
		if(x==0) return (num0){v,c0+1};
		return (num0){(int)((lint)v*x%mod),c0};
	}
	num0& operator*=(const num0 &b){
		return *this=*this*b;
	}
}dp[1<<M];

int main(){
	inv[0]=inv[1]=1;
	for(int i=2; i<=10000; ++i){
		inv[i]=(lint)mod/i*(mod-inv[mod%i])%mod;
	}
	n=nxi(),m=nxi();
	for(int i=1; i<1<<m; ++i) dp[i]=1;
	while(n--){
		static int v[1<<K],tw[1<<K];
		static num0 w[1<<K],iw[1<<K];
		int q=nxi(),sum=0;
		//getwgt
		for(int i=0; i<q; ++i){
			v[1<<i]=nxi(),tw[1<<i]=nxi();
			sum+=tw[1<<i];
		}
		for(int lb,i=0; i<1<<q; ++i){
			if(i==(lb=i&-i)) tw[i]=(lint)tw[i]*inv[sum]%mod;
			else tw[i]=(tw[i^lb]+tw[lb])%mod;
			w[i]=tw[i];
			iw[i]=w[i].qinv();
		}
		//w'[i]=\prod_ {j \sub i} w[j]^ {-1^ {|i|-|j|}}
		for(int i=1; i<1<<q; i<<=1){
			for(int j=0; j<1<<q; j+=i<<1){
				for(int k=0; k<i; ++k){
					w[j+k+i]*=iw[j+k];
					iw[j+k+i]*=w[j+k];
				}
			}
		}
		//applywgt
		for(int lb,i=0; i<1<<q; ++i){
			if(i!=(lb=i&-i)) v[i]=v[i^lb]|v[lb];
			dp[v[i]]*=w[i];
		}
	}
	for(int i=1; i<1<<m; i<<=1){
		for(int j=0; j<1<<m; j+=i<<1){
			for(int k=0; k<i; ++k){
				dp[j+k+i]*=dp[j+k];
			}
		}
	}
	for(int i=0; i<1<<m; ++i){
		res[i]=dp[i].qval();
	}
	for(int i=1; i<1<<m; i<<=1){
		for(int j=0; j<1<<m; j+=i<<1){
			for(int k=0; k<i; ++k){
				res[j+k+i]=(res[j+k+i]-res[j+k]+mod)%mod;
			}
		}
	}
	int ans=0;
	for(int i=0; i<1<<m; ++i){
		ans^=res[i];
	}
	printf("%d\n",ans);
	return 0;
}
