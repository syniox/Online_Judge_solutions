#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1<<18;
const int mod=1e9+7;
const int inv2=mod-(mod>>1);
int n;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

namespace P{
	template <class T> inline void tor(T &a,T &b){
		twk(b+=a);
	}
	template <class T> inline void ior(T &a,T &b){
		twk(b+=mod-a);
	}
	template <class T> inline void tand(T &a,T &b){
		twk(a+=b);
	}
	template <class T> inline void iand(T &a,T &b){
		twk(a+=mod-b);
	}
	template <class T> inline void txor(T &a,T &b){
		T t1=a+b,t2=a+mod-b;
		twk(a=t1);twk(b=t2);
	}
	template <class T> inline void ixor(T &a,T &b){
		T t1=(lint)(a+b)*inv2%mod;
		T t2=(lint)(a+mod-b)*inv2%mod;
		a=t1,b=t2;
	}


	template <class T> inline void fwt(T *a,int len,void(*trans)(T&,T&)){
		for(int i=1; i<len; i<<=1){
			for(int j=0; j<len; j+=i<<1){
				for(int k=0; k<i; ++k){
					trans(a[j+k],a[j+k+i]);
				}
			}
		}
	}

	template <class T> class poly{
		public:
			int len;
			T *n;
			poly(int len=0){
				this->len=len;
				n=new T[len];
			}
	};
}
using P::poly;

template <class T>
void solve(poly <T> a,poly <T> b,poly <T> c,void(*tr)(T&,T&),void(*itr)(T&,T&)){
	static int buka[N],bukb[N];
	memcpy(buka,a.n,(1<<n)*sizeof(T));
	memcpy(bukb,b.n,(1<<n)*sizeof(T));
	P::fwt(buka,1<<n,tr);
	P::fwt(bukb,1<<n,tr);
	for(int i=0; i<1<<n; ++i){
		c.n[i]=(lint)buka[i]*bukb[i]%mod;
	}
	P::fwt(c.n,1<<n,itr);
	for(int i=0; i<1<<n; ++i){
		printf("%d ",c.n[i]);
	}
	puts("");
}

int main(){
	n=nxi();
	poly <int> a(1<<n),b(1<<n),c(1<<n);
	for(int i=0; i<1<<n; ++i) a.n[i]=nxi();
	for(int i=0; i<1<<n; ++i) b.n[i]=nxi();
	solve(a,b,c,P::tor,P::ior);
	solve(a,b,c,P::tand,P::iand);
	solve(a,b,c,P::txor,P::ixor);
	return 0;
}
