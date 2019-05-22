#include <iostream>
#include <cstdio>
#include <cstring>
#include <cassert>
const int N=15;
int n,m,tot_v,sval[1<<N],fir[N],val[N][N],lg2[1<<N];
int dp[1<<N][N];

namespace utils{
	inline int nxi(FILE *fd=stdin){
		int x=0;
		char c;
		while(((c=fgetc(fd))>'9'||c<'0')&&c!='-');
		const bool f=(c=='-')&&(c=fgetc(fd));
		while(x=x*10-48+c,(c=fgetc(fd))>='0'&&c<='9');
		return f?-x:x;
	}
	template <class T> inline void apx(T &x,const T y){
		x<y?x=y:0;
	}
	template <class T> inline void apn(T &x,const T y){
		x>y?x=y:0;
	}
}
using namespace utils;

int main(){
	memset(dp,-63,sizeof(dp));
	n=nxi(),m=nxi();
	for(int i=0; i<n; ++i){
		lg2[1<<i]=i;
	}
	for(int i=1; i<=m; ++i){
		const int a=nxi()-1,b=nxi()-1;
		tot_v+=(val[a][b]=val[b][a]=nxi());
	}
	for(int i=1; i<1<<n; ++i){
		int lbit=i&-i,prev=i^lbit;
		sval[i]=sval[prev];
		int x=lg2[lbit];
		for(int j=0; j<n; ++j){
			if(i>>j&1) sval[i]+=val[x][j];
		}
	}
	for(int i=1; i<1<<n; i+=2){
		dp[i][0]=sval[i];
	}
	for(int i=1; i<1<<n; ++i){
		for(int j=0; j<n; ++j){
			if((i>>j&1)==0||dp[i][j]<-1e9) continue;
			for(int k=0; k<n; ++k){
				if(i>>k&1||val[j][k]==0) continue;
				apx(dp[i|1<<k][k],dp[i][j]+val[j][k]);
			}
			for(int k=(i+1)|i; k<1<<n; k=(k+1)|i){
				apx(dp[k][j],dp[i][j]+sval[(k^i)|1<<j]);
			}
		}
	}
	printf("%d\n",tot_v-dp[(1<<n)-1][n-1]);
	return 0;
}
