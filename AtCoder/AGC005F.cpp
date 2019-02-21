#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
typedef long long lint;
const int N=262144;
const int mod=924844033;
//5
int n,cal[N],fac[N],inv[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int fpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod; 
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i) fac[i]=(lint)fac[i-1]*i%mod;
	inv[N-1]=fpow(fac[N-1],mod-2);
	for(int i=N-1; i; --i) inv[i-1]=(lint)inv[i]*i%mod;
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

namespace G{
	int cnt,fir[N],sz[N];
	struct edge{
		int to,nx;
	}eg[N<<1];

	inline void add(const int a,const int b){
		eg[++cnt]=(edge){b,fir[a]};
		fir[a]=cnt;
	}

	inline void dfs_cal(const int x){
		sz[x]=1;
		for(int i=fir[x]; i; i=eg[i].nx){
			const int y=eg[i].to;
			if(!sz[y]){
				dfs_cal(y);
				++cal[sz[y]];
				sz[x]+=sz[y];
			}
		}
		++cal[n-sz[x]];
	}
}

namespace P{

	void ntt(int *a,int len,bool f){
		static int rev[N<<1];
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(a[i],a[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=fpow(5,(mod-1)/(i<<1));
			for(int j=0; j<len; j+=i<<1){
				for(int w=1,k=0; k<i; ++k,w=(lint)w*t%mod){
					lint p=(lint)w*a[j+k+i];
					a[j+k+i]=(a[j+k]-p)%mod;
					a[j+k]=(a[j+k]+p)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			if(a[i]<0) a[i]+=mod;
		}
		if(f==0) return;
		std::reverse(a+1,a+len);
		int tmp=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			a[i]=(lint)a[i]*tmp%mod;
		}
	}

	class poly{
		public:
			int len,*n;
			poly(int len=0){
				this->len=len;
				n=new int[len+1];
			}
			friend poly operator * (poly a,poly b);
	}ans;

	poly operator * (poly a,poly b){
		static int buka[N<<1],bukb[N<<1];
		poly c(a.len+b.len);
		int len=1;
		while(len<=c.len) len<<=1;
		memset(buka,0,len*sizeof(int));
		memset(bukb,0,len*sizeof(int));
		memcpy(buka,a.n,(a.len+1)*sizeof(int));
		memcpy(bukb,b.n,(b.len+1)*sizeof(int));
		ntt(buka,len,0);
		ntt(bukb,len,0);
		for(int i=0; i<len; ++i){
			buka[i]=(lint)buka[i]*bukb[i]%mod;
		}
		ntt(buka,len,1);
		memcpy(c.n,buka,(c.len+1)*sizeof(int));
		return c;
	}

	inline void get_poly(){
		poly a(n),b(n);
		for(int i=1; i<n; ++i){
			a.n[i]=(lint)cal[i]*fac[i]%mod;
			b.n[i]=inv[n-i-1];
		}
		ans=a*b;
	}
}

int main(){
	init();
	n=nxi();
	for(int i=1; i<n; ++i){
		const int a=nxi(),b=nxi();
		G::add(a,b);
		G::add(b,a);
	}
	G::dfs_cal(1);
	P::get_poly();
	for(int i=1; i<=n; ++i){
		const int all=(lint)n*C(n,i)%mod;
		const int invld=(lint)inv[i]*P::ans.n[n-1+i]%mod;
		printf("%d\n",(all+mod-invld)%mod);
	}
	return 0;
}
