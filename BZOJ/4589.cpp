#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=65536;
const int mod=1e9+7;
int sum,n;
bool npr[N];

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	static int prm[N];
	int cnp=0;
	npr[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

namespace P{
	const int inv2=fpow(2,mod-2);

	inline void fwt(int *a,int len){
		for(int i=1; i<len; i<<=1){
			for(int j=0; j<len; j+=i<<1){
				for(int k=0; k<i; ++k){
					int t1=a[j+k],t2=a[j+k+i];
					a[j+k]=(t1+t2)%mod;
					a[j+k+i]=(t1+mod-t2)%mod;
				}
			}
		}
	}

	inline void ifwt(int *a,int len){
		for(int i=1; i<len; i<<=1){
			for(int j=0; j<len; j+=i<<1){
				for(int k=0; k<i; ++k){
					int t1=a[j+k],t2=a[j+k+i];
					a[j+k]=(lint)(t1+t2)*inv2%mod;
					a[j+k+i]=(lint)(t1+mod-t2)*inv2%mod;
				}
			}
		}
	}

	class _poly{
		public:
			int len,*n;

			_poly(int len=0){
				this->len=len;
				n=new int[len];
			}
			inline void clear(){
				memset(n,0,len*sizeof(int));
			}
			inline void del(){
				delete[] n;
			}
	};

	inline _poly fpow(_poly org,int t){
		int len=1;
		while(len<org.len) len<<=1;
		_poly ans(len);
		fwt(org.n,len);

		ans.clear();
		ans.n[0]=1;
		fwt(ans.n,len);
		for(; t; t>>=1){
			if(t&1){
				for(int i=0; i<len; ++i){
					ans.n[i]=(lint)ans.n[i]*org.n[i]%mod;
				}
			}
			for(int i=0; i<len; ++i){
				org.n[i]=(lint)org.n[i]*org.n[i]%mod;
			}
		}
		ifwt(ans.n,len);
		return ans;
	}
}
using P::_poly;

int main(){
	static _poly base_p(N);
	init();
	while(~scanf("%d%d\n",&sum,&n)){
		memset(base_p.n,0,N*sizeof(int));
		for(int i=1; i<=n; ++i){
			base_p.n[i]=!npr[i];
		}
		base_p.len=n+1;
		_poly res=P::fpow(base_p,sum);
		//_poly res=base_p*base_p;
		printf("%d\n",res.n[0]);
		res.del();
	}
	return 0;
}
