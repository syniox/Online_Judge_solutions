#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
#include <algorithm>
typedef long long lint;
using namespace std;
const int N=5e5+5,V=10;
const int mod=1e9+7;
int n,q,dp[N][V+1],wgt[N][V+1],lst[N];
//wgt[i]: 以str[i]开头的字符串
char str[N];

namespace utils{
#define eprintf(...) fprintf(stderr,__VA_ARGS__)
	template <class T> inline void apn(T &x,const T y){x=x<y?x:y;}
	template <class T> inline void apx(T &x,const T y){x=x>y?x:y;}
	template <class T> inline T cabs(const T &x){return x<0?-x:x;}
	static struct{
		template <class T> operator T(){
			T x=0;
			char c;
			while(((c=getchar())>'9'||c<'0')&&c!='-');
			const bool f=c=='-'&&(c=getchar());
			while(x=x*10-48+c,(c=getchar())>='0'&&c<='9');
			return f?-x:x;
		}
	}ni;
}
using namespace utils;

int main(){
	scanf("%s",str+1);
	n=strlen(str+1),q=ni;
	for(int lpos[V]={0},i=1; i<=n; ++i){
		const int c=str[i]-'a';
		lst[i]=lpos[c];
		for(int j=0; j<V; ++j){
			dp[i][j]=dp[i-1][j]*2ll%mod;
			dp[i][j]=(dp[i][j]-(lst[i]?dp[lst[i]-1][j]:0)+mod)%mod;
		}
		lpos[c]=i;
		for(int j=0; j<V; ++j){
			dp[i][V]=(dp[i][V]+dp[i][j])%mod;
		}
		if(!lst[i]) ++dp[i][c];
	}
	for(int i=1; i<=n; ++i){
		if(!lst[i]) wgt[i][str[i]-'a']=1;
		else{
			for(int j=0; j<=V; ++j){
				wgt[i][j]=(wgt[lst[i]][j]*2ll-wgt[lst[i]-1][j]+mod)%mod;//todo: lst[i]-1==0
			}
			if(lst[i]==1) wgt[i][V]=(wgt[i][V]-1+mod)%mod;
		}
	}
	while(q--){
		int l=ni,r=ni,ans=0;
		if(l==1){
			for(int i=0; i<V; ++i)
				ans=(ans+dp[r][i])%mod;
		}else{
			for(int i=0; i<V; ++i){
				ans=(ans+(lint)(dp[r][i]-1)*wgt[l-1][i])%mod;
			}
			ans=(ans+(lint)dp[r][V]*wgt[l-1][V])%mod;
		}
		printf("%d\n",ans);
	}
	return 0;
}
