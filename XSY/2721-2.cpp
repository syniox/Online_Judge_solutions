#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
#include <vector>
using namespace std;
typedef long long lint;
const lint N=1e10;
const int S=1e5+5,B=4.65e6;
lint n;
int q,cns,cnp,prm[B];
unsigned fd[B];
bool npr[B],vis_fd[N/B+10];
vector<unsigned> ph[S];

struct sieve_s{//f*g=h
	unsigned v[B],cache[N/B+10];
	bool vis[N/B+10];
	virtual unsigned g(const lint x)=0;
	virtual unsigned h(const lint x)=0;
	unsigned operator()(const lint x);
};
struct mu_s:sieve_s{
	unsigned g(const lint x){return x;}
	unsigned h(const lint x){return 1;}
}mu;
struct phi_s:sieve_s{
	unsigned g(const lint x){return x;}
	unsigned h(const lint x){return (unsigned)x*unsigned(x+1)>>1u;}
}phi;

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

unsigned sieve_s::operator()(const lint x){
	if(x<B) return v[x];
	if(vis[n/x]) return cache[n/x];
	vis[n/x]=1;
	unsigned ans=h(x);
	for(lint i=2,j; i<=x; i=j+1){
		j=x/(x/i);
		ans=(ans-(g(j)-g(i-1))*(*this)(x/i));
	}
	return cache[n/x]=ans;
}
inline void par(unsigned v[],const int n){
	for(int i=1; i<=n; ++i) v[i]+=v[i-1];
}

void load(){
	mu.v[1]=phi.v[1]=1;
	for(int i=2; i<B; ++i){
		if(!npr[i]){
			prm[++cnp]=i;
			mu.v[i]=-1;
			phi.v[i]=i-1;
		}
		for(int j=1,k; j<=cnp&&(k=i*prm[j])<B; ++j){
			npr[k]=1;
			if(i%prm[j]==0){
				phi.v[k]=phi.v[i]*prm[j];
				break;
			}
			mu.v[k]=-mu.v[i];
			phi.v[k]=phi.v[i]*(prm[j]-1);
		}
	}
	for(; (lint)prm[cns+1]*prm[cns+1]<=N; ++cns);
	par(mu.v,B-1);
	par(phi.v,B-1);
}

void build_fd(const int q){
	static int lp[B],lcnt[B];//除去最小质因子之后的数，最小质因子指数
	fd[1]=1;
	for(int i=2; i<B; ++i){
		if(!npr[i]) fd[i]=-1,lp[i]=lcnt[i]=1;
		for(int j=1,k; j<=cnp&&(k=i*prm[j])<B; ++j){
			if(i%prm[j]==0){
				lp[k]=lp[i];
				lcnt[k]=lcnt[i]+1;
				fd[k]=lcnt[k]<=q?-fd[i]:0;
				break;
			}
			lp[k]=i;
			lcnt[k]=1;
			fd[k]=-fd[i];//q>=1
		}
	}
	par(fd,B-1);
}

void build_h(const int q){
	for(int i=1; i<=cns; ++i){
		int cnt=0;
		for(lint scc=1; scc*prm[i]<=n; ++cnt,scc*=prm[i]);
		ph[i].resize(cnt+1);
		ph[i][0]=1;
		for(int j=1; j<=cnt; ++j){
			unsigned res=j<=q?(j&1?-1:1):0;
			for(int k=1; k<=j; ++k){
				res=res-(-(k==1)*ph[i][j-k]);
			}
			ph[i][j]=res;
		}
	}
}

unsigned dfs_fd(const int t,const lint scc,const unsigned vh,const lint n,const int q){
	if(t>cns) return vh*mu(n/scc);
	unsigned ans=0;
	for(lint s=scc,cnt=0; s<=n; ++cnt,s*=prm[t]){
		if(cnt!=1) ans+=dfs_fd(t+1,s,vh*ph[t][cnt],n,q);
	}
	return ans;
}

unsigned get_fd(const int g,const int q){
	static unsigned cache[N/B+10];
	if(g<B) return fd[g];
	if(vis_fd[n/g]) return cache[n/g];
	vis_fd[n/g]=1;
	eprintf("qfd: %d %d\n",g,q);
	return cache[n/g]=dfs_fd(1,1,1,g,q);
}

int main(){
	n=ni,q=ni;
	load();
	unsigned ans=0;
	for(int i=1; i<=q; ++i){
		memset(vis_fd,0,sizeof(vis_fd));
		build_fd(i);
		build_h(i);
		for(lint j=1,k; j<=n; j=k+1){
			k=n/(n/j);
			ans=(ans+(get_fd(k,i)-get_fd(j-1,i))*(phi(n/j)*2-1));
		}
		//eprintf("finished %d.\n",i);
	}
	printf("%u\n",ans&((1<<30)-1));
	return 0;
}
