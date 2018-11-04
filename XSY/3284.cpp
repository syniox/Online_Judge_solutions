#include <iostream>
#include <cstdio>
#include <cstring>
const int N=42;
const int mod=2333;
int n,m;
template <class T> inline void twk(T &x){
	if(x>=mod) x-=mod;
}
struct mtrx{
	int x[N][N];
	mtrx(){
		memset(x,0,sizeof(x));
		for(int i=1;i<=n;++i) x[i][i]=1;
	}
	mtrx operator * (const mtrx &b) const {
		mtrx c;
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				c.x[i][j]=0;
				for(int k=1;k<=n;++k){
					c.x[i][j]+=x[i][k]*b.x[k][j];
					if(c.x[i][j]>=(int)1e9) c.x[i][j]%=mod;
				}
				c.x[i][j]%=mod;
			}
		}
		return c;
	}
	inline void print(){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j) printf("%d ",x[i][j]);
			puts("");
		}
	}
}dt;

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

template <class T> inline T qpow(T x,int t){
	T ans;
	for(;t;x=x*x,t>>=1){
		if(t&1) ans=ans*x;
	}
	return ans;
}

int main(){
#ifndef ONLINE_JUDGE
//	freopen("a.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		const int a=nxi(),b=nxi();
		++dt.x[a][b];
		++dt.x[b][a];
	}
	for(int i=nxi();i;--i){
		const int s=nxi(),t=nxi(),l=nxi(),r=nxi();
		mtrx mt=qpow(dt,l);
		int ans=0;
		for(int i=l;i<=r;++i,mt=mt*dt){
			twk(ans+=mt.x[s][t]);
		}
		printf("%d\n",ans);
	}
	return 0;
}
