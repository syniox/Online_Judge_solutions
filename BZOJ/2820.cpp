#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const int N=1e7+2;
int T,n,m,cnp,mu[N],prm[665000];
lint pf[N];
bool npr[N];
inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	for(;c>='0'&&c<='9';c=getchar()) x=x*10+c-48;
	return x;
}
void init(){
	mu[1]=1;
	for(int i=2;i<N;++i){
		if(!npr[i]){
			prm[++cnp]=i;
			mu[i]=-1;
		}
		for(int j=1;(lint)i*prm[j]<N&&j<=cnp;++j){
			int tp=i*prm[j];
			npr[tp]=1;
			if(i%prm[j]==0) break;
			mu[tp]=-mu[i];
		}
	}
	for(int i=1;i<=cnp;++i){
		for(int j=prm[i];j<N;j+=prm[i]){
			pf[j]+=mu[j/prm[i]];
		}
	}
	for(int i=1;i<N;++i){
		pf[i]+=pf[i-1];
	}
}
int main(){
	T=nxi();
	init();
	while(T--){
		n=nxi(),m=nxi();
		int p=min(n,m);
		lint ans=0;
		for(int q,i=1;i<=p;i=q+1){
			q=min(n/(n/i),m/(m/i));
			ans+=(pf[q]-pf[i-1])*(n/i)*(m/i);
		}
		printf("%lld\n",ans);
	}
	return 0;
}
