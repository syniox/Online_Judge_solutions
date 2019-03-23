#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=21;
const int mod=998244353;
int n,m,q,val[N+1],wsum[1<<N],step[N+1][1<<N],dp[1<<N];
int cbit[1<<N],lg2[1<<N];
bool valid[1<<N];

class edge{
	public:
		int x,y;
}eg[N*N];

inline void init(){
	for(int i=1; i<n; ++i){
		lg2[1<<i]=i;
	}
	for(int i=1; i<1<<n; ++i){
		cbit[i]=cbit[i>>1]+(i&1);
	}
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
	for(; t; t>>=1,x=(lint)x*x%mod){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

namespace U{
	int fa[N+1],dgr[N+1];

	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}

	inline bool jdg(const int st){
		memset(dgr,0,(n+1)*sizeof(int));
		memset(fa,0,(n+1)*sizeof(int));
		for(int i=1; i<=m; ++i){
			int x=eg[i].x,y=eg[i].y;
			if(st>>(x-1)&1&&st>>(y-1)&1){
				++dgr[x],++dgr[y];
				x=find_rt(x),y=find_rt(y);
				if(x!=y) fa[x]=y;
			}
		}
		for(int rt=0,i=1; i<=n; ++i){
			if(st>>(i-1)&1){
				int x=find_rt(i);
				if(!rt) rt=x;
				else if(x!=rt) return 1;
			}
		}
		for(int i=1; i<=n; ++i){
			if(st>>(i-1)&1&&dgr[i]&1) return 1;
		}
		return 0;
	}
}

inline void FWT(int *a,const int len,const bool type){
	for(int i=1; i<len; i<<=1){
		for(int j=0; j<len; j+=i<<1){
			for(int k=0; k<i; ++k){
				a[j+k+i]=(a[j+k+i]+(type?mod-a[j+k]:a[j+k]))%mod;
			}
		}
	}
}

inline void solve(){
	static int res[N+1][1<<N],tmp[1<<N];
	dp[0]=1;
	for(int i=1; i<=n; ++i){
		for(int j=0; j<1<<n; ++j){
			if(cbit[j]==i-1) res[i-1][j]=dp[j];
		}
		FWT(res[i-1],1<<n,0);
		memset(tmp,0,(1<<n)*sizeof(int));
		for(int j=1; j<=i; ++j){
			for(int k=0; k<1<<n; ++k){
				tmp[k]=(tmp[k]+(lint)res[i-j][k]*step[j][k])%mod;
			}
		}
		FWT(tmp,1<<n,1);
		for(int j=1; j<1<<n; ++j){
			if(cbit[j]==i){
				int wgt=fpow(fpow(wsum[j],mod-2),q);
				dp[j]=(lint)tmp[j]*wgt%mod;
			}
		}
	}
}

int main(){
	n=nxi(),m=nxi(),q=nxi();
	init();
	for(int i=1; i<=m; ++i){
		eg[i].x=nxi(),eg[i].y=nxi();
	}
	for(int i=1; i<=n; ++i){
		val[i]=nxi();
	}
	for(int i=1; i<1<<n; ++i){
		const int lbit=i&-i;
		wsum[i]=wsum[i^lbit]+val[lg2[lbit]+1];
	}
	for(int i=1; i<1<<n; ++i){
		valid[i]=U::jdg(i);
		if(valid[i]){
			step[cbit[i]][i]=fpow(wsum[i],q);
		}
	}
	for(int i=1; i<=n; ++i){
		FWT(step[i],1<<n,0);
	}
	solve();
	printf("%d\n",dp[(1<<n)-1]);
	return 0;
}
