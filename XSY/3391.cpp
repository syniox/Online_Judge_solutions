#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=131072;
const int mod=998244353;
int n,fac[N];

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<N; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
}

namespace P{
	int wt[N];

	inline void init(){
		wt[0]=1;
		const int w=fpow(3,(mod-1)/N);
		for(int i=1; i<N; ++i){
			wt[i]=(lint)wt[i-1]*w%mod;
		}
	}

	inline void ntt(int *a,const int len,bool f){
		static int rev[N];
		assert(len<=N);
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(a[i],a[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=N/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int k=0,w=0; k<i; ++k,w+=t){
					lint p=(lint)a[j+k+i]*wt[w];
					a[j+k+i]=(a[j+k]-p)%mod;
					a[j+k]=(a[j+k]+p)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			if(a[i]<0) a[i]+=mod;
		}
		if(!f) return;
		std::reverse(a+1,a+len);
		int tmp=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			a[i]=(lint)a[i]*tmp%mod;
		}
	}
}

class poly{
	public:
		int len,*n;

		inline void init(const int len=0){
			this->len=len;
			n=new int[len];
		}

		inline void copy(const poly &x){
			if(n!=NULL) delete[] n;
			len=x.len;
			n=new int[len];
			memcpy(n,x.n,len*sizeof(int));
		}

		inline void move(poly &x){//use &&x in c++11
			if(n!=NULL) delete[] n;
			len=x.len,n=x.n,x.n=NULL;
		}

		poly(const int len=0){init(len);}
		poly(const poly &x){copy(x);}
		~poly(){if(n!=NULL) delete[] n;}

		inline void clear(){
			memset(n,0,len*sizeof(int));
		}

		inline void operator = (const poly &x){
			this->copy(x);
		}

		inline void stat(){
			for(int i=0; i<len; ++i){
				printf("%d ",n[i]);
			}
			puts("");
		}

		friend poly operator * (const poly &a,const poly &b){
			static int buka[N],bukb[N];
			poly c(a.len+b.len-1);
			int len=1;
			while(len<c.len) len<<=1;
			memset(buka,0,len*sizeof(int));
			memset(bukb,0,len*sizeof(int));
			memcpy(buka,a.n,a.len*sizeof(int));
			memcpy(bukb,b.n,b.len*sizeof(int));
			P::ntt(buka,len,0);
			P::ntt(bukb,len,0);
			for(int i=0; i<len; ++i){
				buka[i]=(lint)buka[i]*bukb[i]%mod;
			}
			P::ntt(buka,len,1);
			memcpy(c.n,buka,c.len*sizeof(int));
			return c;
		}

		friend poly operator + (const poly &a,const poly &b){
			poly c(std::max(a.len,b.len));
			c.clear();
			for(int i=0; i<a.len; ++i) c.n[i]+=a.n[i];
			for(int i=0; i<b.len; ++i) twk(c.n[i]+=b.n[i]);
			return c;
		}
}pl[N],exc[N];

void solve(const int l,const int r){
	if(l==r) return;
	const int mid=(l+r)>>1;
	solve(l,mid);
	solve(mid+1,r);
	exc[l]=pl[l]*exc[mid+1]+pl[mid+1]*exc[l];
	pl[l]=pl[l]*pl[mid+1];
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	P::init();
	init();
	n=nxi();
	for(int i=1; i<=n; ++i){
		const int p=nxi(),a=nxi(),b=nxi();
		pl[i].init(2);
		pl[i].n[0]=1;
		pl[i].n[1]=(p+(lint)(1-p+mod)*b)%mod;
		exc[i].init(1);
		exc[i].n[0]=(lint)p*a%mod;
	}
	solve(1,n);
	int ans=0;
	if(pl[1].len!=n+1){
		fprintf(stderr,"[warning]len:%d\n",pl[1].len);
		pl[1].stat();
	}
	//assert(pl[1].len==n+1);
	//exc[1].stat();
	for(int i=0; i<n; ++i){
		ans=(ans+(lint)fac[i]*fac[n-i-1]%mod*exc[1].n[i])%mod;
	}
	printf("%lld\n",(lint)ans*fpow(fac[n],mod-2)%mod);
	return 0;
}
