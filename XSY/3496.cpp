#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
typedef long long lint;
const int N=1e6+5;
const int mod=998244353;
int n,q,qa,qb,qc,qd;
char invld[N];

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

struct mtrx{
	int n[3][3];

	friend mtrx operator * (const mtrx &a,const mtrx &b){
		mtrx c;
		for(int i=0; i<3; ++i){
			for(int j=0; j<3; ++j){
				lint tmp=0;
				tmp+=(lint)a.n[i][0]*b.n[0][j];
				tmp+=(lint)a.n[i][1]*b.n[1][j];
				tmp+=(lint)a.n[i][2]*b.n[2][j];
				c.n[i][j]=tmp%mod;
			}
		}
		return c;
	}
}g0,g1,pmtx[N],ipmt[N];//转移到第i位结束

struct vec{
	int n[3];

	friend vec operator * (const vec &a,const mtrx &b){
		vec c;
		c.n[0]=((lint)a.n[0]*b.n[0][0]+(lint)a.n[1]*b.n[1][0]+(lint)a.n[2]*b.n[2][0])%mod;
		c.n[1]=((lint)a.n[0]*b.n[0][1]+(lint)a.n[1]*b.n[1][1]+(lint)a.n[2]*b.n[2][1])%mod;
		c.n[2]=((lint)a.n[0]*b.n[0][2]+(lint)a.n[1]*b.n[1][2]+(lint)a.n[2]*b.n[2][2])%mod;
		return c;
	}
};

mtrx mtrx_inv(mtrx x){
	mtrx inv;
	memset(inv.n,0,sizeof(inv.n));
	inv.n[0][0]=inv.n[1][1]=inv.n[2][2]=1;
	for(int i=0; i<3; ++i){
		int j=i;
		while(j<3&&!x.n[j][i]) ++j;
		if(i!=j){
			for(int k=0; k<3; ++k){
				std::swap(x.n[i][k],x.n[j][k]);
				std::swap(inv.n[i][k],inv.n[j][k]);
			}
		}
		for(int j=0; j<3; ++j){
			if(j==i||!x.n[j][i]) continue;
			int wgt=(lint)(mod-x.n[j][i])*fpow(x.n[i][i],mod-2)%mod;
			for(int k=0; k<3; ++k){
				x.n[j][k]=(x.n[j][k]+(lint)x.n[i][k]*wgt)%mod;
				inv.n[j][k]=(inv.n[j][k]+(lint)inv.n[i][k]*wgt)%mod;
			}
		}
	}
	for(int i=0; i<3; ++i){
		if(x.n[i][i]==1) continue;
		int wgt=fpow(x.n[i][i],mod-2);
		for(int k=0; k<3; ++k){
			inv.n[i][k]=(lint)inv.n[i][k]*wgt%mod;
		}
	}
	return inv;
}

void build_mtrx(){
	mtrx inv0,inv1;
	g0.n[0][0]=1,g0.n[0][1]=2,g0.n[0][2]=1;
	g0.n[1][0]=0,g0.n[1][1]=1,g0.n[1][2]=1;
	g0.n[2][0]=1,g0.n[2][1]=2,g0.n[2][2]=2;

	g1.n[0][0]=1,g1.n[0][1]=2,g1.n[0][2]=1;
	g1.n[1][0]=0,g1.n[1][1]=1,g1.n[1][2]=1;
	g1.n[2][0]=0,g1.n[2][1]=0,g1.n[2][2]=1;

	inv0=mtrx_inv(g0);
	inv1=mtrx_inv(g1);
	pmtx[0].n[0][0]=1;
	pmtx[0].n[1][1]=1;
	pmtx[0].n[2][2]=1;
	ipmt[0].n[0][0]=1;
	ipmt[0].n[1][1]=1;
	ipmt[0].n[2][2]=1;
	for(int i=1; i<=n; ++i){
		pmtx[i]=pmtx[i-1]*(invld[i-1]=='1'?g1:g0);
		ipmt[i]=(invld[i-1]=='1'?inv1:inv0)*ipmt[i-1];
	}
}

inline int ask(const int l,const int r){
	vec res((vec){1,0,0}*g0*ipmt[l]*pmtx[r]);
	return res.n[2];
}

int main(){
#ifndef ONLINE_JUDGE
	//freopen("d.in","r",stdin);
#endif
	n=nxi(),q=nxi();
	scanf("%s",invld+1);
	qa=nxi(),qb=nxi(),qc=nxi(),qd=nxi();
	build_mtrx();
	int ans=0;
	for(int i=1; i<=q; ++i){
		const int l=std::min(qa,qb),r=std::max(qa,qb);
		qa=((qa^i)+qc)%n+1;
		qb=((qb^i)+qd)%n+1;
		ans^=ask(l,r);
	}
	printf("%d\n",ans);
	return 0;
}
