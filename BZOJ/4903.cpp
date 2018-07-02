//sro yww
#include<iostream>
#include<cstdio>
using namespace std;
typedef long long lint;
const int N=233334;
const int mod=1e9+7;
int f[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void md(int &x){
	if(x>=mod) x-=mod;
}

//lucas->∏(n[i],m[i])==1 ->n[i]&m[i]==m[i] ->n&m==m
int main(){
	int x,ans(0),n=nxi();
	for(int i=1;i<=n;++i){
		x=nxi();
		int s=0;
		for(int k=(x+1)|x;k<N;k=(k+1)|x) s=s+f[k];
		md(f[x]+=s%mod+1);
		md(ans+=f[x]);
	}
	printf("%d\n",(ans-n+mod)%mod);
}
