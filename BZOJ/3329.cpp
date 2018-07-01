#include<iostream>
#include<cstdio>
#include<cstring>
using namespace std;
typedef long long lint;
const lint mod=1e9+7;
int bit,mx[65];
lint dp[65][2];
struct mtrx{
	lint a,b,c,d;
	mtrx operator * (const mtrx y) const{
		return (mtrx){(a*y.a+b*y.c)%mod,(a*y.b+b*y.d)%mod,(c*y.a+d*y.c)%mod,(c*y.b+d*y.d)%mod};
	}
};

inline int nxi(){
	lint x=0;
	char c;
	while((c=getchar())>'9'||c<'0');
	while(x=x*10+c-48,(c=getchar())>='0'&&c<='9');
	return x;
}

inline void init(lint n){
	bit=0;
	while(n){
		mx[++bit]=n&1;
		n>>=1;
	}
}

mtrx qmi(mtrx x,lint t){
	if(t==1) return x;
	mtrx q=qmi(x,t>>1);
	q=q*q;
	if(t&1) q=q*x;
	return q;
}

lint dfs(int w,int t,bool f){
	if(w==2) return !f||mx[1]||mx[2]; 
	if(dp[w][t]&&!f) return dp[w][t];
	if(!f) return (dp[w-1][0]=dfs(w-1,0,0))+(dp[w-1][1]=dfs(w-1,1,0));
	lint ans=0;
	if(mx[w-1]&&!t) ans+=dfs(w-1,1,1);
	return ans+dfs(w-1,0,f&&mx[w-1]==0);
}

int main(){
	mtrx r=(mtrx){0,1,1,1};
	lint n,T=nxi();
	dp[1][1]=dp[2][0]=dp[2][1]=1;
	while(T--){
		n=nxi();
		init(n);
		printf("%lld\n",dfs(bit+1,0,1));
		printf("%lld\n",qmi(r,n).d+1);
	}
	return 0;
}
