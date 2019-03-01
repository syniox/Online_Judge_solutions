#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
typedef long long lint;
const int N=131072;
const int mod=998244353;
int n,m;

class mtrx{
	public:
		int n[2][2];

		friend mtrx operator * (const mtrx &a,const mtrx &b){
			mtrx c;
			c.n[0][0]=((lint)a.n[0][0]*b.n[0][0]+(lint)a.n[0][1]*b.n[1][0])%mod;
			c.n[0][1]=((lint)a.n[0][0]*b.n[0][1]+(lint)a.n[0][1]*b.n[1][1])%mod;
			c.n[1][0]=((lint)a.n[1][0]*b.n[0][0]+(lint)a.n[1][1]*b.n[1][0])%mod;
			c.n[1][1]=((lint)a.n[1][0]*b.n[0][1]+(lint)a.n[1][1]*b.n[1][1])%mod;
			return c;
		}
};

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline int fpow(int x,T t){
	int ans=1;
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

template <class T> inline mtrx fpow(mtrx x,T t){
	mtrx ans;
	ans.n[0][0]=ans.n[1][1]=1;
	ans.n[0][1]=ans.n[1][0]=0;
	for(; t; t>>=1,x=x*x){
		if(t&1) ans=ans*x;
	}
	return ans;
}

namespace P{
	int wt[N<<4];
	inline void init(){
		int t=fpow(3,(mod-1)/(N<<4));
		wt[0]=1;
		for(int i=1; i<N<<4; ++i){
			wt[i]=(lint)wt[i-1]*t%mod;
		}
	}

	void ntt(int *a,int len,bool f){
		static int rev[N<<4];
		for(int i=1; i<len; ++i){
			rev[i]=rev[i>>1]>>1|(i&1?len>>1:0);
			if(i<rev[i]) std::swap(a[i],a[rev[i]]);
		}
		for(int i=1; i<len; i<<=1){
			int t=(N<<4)/(i<<1);
			for(int j=0; j<len; j+=i<<1){
				for(int w=0,k=0; k<i; ++k,w+=t){
					lint p=(lint)a[j+k+i]*wt[w];
					a[j+k+i]=(a[j+k]-p)%mod;
					a[j+k]=(a[j+k]+p)%mod;
				}
			}
		}
		for(int i=0; i<len; ++i){
			a[i]<0?a[i]+=mod:0;
		}
		if(!f) return;
		std::reverse(a+1,a+len);
		int t=fpow(len,mod-2);
		for(int i=0; i<len; ++i){
			a[i]=(lint)a[i]*t%mod;
		}
	}

	class poly{
		public:
			int len,*n;

			poly(int len=0){
				this->len=len;
				n=new int[len];
			}
			inline void sanitize(const int new_len){
				int *cur=new int[new_len];
				memcpy(cur,n,new_len*sizeof(int));
				delete[] n;
				n=cur;
			}
			inline void del(){
				len=0;
				delete[] n;
			}
			inline void clear(){
				memset(n,0,len*sizeof(int));
			}

			friend poly operator + (const poly a,const poly b);
			friend poly operator - (const poly a,const poly b);
			friend poly operator * (const poly a,const poly b);
	};

	poly operator - (const poly a,const poly b){
		poly c(std::max(a.len,b.len));
		for(int i=0; i<c.len; ++i){
			c.n[i]=0;
			if(a.len>i) c.n[i]=a.n[i];
			if(b.len>i) c.n[i]=(c.n[i]+mod-b.n[i])%mod;
		}
		return c;
	}

	poly operator * (const poly a,const int b){
		poly c(a.len);
		for(int i=0; i<c.len; ++i){
			c.n[i]=(lint)a.n[i]*b%mod;
		}
		return c;
	}

	poly operator * (const poly a,const poly b){
		static int buka[N<<4],bukb[N<<4];
		poly c(a.len+b.len-1);
		int len=1;
		while(len<c.len) len<<=1;
		memset(buka,0,len*sizeof(int));
		memset(bukb,0,len*sizeof(int));
		memcpy(buka,a.n,a.len*sizeof(int));
		memcpy(bukb,b.n,b.len*sizeof(int));
		ntt(buka,len,0);
		ntt(bukb,len,0);
		for(int i=0; i<len; ++i){
			buka[i]=(lint)buka[i]*bukb[i]%mod;
		}
		ntt(buka,len,1);
		memcpy(c.n,buka,c.len*sizeof(int));
		return c;
	}

	inline void get_inv(poly a){
		static poly lst(N<<4),cur;
		static poly tmp_a(N<<4);
		int len=a.len;
		while(len!=(len&-len)) len+=(len^-len);
		tmp_a.clear();
		memcpy(tmp_a.n,a.n,len*sizeof(int));
		lst.n[0]=1;
		for(int i=1; i<len; i<<=1){
			cur.del();
			lst.len=i;
			tmp_a.len=i<<1;
			cur=lst*2-lst*lst*tmp_a;//waste..
			memcpy(lst.n,cur.n,(i<<1)*sizeof(int));
		}
		memcpy(a.n,cur.n,len*sizeof(int));
	}
}

int main(){
	P::init();
	n=nxi(),m=nxi();
	if(n<m){
		puts("0");
		return 0;
	}
	int len=1;
	while(len<=n) len<<=1;
	P::poly ans_a(len),ans_b(len);
	for(int step=(N<<4)/len,i=0; i<len; ++i){
		int w=P::wt[i*step];
		mtrx res=(mtrx){0,1,mod-w,1};
		res=fpow(res,m);
		ans_a.n[i]=(res.n[0][0]+res.n[0][1])%mod;
		ans_b.n[i]=(res.n[1][0]+res.n[1][1])%mod;
	}

	P::ntt(ans_a.n,len,1);
	P::ntt(ans_b.n,len,1);
	P::get_inv(ans_b);
	ans_a=ans_a*ans_b;
	printf("%d\n",ans_a.n[n]);
	return 0;
}
