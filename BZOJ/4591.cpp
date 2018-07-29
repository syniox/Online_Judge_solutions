#include<iostream>
#include<cstdio>
#include<cstring>
const int mod=2333;
int C[mod][mod],sc[mod][mod];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void twk(int &x){
	if(x>=mod) x-=mod;
}

inline void init(){
	C[0][0]=1;
	for(int i=0;i<mod;++i) sc[0][i]=1;
	for(int i=1;i<mod;++i){
		sc[i][0]=C[i][0]=1;
		for(int j=1;j<mod;++j){
			twk(C[i][j]=C[i-1][j]+C[i-1][j-1]);
			twk(sc[i][j]=sc[i][j-1]+C[i][j]);
		}
	}
}

int sol(int n,int k){
#define P mod
	if(n<P&&k<P) return sc[n][k];
	return (sol(n/P,k/P-1)*sc[n%P][P-1]+sc[n/P][k/P-1]*sc[n%P][k%P])%P;
}

int main(){
#ifndef ONLINE_JUDGE
	freopen("4591.in","r",stdin);
#endif
	init();
	int T=nxi();
	while(T--){
		int n=nxi(),k=nxi();
		printf("%d\n",sol(n,k));
	}
	return 0;
}
