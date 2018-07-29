#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
const int N=32;
const int mod=2017;
int n,m;
struct mtx{
	int x[N][N];
	mtx operator * (const mtx b) const{
		mtx c;
		for(int i=0;i<=n;++i){
			for(int j=0;j<=n;++j){
				c.x[i][j]=0;
				for(int k=0;k<=n;++k){
					c.x[i][j]+=x[i][k]*b.x[k][j];
				}
				c.x[i][j]%=mod;
			}
		}
		return c;
	}
}p;

inline mtx qpow(mtx &x,int t){
	mtx ans;
	for(int i=0;i<=n;++i){
		for(int j=0;j<=n;++j){
			ans.x[i][j]=(i==j);
		}
	}
	for(;t;t>>=1,x=x*x){
		if(t&1) ans=ans*x;
	}
	return ans;
}

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("4887.in","r",stdin);
#endif
	n=nxi(),m=nxi();
	for(int i=1;i<=m;++i){
		int a=nxi(),b=nxi();
		p.x[a][b]=p.x[b][a]=1;
	}
	++p.x[0][0];
	for(int i=1;i<=n;++i){
		++p.x[i][0];
		++p.x[i][i];
	}
	p=qpow(p,nxi());
	int ans=0;
	for(int i=0;i<=n;++i){
		ans+=p.x[1][i];
	}
	printf("%d\n",ans%mod);
	return 0;
}
