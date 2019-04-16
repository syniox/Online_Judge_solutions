#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=12;
const int S3=531441+5;
const int mod=998244353;
int n,q,eg[N+1][N+1],hbit[1<<N],id[1<<N][1<<N];
int exi1[S3],exi0[S3],dp[12][S3];
//x|y((x&y)==0)点集中存在/不存在x->y的边的概率

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
	for(int i=2; i<1<<n; ++i){
		hbit[i]=hbit[i>>1]+1;
	}
}

void build_exi(){
	static int cnt;
	for(int i=1; i<1<<n; ++i){
		for(int j=(i-1)&i; j; j=(j-1)&i){
			id[i][j]=++cnt;
			int e0=1,e1=1;
			for(int k=2; k<=n; ++k){
				if((j>>(k-1)&1)==0) continue;
				int p=1;
				for(int l=1; l<=n; ++l){
					if((i^j)>>(l-1)&1)
						p=(lint)p*(1-eg[l][k]+mod)%mod;
				}
				e0=(lint)e0*p%mod;
				e1=(lint)e1*(1-p+mod)%mod;
			}
			exi0[cnt]=e0;
			exi1[cnt]=e1;
		}
	}
}

int main(){
	n=nxi(),q=nxi();
	if(n==1){
		puts("1");
		return 0;
	}
	init();
	for(int i=1; i<=n*(n-1); ++i){
		const int a=nxi(),b=nxi(),p=nxi(),q=nxi();
		eg[a][b]=(lint)p*fpow(q,mod-2)%mod;
	}
	build_exi();
	for(int i=2; i<1<<n; ++i){
		if(!(i&1)) continue;
		assert(id[i][i^1]);
		int p=1;
		for(int j=2; j<=n; ++j){
			if(i>>(j-1)&1)
				p=(lint)p*eg[1][j]%mod;
		}
		dp[1][id[i][i^1]]=p;
	}
	for(int i=1; i<q; ++i){
		for(int j=1; j<1<<n; ++j){
			if(!(j&1)) continue;
			for(int k=(j-1)&j; k; k=(k-1)&j){
				if(k&1) continue;
				//assert(id[j][k]);
				int curv=dp[i][id[j][k]];
				if(!curv) continue;
				int all=((1<<n)-1)^j;
				for(int l=all; l; l=(l-1)&all){
					int to=id[j|l][l];
					//assert(to);
					//assert(id[k|l][l]);
					//assert(id[(j^k)|l][l]);
					int wgt=(lint)exi1[id[k|l][l]]*exi0[id[(j^k)|l][l]]%mod;
					dp[i+1][to]=(dp[i+1][to]+(lint)curv*wgt)%mod;
				}
			}
		}
	}
	int ans=0;
	for(int i=1; i<1<<n; ++i){
		if(i&1) continue;
		assert(id[(1<<n)-1][i]);
		for(int j=1; j<=q; ++j){
			ans=(ans+dp[j][id[(1<<n)-1][i]])%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
