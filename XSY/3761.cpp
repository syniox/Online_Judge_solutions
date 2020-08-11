#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
using namespace std;
typedef long long lint;
const int N=5e5+5,V=10;
const int mod=1e9+7;
static lint mmod=(1ull<<63)-(lint)mod*mod;
int n,q;
char str[N];

namespace utils{
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	inline char getc(){
		static char buf[20000],*h,*t;
		if(h==t){
			t=(h=buf)+fread(buf,1,20000,stdin);
			if(h==t) return EOF;
		}
		return *h++;
	}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getc())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getc());
			while(x=x*10-48+c,(c=getc())>='0'&&c<='9');
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

struct mtx{
	int v[V+1][V+1];
	inline void init(){
		memset(v,0,sizeof(v));
	}
	friend mtx operator*(const mtx &a,const mtx &b){
		static lint vbuk[V+1][V+1];
		memset(vbuk,0,sizeof(vbuk));
		mtx c;
		for(int i=0; i<=V; ++i){
			for(int j=0; j<=V; ++j){
				if(!a.v[i][j]) continue;
				for(int k=0; k<=V; ++k){
					vbuk[i][k]=vbuk[i][k]+(lint)a.v[i][j]*b.v[j][k];
					if(vbuk[i][k]>=mmod) vbuk[i][k]%=mod;
				}
			}
		}
		for(int i=0; i<=V; ++i){
			for(int j=0; j<=V; ++j){
				c.v[i][j]=vbuk[i][j]%mod;
			}
		}
		return c;
	}
}mt[V],imt[V],msum[N],isum[N];
struct vec_s{
	int v[V+1];
	inline void init(){
		memset(v,0,sizeof(v));
	}
	vec_s operator*(const mtx &b){
		vec_s c;
		c.init();
		for(int i=0; i<=V; ++i){
			if(!v[i]) continue;
			for(int j=0; j<=V; ++j){
				c.v[j]=(c.v[j]+(lint)v[i]*b.v[i][j])%mod;
			}
		}
		return c;
	}
};

mtx getinv(const mtx orig){
	mtx r,m=orig;
	r.init();
	for(int i=0; i<=V; ++i){
		r.v[i][i]=1;
	}
	for(int i=0; i<=V; ++i){
		int j=i;
		for(; j<=V&&!m.v[i][j]; ++j);
		assert(j<=V);
		if(i!=j){
			for(int k=0; k<=V; ++k){
				swap(m.v[i][k],m.v[j][k]);
				swap(r.v[i][k],r.v[j][k]);
			}
		}
		for(int k=0; k<=V; ++k){
			if(k==i) continue;
			int wgt=lint(mod-m.v[k][i])*fpow(m.v[i][i],mod-2)%mod;
			if(!wgt) continue;
			for(int l=0; l<=V; ++l){
				m.v[k][l]=(m.v[k][l]+(lint)m.v[i][l]*wgt)%mod;
				r.v[k][l]=(r.v[k][l]+(lint)r.v[i][l]*wgt)%mod;
			}
		}
	}
	return r;
}

bool is_e(const mtx mt){
	for(int i=0; i<=V; ++i){
		for(int j=0; j<=V; ++j){
			if((i==j)!=mt.v[i][j]) return 0;
		}
	}
	return 1;
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1),q=ni;
	for(int i=0; i<V; ++i){
		for(int j=0; j<=V; ++j){
			mt[i].v[j][j]=1;
		}
		for(int j=0; j<=V; ++j){
			mt[i].v[j][i]=1;
		}
		imt[i]=getinv(mt[i]);
		assert(is_e(mt[i]*imt[i]));
	}
	msum[n]=mt[str[n]-'a'];
	isum[n]=imt[str[n]-'a'];
	for(int i=n-1; i; --i){
		msum[i]=msum[i+1]*mt[str[i]-'a'];
		isum[i]=imt[str[i]-'a']*isum[i+1];
	}
	while(q--){
		int l=ni,r=ni;
		vec_s t;
		t.init();
		t.v[V]=1;
		if(r<n) t=t*isum[r+1];
		t=t*msum[l];
		int ans=0;
		for(int i=0; i<V; ++i){
			ans=(ans+t.v[i])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}

