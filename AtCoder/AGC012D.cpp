#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <vector>
typedef long long lint;
const int N=2e5+5;
const int mod=1e9+7;
int n,lim1,lim2,npos1,npos2,col[N],wgt[N],lpos[N];
int fac[N],ifac[N];
std::vector <int> list[N];

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
	fac[0]=1;
	for(int i=1; i<=n; ++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	ifac[n]=fpow(fac[n],mod-2);
	for(int i=n; i; --i){
		ifac[i-1]=(lint)ifac[i]*i%mod;
	}
}

namespace U{
	int fa[N];
	int find_rt(const int x){
		return fa[x]?fa[x]=find_rt(fa[x]):x;
	}
	inline void link(int x,int y){
		x=find_rt(x),y=find_rt(y);
		if(x!=y) fa[x]=y;
	}
}

int solve(const int x){
	static int buk[N];
	int res=fac[list[x].size()];
	for(std::vector <int> ::iterator it=list[x].begin(); it!=list[x].end(); ++it){
		++buk[col[*it]];
	}
	for(std::vector <int> ::iterator it=list[x].begin(); it!=list[x].end(); ++it){
		if(!buk[col[*it]]) continue;
		res=(lint)res*ifac[buk[col[*it]]]%mod;
		buk[col[*it]]=0;
	}
	return res;
}

int main(){
	n=nxi(),lim1=nxi(),lim2=nxi();
	init();
	wgt[0]=mod;
	for(int i=1; i<=n; ++i){
		col[i]=nxi(),wgt[i]=nxi();
		if(!lpos[col[i]]||wgt[lpos[col[i]]]>wgt[i]){
			lpos[col[i]]=i;
		}
	}
	for(int i=1; i<=n; ++i){
		if(i!=lpos[col[i]]&&wgt[i]+wgt[lpos[col[i]]]<=lim1){
			U::link(i,lpos[col[i]]);
		}
	}
	for(int i=1; i<=n; ++i){
		if(!lpos[i]) continue;
		int tmp=lpos[i];
		if(wgt[npos1]>wgt[tmp]) std::swap(npos1,tmp);
		if(wgt[npos2]>wgt[tmp]) std::swap(npos2,tmp);
	}
	assert(npos1);
	for(int i=1; i<=n; ++i){
		if(npos1&&col[i]!=col[npos1]&&wgt[i]+wgt[npos1]<=lim2){
			U::link(i,npos1);
		}
		if(npos2&&col[i]!=col[npos2]&&wgt[i]+wgt[npos2]<=lim2){
			U::link(i,npos2);
		}
	}
	for(int i=1; i<=n; ++i){
		list[U::find_rt(i)].push_back(i);
	}
	int ans=1;
	for(int i=1; i<=n; ++i){
		if(U::find_rt(i)==i){
			ans=(lint)ans*solve(i)%mod;
		}
	}
	printf("%d\n",ans);
	return 0;
}
