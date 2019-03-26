#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cassert>
#include <map>
typedef long long lint;
const int S=1e6+5;
int prm[S>>3],cnp;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	static bool npr[S];
	for(int i=2; i<S; ++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1; j<=cnp&&i*prm[j]<S; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline int fpow(int x,int t,const int mod){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int get_phi(int x){
	int ans=x,sqr=sqrt(x);
	for(int i=1; prm[i]<=sqr; ++i){
		if(x%prm[i]==0){
			ans=ans/prm[i]*(prm[i]-1);
			while(x%prm[i]==0) x/=prm[i];
		}
	}
	if(x>1) ans=ans/x*(x-1);
	return ans;
}

inline int gcd(const int x,const int y){
	return y?gcd(y,x%y):x;
}

namespace BSGS{
	std::map <int,int> mp;
	int sqr,phi,mod;

	inline void build_mp(const int y){
		int p=1;
		for(int i=0; i<=sqr; ++i){
			if(mp.find(p)==mp.end()) mp[p]=i;
			p=(lint)p*y%mod;
		}
	}

	int main(int y,int z,int mod){
		y%=mod,z%=mod;
		if(z==1) return 0;
		for(int w=y,i=1; i<60; ++i,w=(lint)w*y%mod){
			if(w==z) return i;
		}
		mp.clear();
		int pans=0,prod=1;
		for(int d=gcd(y,mod); d>1; z/=d,mod/=d,d=gcd(y,mod)){
			if(z%d) return -1;
			++pans;
			prod=(lint)prod*(y/d)%mod;
		}
		sqr=sqrt(mod)+1;
		BSGS::mod=mod;
		phi=get_phi(mod);
		build_mp(y);
		if(y==0&&z) return -1;
		assert(gcd(prod,mod)==1);
		z=(lint)z*fpow(prod,phi-1,mod)%mod;
		int step=fpow(y,sqr,mod);
		for(int w=1,i=0; i<sqr; ++i){
			std::map <int,int> ::iterator it=mp.find((lint)z*fpow(w,phi-1,mod)%mod);
			if(it!=mp.end()) return pans+i*sqr+it->second;
			w=(lint)w*step%mod;
		}
		return -1;
	}
}

namespace BIO{
	const int N=1e5+2;
	int mod,phi,pre_prod,fac[N],ifac[N];
	int p,pk;

	inline int get_num(int x,int p){
		int ans=0;
		for(int tmp,w=p; w<=x; w*=p){
			ans+=tmp=x/w;
			if(tmp<p) break;
		}
		return ans;
	}

	inline int C(const int x,const int y){
		if(x<y) return 0;
		return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
	}

	int lucas(const int x,const int y){
		if(x<mod&&y<mod) return C(x,y);
		return (lint)lucas(x/mod,y/mod)*C(x%mod,y%mod)%mod;
	}

	inline void init(){
		fac[0]=1;
		for(int i=1; i<mod; ++i){
			fac[i]=(lint)fac[i-1]*i%mod;
		}
		ifac[mod-1]=fpow(fac[mod-1],mod-2,mod);
		for(int i=mod-1; i; --i){
			ifac[i-1]=(lint)ifac[i]*i%mod;
		}
	}

	/*
	int ex_lucas(const int k){
		int f=k/pk;
		int ans=1;
		for(int i=f*k+1; i<=k; ++i){
			if(i%p==0) continue;
			ans=(lint)ans*i%pk;
		}
		if(f) ans=(lint)ans*ex_lucas(f)%pk;
		return (lint)ans*fpow(pre_prod,f,pk)%pk;
	}

	inline int solve(const int y,const int z,const int p,const int prod){
		if(y<z) return 0;
		BIO::p=p,BIO::pk=prod;
		pre_prod=1;
		for(int i=1; i<prod; ++i){
			if(i%p==0) continue;
			pre_prod=(lint)pre_prod*i%mod;
		}
		int nump=get_num(y,p);
		nump-=get_num(z,p)+get_num(y-z,p);
		int denom=fpow((lint)ex_lucas(z)*ex_lucas(y-z)%prod,phi-1,prod);
		int powp=fpow(p,nump,prod);
		return (lint)ex_lucas(y)*denom%prod*powp%prod;
	}

	int main(const int y,const int z,const int mod){
		static int buk[N],prod[N],cbuk;
		BIO::mod=mod;
		cbuk=0;
		phi=get_phi(mod);
		for(int i=1; prm[i]<=1e5; ++i){
			if(mod%prm[i]==0){
				buk[++cbuk]=prm[i];
				prod[cbuk]=1;
				for(int tmp=mod; tmp%prm[i]==0; tmp/=prm[i]){
					prod[cbuk]*=prm[i];
				}
			}
		}
		int ans=0;
		for(int i=1; i<=cbuk; ++i){
			int res=solve(z,y,buk[i],prod[i]);
			int wgt=(mod/prod[i])*(phi-1)%mod;
			ans=(ans+(lint)res*wgt)%mod;
		}
		return ans;
	}
	*/

	int main(int y,int z,const int mod){
		if(y>1e6||z>1e6){
			BIO::mod=mod;
			init();
			return lucas(z,y);
		}
		std::swap(y,z);
		if(y<z) return 0;
		int ans=1;
		for(int i=1; i<=cnp&&prm[i]<=y; ++i){
			int num=get_num(y,prm[i])-get_num(z,prm[i])-get_num(y-z,prm[i]);
			ans=(lint)ans*fpow(prm[i],num,mod)%mod;
		}
		return ans;
	}
}

int main(){
	init();
	for(int T=nxi(); T; --T){
		int op=nxi(),y=nxi(),z=nxi(),p=nxi();
		int tmp;
		switch(op){
			case 1:
				printf("%d\n",fpow(y,z,p));
				break;
			case 2:
				tmp=BSGS::main(y,z,p);
				if(tmp>=0) printf("%d\n",tmp);
				else puts("Math Error");
				break;
			case 3:
				printf("%d\n",BIO::main(y,z,p));
				break;
		}
	}
	return 0;
}
