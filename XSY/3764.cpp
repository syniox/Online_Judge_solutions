#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=262144;
const int mod=998244353;
const int inv2=(mod+1)>>1;
int n,fac[N],ifac[N];
char str[N];

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

namespace P{
	int wt[N<<1];
	struct _init{
		_init(){
			wt[0]=1;
			int t=fpow(3,(mod-1)/(N<<1));
			for(int i=1; i<N<<1; ++i){
				wt[i]=(lint)wt[i-1]*t%mod;
			}
		}
	}_init_;

	void ntt(int *a,const int len,const bool f){
		static int rev[N<<1];
		assert(len==(len&-len));
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) swap(a[i],a[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=N/i;
			for(int j=0; j<len; j+=i<<1){
				for(int k=0,w=0; k<i; ++k,w+=t){
					lint x=a[j+k],y=(lint)a[j+k+i]*wt[w];
					a[j+k]=(x+y)%mod;
					a[j+k+i]=(x-y)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			a[i]=(a[i]+mod)%mod;
		}
		if(!f) return;
		reverse(a+1,a+len);
		for(int i=0,t=fpow(len,mod-2); i<len; ++i){
			a[i]=(lint)a[i]*t%mod;
		}
	}
}

void getfac(){
	fac[0]=1;
	for(int i=1; i<=n; ++i)
		fac[i]=(lint)fac[i-1]*i%mod;
	ifac[n]=fpow(fac[n],mod-2);
	for(int i=n; i>=1; --i)
		ifac[i-1]=(lint)ifac[i]*i%mod;
}

int solve(const char c){
	static int p1[N<<1],p2[N<<1];
	int len;
	for(len=(n+1)<<1; len!=(len&-len); len+=len&-len);
	memset(p1,0,len*sizeof(int));
	memset(p2,0,len*sizeof(int));
	for(int s=1,i=1; i<=n; ++i,s=s*2%mod){
		if(str[i]==c) p1[i]=(lint)s*ifac[n-i]%mod;
	}
	for(int s=inv2,i=1; i<n; ++i,s=(lint)s*inv2%mod){
		if(str[i]==c) p2[len-i]=(lint)s*ifac[i-1]%mod;
	}
	P::ntt(p1,len,0);
	P::ntt(p2,len,0);
	for(int i=0; i<len; ++i){
		p1[i]=(lint)p1[i]*p2[i]%mod;
	}
	P::ntt(p1,len,1);
	int ans=0;
	for(int i=1; i<n; ++i){
		ans=(ans+(lint)fac[n-i-1]*p1[i])%mod;
	}
	return ans;
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	getfac();
	printf("%d\n",(solve('0')+solve('1'))%mod);
	return 0;
}
