#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=131072;
const int mod=998244353;
int n,m,xval,val[N];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

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

inline int hbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) ans+=i,x>>=i;
	}
	return ans;
}

namespace P{
	int wt[N<<1],buka[N<<1],bukb[N<<1];
	class poly{
		public:
			int len,*n;

			poly(int len=0){
				this->len=len;
				n=new int[len+1];
			}
			inline void del(){
				delete[] n;
			}
			friend poly operator * (const poly a,const poly b);
	};

	inline void init(){
		int t=fpow(3,(mod-1)/(N<<1));
		wt[0]=1;
		for(int i=1; i<N<<1; ++i){
			wt[i]=(lint)wt[i-1]*t%mod;
		}
	}

	inline void ntt(int *a,int len,bool f){
		static int rev[N<<1];
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(a[i],a[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=(N<<1)/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int w=0,k=0; k<i; ++k,w+=t){
					lint p=(lint)wt[w]*a[j+k+i];
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

	poly get_mul(int *a,int len_a,int *b,int len_b){
		poly c(len_a+len_b-1);
		int len=1;
		while(len<=c.len) len<<=1;
		memset(buka,0,len<<2);
		memset(bukb,0,len<<2);
		memcpy(buka,a,len_a<<2);
		memcpy(bukb,b,len_b<<2);
		ntt(buka,len,0);
		ntt(bukb,len,0);
		for(int i=0; i<len; ++i){
			buka[i]=(lint)buka[i]*bukb[i]%mod;
		}
		ntt(buka,len,1);
		memcpy(c.n,buka,(c.len+1)<<2);
		return c;
	}

	poly operator * (const poly a,const poly b){
		return get_mul(a.n,a.len+1,b.n,b.len+1);
	}
}
using P::poly;
poly gen,ans,sum;

void solve(const int l,const int r){
	if(l==r){
		sum.n[l]=((lint)sum.n[l]+(ans.n[l]<<(l>0)))%mod;
		return;
	}
	int mid=(l+r)>>1;
	solve(l,mid);
	const int _lim=std::min(xval+1,r-l+1);
	poly tmp;
	tmp=P::get_mul(sum.n+l,mid-l+1,gen.n,_lim);
	for(int i=mid+1; i<=r; ++i){
		twk(ans.n[i]+=tmp.n[i-l]);
	}
	tmp.del();
	tmp=P::get_mul(ans.n+l,mid-l+1,ans.n,std::min(mid+1,_lim));
	for(int i=mid+1; i<=r; ++i){
		sum.n[i]=((lint)sum.n[i]+(tmp.n[i-l]<<(l>0)))%mod;
	}
	tmp.del();
	solve(mid+1,r);
}

int main(){
	P::init();
	n=nxi(),m=nxi();
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
		apx(xval,val[i]);
	}
	gen=poly(xval);
	ans=poly(N<<1);
	sum=poly(N<<1);
	gen.n[0]=1;
	for(int i=1; i<=n; ++i){
		++gen.n[val[i]];
	}
	ans.n[0]=1;
	sum.n[0]=0;
	solve(0,m);
	for(int i=1; i<=m; ++i){
		printf("%d\n",ans.n[i]);
	}
	return 0;
}
