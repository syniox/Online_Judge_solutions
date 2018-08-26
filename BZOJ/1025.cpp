#include<iostream>
#include<cstdio>
#include<cstring>
typedef long long lint;
const int N=1005;
int n,cnp,prm[200];
bool npr[N];
lint dp[N];

inline int nxi(){
	int x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(){
	npr[1]=1;
	for(int i=2;i<=n;++i){
		if(!npr[i]) prm[++cnp]=i;
		for(int j=1;j<=cnp&&i*prm[j]<=n;++j){
			npr[i*prm[j]]=1;
			if(i%prm[j]==0) break;
		}
	}
}

int main(){
	n=nxi();
	init();
//	for(int i=0;i<=n;++i) dp[i]=1;
	dp[0]=1;
	for(int i=1;i<=cnp&&prm[i]<=n;++i){
		for(int j=n;j;--j){
			for(int k=prm[i];k<=j;k=k*prm[i]){
				dp[j]+=dp[j-k];
			}
		}
	}
	lint ans=0;
	for(int i=0;i<=n;++i) ans+=dp[i];
	printf("%lld\n",ans);
}
