#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
typedef long long lint;
const int N=1e6+5;
const int M=55;
const int mod=1e9+7;
int n,m,cnt_0,cnt_free,hx[M];

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline int gcd(int x,int y){
	while(x^=y^=x^=y%=x);
	return y;
}

inline int qpow(int x,int t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline int hbit(int x){
	int ans=0;
	for(int i=16; i; i>>=1){
		if(x>>i) x>>=i,ans+=i;
	}
	return ans;
}

//Sieve
namespace S{
	class Dusieve{
		protected:
			int hx[N],mp[N];
			bool vis[(int)1e3+5];
			virtual int _g(int x)=0;
			virtual int _prod(int x)=0;
		public:
			inline void clear(){
				memset(vis,0,sizeof(vis));
			}
			inline int operator () (int x){
				if(x<N) return hx[x];
				const int dv=n/x;
				if(vis[dv]) return mp[dv];
				int ans=_prod(x);
				for(int i=2,j=x/i; j; i=x/j+1,j=x/i){
					ans-=(_g(x/j)-_g(i-1))*(*this)(j);
				}
				vis[dv]=1;
				return mp[dv]=ans;
			}
	};
	class Mu:public Dusieve{
		protected:
			int cnp,prm[N];
			bool npr[N];
			virtual int _g(int x){return x;}
			virtual int _prod(int){return 1;}
		public:
			inline void init(){
				hx[1]=1;
				for(int i=2; i<N; ++i){
					if(!npr[i]){
						hx[i]=-1;
						prm[++cnp]=i;
					}
					for(int j=1; j<=cnp&&i*prm[j]<N; ++j){
						npr[i*prm[j]]=1;
						if(i%prm[j]==0) break;
						hx[i*prm[j]]=-hx[i];
					}
					hx[i]+=hx[i-1];
				}
			}
	}mu;
}

//poly
namespace P{
	class poly{
		protected:
			int n,*hx;
		public:
			poly(int n){
				this->n=n;
				hx=new int[n+1];
			}

			inline int ask(int x){
				int ans=0;
				for(int i=0,tp=1; i<=n; ++i,tp=(lint)tp*x%mod){
					ans=(ans+(lint)hx[i]*tp)%mod;
				}
				return ans;
			}

			friend void lagrange(poly &a,int len,int px[],int py[]);
	}spow(0);

	inline void lagrange(poly &a,int n,int px[],int py[]){
		static int f[M];
		memset(f,0,sizeof(f));
		a=poly(n);
		memset(a.hx,0,(n+1)<<2);
		f[0]=1;
		//mul poly:(1,px[i])
		for(int i=0; i<=n; ++i){
			for(int j=i+1; j; --j){
				f[j]=(f[j-1]+(lint)f[j]*(mod-px[i]))%mod;
			}
			f[0]=(lint)f[0]*px[i]%mod;
		}
		for(int i=0; i<=n; ++i){
			int base=1;
			for(int j=0; j<=n; ++j){
				if(j==i) continue;
				base=(lint)base*(px[i]+mod-px[j])%mod;
			}
			base=((lint)qpow(base,mod-2)*py[i])%mod;
			int rest=1;
			for(int j=n; ~j; --j){
				a.hx[j]=(a.hx[j]+(lint)rest*base)%mod;
				rest=((lint)rest*px[i]+f[j])%mod;
			}
		}
	}

	inline void init(){
		static int px[M],py[M];
		px[0]=py[0]=0;
		for(int i=1; i<=cnt_free+1; ++i){
			px[i]=i;
			py[i]=(py[i-1]+qpow(i,cnt_free))%mod;
		}
		lagrange(spow,cnt_free+1,px,py);
	}
}

inline int solve(){
	static int prm_buk[10+5],prm_ans[1<<10];
	static bool prm_side[1<<10];
	P::init();
	S::mu.init();
	int ans=0;
	if(cnt_free+cnt_0==m){
		for(int l=1,r; l<=n; l=r+1){
			r=n/(n/l);
			ans=(ans+(S::mu(r)+mod-S::mu(l-1))*(lint)P::spow.ask(n/l))%mod;
		}
	}
	else{
		int cur=0,limit=sqrt(n)+1,prm_pt=0;
		for(int i=1; i<=m; ++i){
			if(hx[i]>0) cur=cur?gcd(cur,hx[i]):hx[i];
		}
		for(int i=2; i<=limit; ++i){
			if(cur%i==0){
				prm_buk[++prm_pt]=i;
				while(cur%i==0) cur/=i;
			}
		}
		if(cur>1) prm_buk[++prm_pt]=cur;
		prm_ans[0]=1;
		ans=(lint)S::mu(1)*P::spow.ask(n)%mod;
		for(int i=1; i<1<<prm_pt; ++i){
			int lb=i&-i;
			prm_ans[i]=(lint)prm_buk[hbit(lb)+1]*prm_ans[i^lb]%mod;
			prm_side[i]=prm_side[i^lb]^1;
			ans=(ans+(prm_side[i]?-1:1)*P::spow.ask(n/prm_ans[i]))%mod;
		}
	}
	return ans<0?ans+mod:ans;
}

int main(){
	m=nxi(),n=nxi();
	for(int i=1; i<=m; ++i){
		hx[i]=nxi();
		cnt_free+=hx[i]==-1;
		cnt_0+=hx[i]==0;
	}
	printf("%d\n",solve());
	return 0;
}
