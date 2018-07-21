#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=100002;
const int mod=19961993;
int m,cnp,prm[61],tr[61][N];//phi[prm]
bool npr[300];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

lint qmi(lint x,int t){
	lint p(1);
	for(;t;t>>=1,x=x*x%mod){
		if(t&1) p=p*x%mod;
	}
	return p;
}

inline void init(){
	for(int i=2;i<300;++i){
		if(!npr[i]) prm[++cnp]=i;
		if(cnp==60) break;
		for(int j=1;j<=cnp&&i*prm[j]<300;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

inline void chn(int p,int x,int v){
	for(;x<=100000;x+=x&-x){
		tr[p][x]+=v;
	}
}

inline int ask(int p,int x,int y){
	int ans(0);
	for(;y;y-=y&-y){
		ans+=tr[p][y];
	}
	--x;
	for(;x;x-=x&-x){
		ans-=tr[p][x];
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("5.in","r",stdin);
	freopen("c.out","w",stdout);
#endif
	init();
	m=nxi();
	for(int i=1;i<=100000;++i){
		chn(2,i,1);
	}
	while(m--){
		int op=nxi(),a=nxi(),b=nxi();
		if(op){
			for(int i=1;i<=60;++i){
				int tp(0),q=prm[i];
				while(b%q==0){
					q*=prm[i];
					++tp;
				}
				chn(i,a,tp-ask(i,a,a));
			}
		}
		else{
			lint ans=1;
			if(a>b) swap(a,b);
			for(int i=1;i<=60;++i){
				int q=ask(i,a,b);
				if(q){
					ans=ans*(prm[i]-1)*qmi(prm[i],q-1)%mod;
				}
			}
			printf("%lld\n",ans);
		}
	}
	return 0;
}
