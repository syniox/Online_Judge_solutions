#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
typedef long long lint;
const int N=1005,mod=1e9+7;
int n,m,qa,qb,fac[N<<2],inv[N<<2];
struct pnt{
	int x,y;
}pt[N],limit[2];

template <class T> inline void apx(T &x,const T y){
	if(x<y) x=y;
}

template <class T> inline void apn(T &x,const T y){
	if(x>y) x=y;
}

template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while(((c=getchar())>'9'||c<'0')&&c!='-');
	const bool f=c=='-'&&(c=getchar());
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return f?-x:x;
}

inline int qpow(int x,int t){
	int ans=1;
	for(;t;x=(lint)x*x%mod,t>>=1){
		if(t&1) ans=(lint)ans*x%mod;
	}
	return ans;
}

inline void init(){
	limit[0]=(pnt){1000,1000};
	limit[1]=(pnt){-1000,-1000};
	fac[0]=1;
	for(int i=1;i<N<<2;++i){
		fac[i]=(lint)fac[i-1]*i%mod;
	}
	inv[(N<<2)-1]=qpow(fac[(N<<2)-1],mod-2);
	for(int i=(N<<2)-1;i;--i){
		inv[i-1]=(lint)inv[i]*i%mod;
	}
}

inline int C(const int x,const int y){
	if(x<y) return 0;
	return (lint)fac[x]*inv[y]%mod*inv[x-y]%mod;
}

namespace S{
	int cnq;
	pnt que_pt[N];

	inline int get_dp(const int l){
		if(m<l||((l&1)^(m&1))) return 0;
		return C(m,(m-l)>>1);
	}

	inline int calc(){
		int ansx=0,ansy=0;
		for(int i=limit[0].x;i<=limit[1].x;++i){
			int cnt=1;
			for(int j=1;cnt&&j<=cnq;++j){
				cnt=(lint)cnt*get_dp(abs(que_pt[j].x-i))%mod;
			}
			twk(ansx+=cnt);
		}
		for(int i=limit[0].y;i<=limit[1].y;++i){
			int cnt=1;
			for(int j=1;cnt&&j<=cnq;++j){
				cnt=(lint)cnt*get_dp(abs(que_pt[j].y-i))%mod;
			}
			twk(ansy+=cnt);
		}
		return (lint)ansx*ansy%mod;
	}

	inline int solve(){
		const int qc=n-qa-qb,sz_p=sizeof(pnt);
		int ans=1,res_a,res_b,res_c;

		memcpy(que_pt+1,pt+1,qa*sz_p);
		cnq=qa;
		ans=res_a=calc();

		memcpy(que_pt+1,pt+qa+1,qb*sz_p);
		cnq=qb;
		ans=(lint)ans*(res_b=calc())%mod;

		memcpy(que_pt+1,pt+qa+qb+1,qc*sz_p);
		cnq=n-qa-qb;
		ans=(lint)ans*(res_c=calc())%mod;

		memcpy(que_pt+1,pt+1,(qa+qb)*sz_p);
		cnq=qa+qb;
		twk(ans+=mod-(lint)res_c*calc()%mod);

		memcpy(que_pt+1,pt+qa+1,(qb+qc)*sz_p);
		cnq=qb+qc;
		twk(ans+=mod-(lint)res_a*calc()%mod);

		memcpy(que_pt+1,pt+1,qa*sz_p);
		memcpy(que_pt+qa+1,pt+qa+qb+1,qc*sz_p);
		cnq=qa+qc;
		twk(ans+=mod-(lint)res_b*calc()%mod);

		memcpy(que_pt+1,pt+1,n*sz_p);
		cnq=n;
		ans=(ans+(lint)2*calc())%mod;

		return ans;
	}
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("d.in","r",stdin);
#endif
	init();
	n=nxi(),qa=nxi(),qb=nxi(),m=nxi();
	for(int i=1;i<=n;++i){
		const int x=nxi(),y=nxi();
		pt[i].x=x+y;
		pt[i].y=x-y;
		apn(limit[0].x,pt[i].x-m);
		apx(limit[1].x,pt[i].x+m);
		apn(limit[0].y,pt[i].y-m);
		apx(limit[1].y,pt[i].y+m);
	}
	printf("%d\n",S::solve());
	return 0;
}
