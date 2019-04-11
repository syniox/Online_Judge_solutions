#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=65536;
const int S=60;
const int mod=998244353;
const int inv2=(mod+1)>>1;
int n,m,q,xval,buk[N],phi[N];

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
}

int get_gcd(const int x,const int y){
	return y?get_gcd(y,x%y):x;
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
	static int cnp,prm[N/5];
	static bool npr[N];
	phi[1]=npr[1]=1;
	for(int i=2; i<N; ++i){
		if(!npr[i]){
			phi[i]=i-1;
			prm[++cnp]=i;
		}
		for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0){
				phi[i*prm[j]]=phi[i]*prm[j];
				break;
			}
			phi[i*prm[j]]=phi[i]*phi[prm[j]];
		}
	}
}

inline void fwt(int *a,const int len){
	for(int i=1; i<len; i<<=1){
		for(int j=0; j<len; j+=i<<1){
			for(int k=0; k<i; ++k){
				int x=a[j+k],y=a[j+k+i];
				a[j+k]=(x+y)%mod;
				a[j+k+i]=(x-y+mod)%mod;
			}
		}
	}
}

inline void ifwt(int *a,const int len){
	for(int i=1; i<len; i<<=1){
		for(int j=0; j<len; j+=i<<1){
			for(int k=0; k<i; ++k){
				int x=a[j+k],y=a[j+k+i];
				a[j+k]=(lint)(x+y)*inv2%mod;
				a[j+k+i]=(lint)(x-y+mod)*inv2%mod;
			}
		}
	}
}

inline int fwt_ans(const int d,const int m){
	static int buk[N];
	memset(buk,0,sizeof(buk));
	for(int i=d; i<=xval; i+=d){
		buk[i]=::buk[i];
	}
	int len=1;
	while(len<=xval) len<<=1;
	fwt(buk,len);
	for(int i=0; i<len; ++i){
		buk[i]=fpow(buk[i],m);
	}
	ifwt(buk,len);
	return buk[q];
}

inline int solve1(){
	return buk[q];
}

inline int solve2(){
	int ans=0;
	for(int i=1; i<=xval; ++i){
		int j=i^q;
		if(j>i) ans=(ans+(lint)buk[i]*buk[j]*get_gcd(i,j))%mod;
	}
	return ans;
}

inline int solve3(){
	int ans=0;
	for(int i=1; i<=std::min(S,xval); ++i){
		ans=(ans+(lint)fwt_ans(i,3)*phi[i])%mod;
	}
	for(int i=S+1; i<=xval; ++i){
		int res=0;
		for(int j=i; j<=xval; j+=i){
			if(!buk[j]) continue;
			for(int k=i; k<=xval; k+=i){
				if(!buk[k]) continue;
				int l=j^k^q;
				if(l%i||!buk[l]) continue;
				res=(res+(lint)buk[j]*buk[k]*buk[l]%mod)%mod;//1e6^3
			}
		}
		ans=(ans+(lint)res*phi[i])%mod;
	}
	for(int i=1; i<=xval; ++i){
		if(buk[i]&&i!=q){
			int res=(lint)buk[i]*buk[q]%mod;
			ans=(ans-(lint)get_gcd(i,q)*res*3)%mod;
		}
	}
	ans=(ans-(lint)q*buk[q])%mod;
	ans=(ans-(lint)q*buk[q]%mod*(buk[q]-1)*3)%mod;
	ans=(lint)ans*fpow(6,mod-2)%mod;
	return ans<0?ans+mod:ans;
}

inline int solve4(){
	static int buk2[N],cbuk[N];
	static bool vis[N];
	int ans=0;
	for(int i=1; i<=std::min(S,xval); ++i){
		ans=(ans+(lint)fwt_ans(i,4)*phi[i])%mod;
	}
	for(int i=S+1; i<=xval; ++i){
		int res=0;
		for(int j=i; j<=xval; j+=i){
			for(int k=i; k<=xval; k+=i){
				buk2[j^k]=(buk2[j^k]+(lint)buk[j]*buk[k])%mod;
			}
		}
		for(int j=i; j<=xval; j+=i){
			for(int k=i; k<=xval; k+=i){
				int x=j^k;
				if(vis[x]) continue;
				vis[x]=1;
				res=(res+(lint)buk2[x]*buk2[q^x])%mod;
			}
		}
		for(int j=i; j<=xval; j+=i){
			for(int k=i; k<=xval; k+=i){
				buk2[j^k]=vis[j^k]=0;
			}
		}
		ans=(ans+(lint)res*phi[i])%mod;
	}
	//2
	for(int i=1; i<=xval; ++i){
		for(int j=i; j<=xval; j+=i){
			cbuk[i]+=buk[j];
		}
	}
	for(int i=1; i<=xval; ++i){
		int res=0;
		for(int j=i; j<=xval; j+=i){
			int k=q^j;
			if(buk[j]&&buk[k]&&k%i==0){
				res=(res+buk[j]*buk[k]%mod*(cbuk[i]-2))%mod;
			}
		}
		ans=(ans-(lint)res*phi[i]*6)%mod;
	}
	//3
	ans=(ans-(lint)solve2()*4*2)%mod;
	ans=((lint)ans*fpow(24,mod-2))%mod;
	return ans<0?ans+mod:ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("d.in","r",stdin);
#endif
	init();
	n=nxi(),m=nxi(),q=nxi();
	for(int i=1; i<=n; ++i){
		const int x=nxi();
		++buk[x];
		apx(xval,x);
	}
	switch(m){
		case 1:
			printf("%d\n",solve1());
			break;
		case 2:
			printf("%d\n",solve2());
			break;
		case 3:
			printf("%d\n",solve3());
			break;
		case 4:
			printf("%d\n",solve4());
			break;
	}
	return 0;
}
