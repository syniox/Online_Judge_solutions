#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <cmath>
typedef long long lint;
using namespace std;
const lint N=1e10;
const int S=4641595;
const double eps=1e-9;
lint n,pw[(int)1e5+5][42];
int q,cnp,prm[S],rnp[S],lcnt[S];
unsigned f[S],mu[S];
bool npr[S];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	inline lint nxi(){
		lint x=0;
		char c;
		while(((c=getchar())>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=getchar());
		while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
		return f?-x:x;
	}
}
using namespace utils;

struct sieve_s{
	protected://f*g=h
		virtual unsigned g(const lint x)=0;
		virtual unsigned h(const lint x)=0;
	public:
		unsigned sum[S],cache[N/S+5];
		bool vis[N/S+5];
		void load(){
			for(int i=2; i<S; ++i){
				sum[i]+=sum[i-1];
			}
		}
		unsigned operator[](const int x){
			assert(x&&x<S);
			return sum[x]-sum[x-1];
		}
		unsigned operator()(const lint x){
			if(x<S) return sum[x];
			if(vis[n/x]) return cache[n/x];
			vis[n/x]=1;
			unsigned ans=h(x);
			for(lint j,i=2; i<=x; i=j+1){
				j=x/(x/i);
				ans-=(g(j)-g(i-1))*(*this)(x/i);
			}
			return cache[n/x]=ans;
		}
};

struct phi_s:sieve_s{
	unsigned g(const lint x){
		return x;
	}
	unsigned h(const lint x){
		return (unsigned)x*((unsigned)x+1ull)>>1u;
	}
}phi;
struct lambda_s:sieve_s{
	unsigned g(const lint x){
		return x;
	}
	unsigned h(const lint x){
		return (unsigned)sqrt(x);
	}
}lambda;

void preload(){
	lambda.sum[1]=1;
	mu[1]=phi.sum[1]=1;
	for(int i=2; i<S; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			mu[i]=-1u;
			rnp[i]=lcnt[i]=1;
			lambda.sum[i]=-1u;
			phi.sum[i]=i-1;
		}
		for(int j=1; j<=cnp&&i*prm[j]<S; ++j){
			int k=i*prm[j];
			npr[k]=1;
			lambda.sum[k]=-lambda.sum[i];
			if(i%prm[j]==0){
				rnp[k]=rnp[i];
				lcnt[k]=lcnt[i]+1;
				phi.sum[k]=phi.sum[i]*prm[j];
				break;
			}
			rnp[k]=i;
			lcnt[k]=1;
			mu[k]=-mu[i];
			phi.sum[k]=phi.sum[i]*(prm[j]-1);
		}
	}
	phi.load();
	lambda.load();
	for(int i=1,end=sqrt(n)+5; i<=end; ++i){
		pw[i][0]=1;
		for(int j=1; j<42; ++j){
			pw[i][j]=pw[i][j-1]*i;
			if(pw[i][j]>n) break;
		}
	}
}

void init_f(const int d){
	f[1]=1;
	///*
	for(int i=2; i<S; ++i){
		f[i]=lcnt[i]>d?0:lcnt[i]&1?-f[rnp[i]]:f[rnp[i]];
	}
	//*/
	for(int i=2; i<S; ++i){
		f[i]+=f[i-1];
	}
}

unsigned getf(const int d,const lint x){
	if(x<S) return f[x];
	int lim=int(pow(x,1.0/(d+1))+eps);
	unsigned ans=0;
	for(int t=1; t<=lim; ++t){
		if(!mu[t]) continue;
		unsigned lt=lambda[t]==-1u&&(d+1)&1?-1u:1u;
		ans+=(unsigned)mu[t]*(unsigned)lt*lambda(x/pw[t][d+1]);
	}
	return ans;
}

int main(){
	n=nxi(),q=nxi();
	preload();
	unsigned ans=0;
	for(int d=1; d<=q; ++d){
		init_f(d);
		unsigned lst=0,cur=0;
		for(lint i=1,j; i<=n; i=j+1){
			j=n/(n/i);
			cur=getf(d,j);
			ans+=(cur-lst)*(2u*phi(n/i)-1u);
			lst=cur;
		}
	}
	printf("%u\n",ans&((1<<30)-1));
	return 0;
}
