#include <iostream>
#include <cstdio>
#include <cstring>
typedef long long lint;
lint qa,qb,qc;

inline int solve(){
	static int buk[60];
	static lint fac[60];
	if(qa>qb) return qb==qc;
	if(qb>qc) return 0;
	lint tot=fac[0]=1;
	for(;fac[tot-1]<=qc/qb;++tot){
		fac[tot]=fac[tot-1]*qb;
	}
	--tot;
	buk[tot]=qc/fac[tot];
	for(int i=tot-1;i>=0;--i){
		buk[i]=qc%fac[i+1]/fac[i];
	}
	lint tp=1,sum=0;
	for(int i=0;i<=tot;++i,tp*=qa){
		sum+=tp*buk[i];
	}
	return sum==qb;
}

int main(){
	while(~scanf("%lld%lld%lld",&qa,&qb,&qc)){
		if(qa==1){
			if(qb==1) puts(qc==1?"infinity":"0");
			else{
				if(qc%qb) printf("%d\n",solve());
				else{
					lint sqc=qc/qb,tp=qb;
					while(tp<sqc) tp*=qb;
					if(tp==sqc||tp==qc) puts("1");
					else printf("%d\n",solve());
				}
			}
		}
		else{
			if(qa==qb) puts(qb==qc?"2":"0");
			else if(qb==qc) puts("1");
			else printf("%d\n",solve());
		}
	}
	return 0;
}
