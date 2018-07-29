#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int mod=2333;
int C[mod][mod],sc[mod][mod];

template<class T> inline T nxi(){
	T x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void twk(int &x){
	if(x>=mod) x-=mod;
}

inline void init(){
	C[0][0]=1,sc[0][0]=1;;
	for(int i=0;i<mod;++i) sc[0][i]=1;
	for(int i=1;i<mod;++i){
		sc[i][0]=C[i][0]=1;
		for(int j=1;j<mod;++j){
			twk(C[i][j]=C[i-1][j]+C[i-1][j-1]);
			twk(sc[i][j]=sc[i][j-1]+C[i][j]);
		}
	}
}

int lucas(const lint n,const lint k){
	if(k<0||n<k) return 0;
	if(n<mod) return C[n][k];
	return lucas(n/mod,k/mod)*lucas(n%mod,k%mod)%mod;
}

int sol(const lint n,const lint k){
	const int P=mod;
	if(k<0) return 0;
	if(n<P&&k<P) return sc[n][k];
	return (sol(n/P,k/P-1)*sol(n%P,n%P)+lucas(n/P,k/P)*sc[n%P][k%P])%P;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("1.in","r",stdin);
	freopen("4591.out","w",stdout);
#endif
	init();
	int T=nxi<int>();
	while(T--){
		lint n=nxi<lint>(),k=nxi<lint>();
		printf("%d\n",sol(n,k));
	}
	return 0;
}
