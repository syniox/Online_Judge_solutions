#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
const int N=1e5+2;
const int mod=1e9+7;
int n,qa,qb,fac2[N];
int s1,s2,s3,s4;
bool swaped;

template <class T> inline void twk(T &x){
	if(x<0) x+=mod;
	else if(x>=mod) x-=mod;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	fac2[0]=1;
	for(int i=1;i<=n;++i){
		twk(fac2[i]=fac2[i-1]<<1);
	}
}

inline void calc(){
	int ansa=0,ansb=0,ans0=0,ans1=0;
	ansa=(ansa+(lint)(fac2[s2]-1)*fac2[s3+s4])%mod;
	ansa=(ansa+(lint)(fac2[s4]-s4-1)*fac2[s3])%mod;
	int codd=0,ceven=1;
	if(s3) codd=ceven=fac2[s3-1];
	ansa=(ansa+(lint)s4*codd)%mod;
	ans0=(ans0+(lint)s4*ceven)%mod;
	twk(ans0+=codd);
	twk(ans1+=ceven);
	ansa=(lint)ansa*fac2[s1]%mod;
	ansb=(lint)ansb*fac2[s1]%mod;
	ans0=(lint)ans0*fac2[s1]%mod;
	ans1=(lint)ans1*fac2[s1]%mod;
	if(swaped) std::swap(ansa,ansb);
	printf("%d %d %d %d\n",ansa,ansb,ans0,ans1);
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("a.in","r",stdin);
#endif
	n=nxi(),qa=nxi(),qb=nxi();
	init();
	if(qa>qb){
		swaped=1,std::swap(qa,qb);
	}
	for(int i=1;i<=n;++i){
		const int x=nxi()%(qa+qb);
		if(x<qa) ++s1;
		else if(x<qb) ++s2;
		else if(x<qa<<1) ++s3;
		else ++s4;
	}
	calc();
	return 0;
}
