#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
const int N=1e5+5;
const int S=420;
const int mod=1e9+7;
int n,q,m,ulim[N],atk[N];
int c_blk,bpmax[S],bprod[S];
int list_c[S],list_u[S][S],list_x[S][S],prod_u[S][S],prod_x[S][S];
//个数,ulim,max,ulim前缀积,max前缀积(inv)

template <class T> inline void apx(T &x,const T y){
	x<y?x=y:0;
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

void build_blk(const int p){
	const int l=(p-1)*S+1,r=std::min(p*S,n);
	bpmax[p]=list_c[p]=0;
	bprod[p]=1;
	for(int i=l; i<=r; ++i){
		if(bpmax[p]>=ulim[i]) bprod[p]=(lint)bprod[p]*ulim[i]%mod;
		else{
			bprod[p]=(lint)bprod[p]*std::max(1,bpmax[p])%mod;
			list_u[p][++list_c[p]]=ulim[i];
			list_x[p][list_c[p]]=std::max(1,bpmax[p]);
		} 
		apx(bpmax[p],atk[i]);
	}
	std::sort(list_u[p]+1,list_u[p]+list_c[p]+1);
	prod_u[p][0]=1;
	prod_x[p][0]=1;
	for(int i=1; i<=list_c[p]; ++i){
		prod_u[p][i]=(lint)prod_u[p][i-1]*list_u[p][i]%mod;
		prod_x[p][i]=(lint)prod_x[p][i-1]*fpow(list_x[p][i],mod-2)%mod;
	}
}

int calc(){
	int pre_max=m,ans=1;
	for(int i=1; i<=c_blk; ++i){
		ans=(lint)ans*bprod[i]%mod;
		int px=std::upper_bound(list_x[i]+1,list_x[i]+list_c[i]+1,pre_max)-list_x[i];
		int pu=std::upper_bound(list_u[i]+1,list_u[i]+list_c[i]+1,pre_max)-list_u[i];
		assert(px>=pu);
		ans=(lint)ans*prod_u[i][pu-1]%mod;
		ans=(lint)ans*prod_x[i][px-1]%mod;
		ans=(lint)ans*fpow(pre_max,px-pu)%mod;
		apx(pre_max,bpmax[i]);
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi(),m=nxi();
	for(int i=1; i<=n; ++i) ulim[i]=nxi();
	for(int i=1; i<=n; ++i) atk[i]=nxi();
	c_blk=n/S+1;
	for(int i=1; i<=c_blk; ++i){
		build_blk(i);
	}
	printf("%d\n",calc());
	for(int i=1; i<=q; ++i){
		const int op=nxi(),x=nxi();
		if(op==0) ulim[x]=nxi();
		else atk[x]=nxi();
		build_blk((x-1)/S+1);
		printf("%d\n",calc());
	}
	return 0;
}
