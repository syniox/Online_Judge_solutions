#include<iostream>
#include<cstdio>
#include<cstring>
const int mod=1e9+7,N=31650;
typedef long long lint;
int m,p,cnp,cnd,dv[N],prm[3500];
bool ispr[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	for(int i=2;i<N;++i){
		if(!ispr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<N;++j){
			ispr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline int phi(const int t){
	int x=t,ans=t;
	for(int j=1;j<=cnp;++j){
		if(x%prm[j]==0){
			ans=ans/prm[j]*(prm[j]-1);
			while((x/=prm[j])%prm[j]==0);
		}
	}
	if(x!=1) ans=ans/x*(x-1);
	return ans;
}

inline void get_dv(int t){
	dv[++cnd]=1;
	for(int j=1;j<=cnp;++j){
		if(t%prm[j]==0){
			const int cur=cnd;
			do{
				for(int i=cnd-cur+1;i<=cnd;++i){
					dv[i+cur]=dv[i]*prm[j];
				}
				cnd+=cur;
			}while((t/=prm[j])%prm[j]==0);
		}
	}
	if(t!=1){
		const int cur=cnd;
		for(int i=1;i<=cur;++i){
			dv[++cnd]=dv[i]*t;
		}
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("b.in","r",stdin);
#endif
	m=nxi(),p=nxi();
	init();
	get_dv(p-1);
	int ans=0;
	for(int i=1;i<=cnd;++i){
//		printf("%d ",dv[i]);
		const int tp=(p-1)/dv[i];
		ans+=1ll*dv[i]*dv[i]%mod*(((lint)tp*phi(tp)+(tp==1))%mod)%mod;
		if(ans>mod) ans-=mod;
//		printf("%d\n",ans);
	}
//	puts("");
	const int tp=(lint)p*(p-1)%mod;
	printf("%lld\n",((lint)(ans-tp+mod)%mod*m>>1)%mod);
	return 0;
}
