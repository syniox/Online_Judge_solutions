#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=17;
const int mod=1e9+7;
const lint mod2=(lint)mod*mod;
int n;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline int cbit(int x){
	x=(x&0x55555555)+((x&0xaaaaaaaa)>>1);
	x=(x&0x33333333)+((x&0xcccccccc)>>2);
	x=(x&0x0f0f0f0f)+((x&0xf0f0f0f0)>>4);
	x=(x&0x00ff00ff)+((x&0xff00ff00)>>8);
	x=(x&0x0000ffff)+((x&0xffff0000)>>16);
	return x;
}

template <class T> inline void twk(T &x){
	x<mod?0:x-=mod;
}

class _poly{
	public:
		int len,*n;

		inline void init(const int len){
			if(n) delete[] n;
			this->len=len;
			n=new int[len];
		}
		inline void set(const _poly &a){
			if(n) delete[] n;
			len=a.len;
			n=new int[a.len];
			memcpy(n,a.n,len*sizeof(int));
		}
		_poly(int len=0){
			n=NULL,init(len);
		}
		_poly(const _poly &tmp){
			n=NULL,set(tmp);
		}
		~_poly(){
			if(n!=NULL) delete[] n;
		}
		_poly* operator = (const _poly &a){
			set(a);
			return this;
		}
		friend _poly operator + (const _poly &a,const _poly &b){
			_poly c(std::max(a.len,b.len));
			memset(c.n,0,c.len*sizeof(int));
			memcpy(c.n,a.n,a.len*sizeof(int));
			for(int i=0; i<b.len; ++i) twk(c.n[i]+=b.n[i]);
			return c;
		}
		friend _poly operator - (const _poly &a,const _poly &b){
			_poly c(std::max(a.len,b.len));
			memset(c.n,0,c.len*sizeof(int));
			memcpy(c.n,a.n,a.len*sizeof(int));
			for(int i=0; i<b.len; ++i) twk(c.n[i]+=mod-b.n[i]);
			return c;
		}
		friend _poly operator * (const _poly &a,const _poly &b){
			_poly c(a.len+b.len-1);
			memset(c.n,0,c.len*sizeof(int));
			for(int i=0; i<a.len; ++i){
				for(int j=0; j<b.len; ++j){
					c.n[i+j]=(c.n[i+j]+(lint)a.n[i]*b.n[j])%mod;
				}
			}
			return c;
		}
}pa[1<<N],pb[1<<N];

template <class T> inline void FWT(T *a,const int len,bool type){
	for(int i=1; i<len; i<<=1){
		for(int j=0; j<len; j+=i<<1){
			for(int k=0; k<i; ++k){
				a[j+k+i]=type?a[j+k+i]-a[j+k]:a[j+k+i]+a[j+k];
			}
		}
	}
}

int main(){
	n=nxi();
	for(int i=0; i<1<<n; ++i){
		int c=cbit(i);
		pa[i].init(c+1);
		memset(pa[i].n,0,pa[i].len*sizeof(int));
		pa[i].n[c]=nxi();
	}
	for(int i=0; i<1<<n; ++i){
		int c=cbit(i);
		pb[i].init(c+1);
		memset(pb[i].n,0,pb[i].len*sizeof(int));
		pb[i].n[c]=nxi();
	}
	FWT(pa,1<<n,0);
	FWT(pb,1<<n,0);
	for(int i=0; i<1<<n; ++i){
		pa[i]=pa[i]*pb[i];
	}
	FWT(pa,1<<n,1);
	for(int i=0; i<1<<n; ++i){
		printf("%d ",pa[i].n[cbit(i)]);
	}
	puts("");
	return 0;
}
