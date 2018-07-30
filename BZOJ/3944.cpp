#include<iostream>
#include<cstdio>
#include<cstring>
#include<cmath>
typedef long long lint;
const int N=1665000;
int n,cnp,prm[N];
bool npr[N];
struct djs{
	//a:front b:last
	lint a[N],b[N];
	bool vis[1850];
	//adjacent
	virtual lint adj(int x)=0;
	virtual lint dirch(int x)=0;

	inline void init(){
		memset(vis+1,0,sizeof(vis)-1);
	}

	inline lint operator () (int x){
		if(x<N) return a[x];
		const int dv=n/x;
		if(vis[dv]) return b[dv];
		vis[dv]=1;
		lint ans=dirch(x);
		lint las=adj(1);
		for(lint i=2,j=x/i,d;j;i=d+1,j=x/i){
			d=x/j;
			lint cur=adj(d);
			ans-=(cur-las)*(*this)(j);
			las=cur;
		}
		return b[dv]=ans;
	}
};
struct mobius:djs{
	virtual lint adj(int x){
		return x;
	}
	virtual lint dirch(int){
		return 1;
	}
}mu;

struct Phi:djs{
	virtual lint adj(int x){
		return x;
	}
	virtual lint dirch(int x){
		return x*((lint)x+1)>>1;
	}
}phi;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	mu.a[1]=phi.a[1]=1;
	for(int i=2;i<N;++i){
		if(!npr[i]){
			mu.a[i]=-1;
			prm[++cnp]=i;
			phi.a[i]=i-1;
		}
		for(int j=1;j<=cnp&&i*prm[j]<N;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0){
				phi.a[i*prm[j]]=phi.a[i]*prm[j];
				break;
			}
			mu.a[i*prm[j]]=-mu.a[i];
			phi.a[i*prm[j]]=phi.a[i]*(prm[j]-1);
		}
		phi.a[i]+=phi.a[i-1];
		mu.a[i]+=mu.a[i-1];
	}
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("3944.in","r",stdin);
#endif
	init();
	int T=nxi();
	while(T--){
		mu.init();
		phi.init();
		n=nxi();
		if(!n){
			puts("0 0");
			continue;
		}
		printf("%lld %lld\n",phi(n),mu(n));
	}
	return 0;
}
