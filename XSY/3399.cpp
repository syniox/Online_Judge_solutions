#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=31;
const int K=10005;//check again?
const int L=32768;
const int mod=998244353;
int pre_ans[21][K];
int T,pow3[L],fac[K],ifac[K];

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int qpow(int x,int t){
	int ans=1;
	for(; t; x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace IO{
	const int SIZE=1<<16;
	char ibuf[SIZE],*ih,*it,obuf[SIZE],*oh=obuf,*ot=oh+SIZE;
	inline void flush(){
		fwrite(obuf,1,oh-obuf,stdout);
		oh=obuf;
	}
	struct _Flusher{
		~_Flusher(){flush();}
	}_flusher;
	inline char get_c(){
		if(ih==it){
			it=(ih=ibuf)+fread(ibuf,1,SIZE,stdin);
			if(ih==it) return EOF;
		}
		return *ih++;
	}
	inline int nxi(){
		int x=0;
		char c;
		while((c=get_c())>'9'||c<'0');
		while(x=x*10-48+c,(c=get_c())>='0'&&c<='9');
		return x;
	}
	inline void put_c(const char c){
		*oh++=c;
		if(oh==ot) flush();
	}
	template <class T> inline void pti(T x){
		static char tmp[20];
		char *pt=tmp;
		if(!x) put_c('0');
		for(T y=x/10; x; x=y,y=x/10){
			*pt++=x-y*10+'0';
		}
		while(pt!=tmp) put_c(*--pt);
	}
}
using IO::get_c;
using IO::put_c;
using IO::nxi;
using IO::pti;

inline void ntt(int a[],int len,bool f){
	static int rev[L];
	for(int i=1; i<len; ++i){
		rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
		if(i<rev[i]) std::swap(a[i],a[rev[i]]);
	}
	for(int i=1; i<len; i<<=1){
		int t=L/(i<<1);
		for(int j=0; j<len; j+=i<<1){
			for(int w=0,k=0; k<i; ++k,w+=t){
				lint p=(lint)a[j+k+i]*pow3[w];
				a[j+k+i]=(a[j+k]-p)%mod;
				a[j+k]=(a[j+k]+p)%mod;
			}
		}
	}
	if(!f) return;
	std::reverse(a+1,a+len);
	int tmp=qpow(len,mod-2);
	for(int i=0; i<len; ++i){
		a[i]=(lint)a[i]*tmp%mod;
	}
}

class poly{
	public:
		int *x,n;

		poly(){}
		poly(const int l){
			n=l;
			x=new int[n+1];
		}
		void del(){
			delete x;
		}
}range_ans[21][21];

namespace B{
	const int S=105;
	const long long _Limit=(1ull<<63)-(lint)mod*mod;
	int n;

	class mtrx{
		public:
			int v[N][N];

			inline int diag_sum(){
				int ans=0;
				for(int i=1; i<=n; ++i){
					twk(ans+=v[i][i]);
				}
				return ans;
			}
			friend mtrx operator * (const mtrx &a,const mtrx &b){
				mtrx c;
				memset(c.v,0,sizeof(c.v));
				for(int i=1; i<=n; ++i){
					for(int j=1; j<=n; ++j){
						lint tmp=0;
						for(int k=1; k<=n; ++k){
							tmp+=(lint)a.v[i][k]*b.v[k][j];
							if(tmp>_Limit) tmp%=mod;
						}
						c.v[i][j]=tmp%mod;
					}
				}
				return c;
			}
			friend int diag_sum(const mtrx &a,const mtrx &b){
				//diagonal
				lint ans=0;
				for(int i=1; i<=n; ++i){
					for(int j=1; j<=n; ++j){
						ans+=(lint)a.v[i][j]*b.v[j][i];
						if(ans>_Limit) ans%=mod;
					}
				}
				return ans%mod;
			}
	};

	inline void build_pre_ans(int t){
		static mtrx blk,pre_pnt[S+1];
		memset(blk.v,0,sizeof(blk.v));
		memset(pre_pnt,0,sizeof(pre_pnt));
		n=nxi();
		int m=nxi();
		for(int i=1; i<=n; ++i){
			pre_pnt[1].v[i][i]=1;
		}
		for(int i=1; i<=m; ++i){
			const int x=nxi(),y=nxi();
			pre_pnt[1].v[x][y]=pre_pnt[1].v[y][x]=1;
		}
		pre_ans[t][0]=n;
		pre_ans[t][1]=pre_pnt[1].diag_sum();

		for(int i=2; i<=S; ++i){
			pre_pnt[i]=pre_pnt[i-1]*pre_pnt[1];
			pre_ans[t][i]=pre_pnt[i].diag_sum();
		}
		blk=pre_pnt[S];
		for(int i=S+1,j=1; i<K; ++i,++j){
			pre_ans[t][i]=diag_sum(blk,pre_pnt[j]);
			if(j==S){
				j=0;
				blk=blk*pre_pnt[S];
			}
		}
	}
}

inline void init(){
	fac[0]=1;
	for(int i=1; i<K; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[K-1]=qpow(fac[K-1],mod-2);
	for(int i=K-1; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
	pow3[0]=1;
	int tmp=qpow(3,(mod-1)/L);
	for(int i=1; i<L; ++i){
		pow3[i]=(lint)pow3[i-1]*tmp%mod;
	}
}

inline int C(int x,int y){
	if(x<y) return 0;
	return (lint)fac[x]*ifac[y]%mod*ifac[x-y]%mod;
}

namespace P{
	poly _base(L-1);

	inline void init(){
		for(int i=0; i<K; ++i){
			_base.x[i]=i&1?mod-ifac[i]:ifac[i];
		}
		ntt(_base.x,L,0);
	}

	inline void build_range_ans(const int l,const int r){
		static int buk[L];
		memset(buk,0,sizeof(buk));
		for(int i=0,cur_ans; i<K; ++i){
			cur_ans=1;
			for(int j=l; j<=r; ++j){
				cur_ans=(lint)cur_ans*pre_ans[j][i]%mod;
			}
			buk[i]=(lint)ifac[i]*cur_ans%mod;
		}
		ntt(buk,L,0);
		for(int i=0; i<L; ++i){
			buk[i]=(lint)buk[i]*_base.x[i]%mod;
		}
		ntt(buk,L,1);
		range_ans[l][r]=poly(K-1);
		memcpy(range_ans[l][r].x,buk,K*sizeof(int));

		/*
		printf("l%d r%d: range:",l,r);
		for(int i=0; i<5; ++i){
			printf("%d ",range_ans[l][r].x[i]);
		}
		puts("");
		*/

		for(int i=2; i<K; ++i){
			int &tp=range_ans[l][r].x[i];
			if(tp<0) tp+=mod;
			tp=((lint)tp*fac[i]+range_ans[l][r].x[i-1])%mod;
		}
	}
}

int main(){
	init();
	P::init();
	T=nxi();
	for(int i=1; i<=T; ++i){
		B::build_pre_ans(i);
	}
	for(int i=1; i<=T; ++i){
		for(int j=i; j<=T; ++j){
			P::build_range_ans(i,j);
		}
	}
	for(int q=nxi(); q; --q){
		const int l=nxi(),r=nxi(),k=nxi();
		pti(range_ans[l][r].x[k]);
		put_c('\n');
	}
	return 0;
}
